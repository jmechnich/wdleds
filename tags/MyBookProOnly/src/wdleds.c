/*
 *   USB WD My Book Fuel Gauge - userspace usblib program
 *		
 *   
 *   Copyright (C) 2007 Jonathan Krishnanantham, AsGF2MX@gmail.com
 *    
 *   This program is free software; you can redistribute it and/or
 *   modify it under the terms of the GNU General Public License as
 *   published by the Free Software Foundation, version 2.
 *         
 */
 
#include <stdio.h>
#include <string.h>
#include <usb.h>
#include <string.h>
#include <asm/errno.h>
#include "wdleds.h"

/* Function to manipulate the LED segments */
static int change_pattern (struct usb_dev_handle *handle,unsigned char pattern)
{
    char *disp_byte;
  	char data_bytes[] ={0x00,pattern};
    
    disp_byte=&data_bytes[0];
    
    /* The structure of the control message is based off USB data captures */
	return usb_control_msg(handle,0x21,0x9,0x200,0x1,disp_byte,0x2,2000);
}

/* Discover and return a handle to the My Book device */
static struct usb_dev_handle *device_init(char *serial)
{
    struct usb_device *dev;				/* Pointer to current usb device */
    struct usb_bus *usbubus = NULL;		/* Pointer to current usb bus */
    struct usb_bus *usb_busses = NULL;	/* Pointer to usb busses */
    struct usb_dev_handle *usb_handle;	/* Handle to usb device */
	char dev_serial[128];				/* Device serial number from usb device */

	/* Initialize and get a list of all usb busses and devices */
    usb_init();
    usb_find_busses();
    usb_find_devices();

	/* Obtain a pointer to the usb busses linked list first element */
    usb_busses = (struct usb_bus*)usb_get_busses();

	/* Run through each bus and its devices to find the device */ 
    for (usbubus = usb_busses;usbubus;usbubus = usbubus->next) 
    {
        for (dev = usbubus->devices;dev;dev = dev->next) {
			
			/* If the Vendor ID is WD */
            if (dev->descriptor.idVendor == VENDOR_ID) {

				/* If the Product ID is for Pro I or Premium or Premium S*/
				if ((dev->descriptor.idProduct == PRODUCT_ID_PROI)||	\
					(dev->descriptor.idProduct == PRODUCT_ID_PRES)||	\
					(dev->descriptor.idProduct == PRODUCT_ID_PRE)) {
				
					/* Get a handle to the device and return it if it is our device */
					usb_handle = usb_open(dev);
					if (usb_get_string_simple(usb_handle,0x3,&dev_serial[0],(size_t) \
						128)>0){
						if (strcasecmp(serial,&dev_serial[0])==0)
							return usb_handle;
					}
					/* Release the handle if it isn't our device */
					usb_close(usb_handle);
				}
            }                
        }
    }
    /* If our device isn't here the return NULL */
    return NULL;
}

/* Claim the required interface - Interface 1 - HID device */
static int claim_interface(struct usb_dev_handle *handle)
{
	/* Detach any kernel drivers associated to the interface */
	usb_detach_kernel_driver_np(handle,WD_HID_IFACE);
	/* Claim the interface */
	return usb_claim_interface(handle,WD_HID_IFACE);
}

/* Release the claimed interface */
static int release_interface(struct usb_dev_handle *handle)
{
	return usb_release_interface(handle,WD_HID_IFACE);
}

/* Main function */
int main(int argc, char **argv)
{
    struct usb_dev_handle *usb_handle;	/* Handle to device */

	char serial[128];					/* Disk serial number */
    unsigned char pattern;				/* Pattern to be displayed */
	int number = 0;						/* Pattern number read in */

    int retval = 1;						/* Default error return */

	/* Check and ensure enough arguments were provided */
	if (argc!=3){
        fprintf(stderr,"Usage: wdleds <disk serial> <integer between 0 and 64>\n");
        goto exit; 						
	}	

	/* Get the serial number */
	strcpy(serial,argv[1]);		

	/* Evaluate the number and accept or reject it */
	number = atoi(argv[2]);
	if (number>=0 && number<64){ 
		pattern = LED_RING|((unsigned char) number) ;
	}
	else{
        fprintf(stderr,"Error: Invalid argument!\n");
        fprintf(stderr,"Usage: wdleds <disk serial> <integer between 0 and 64>\n");
        goto exit;    	
	}
	
    /* Find the specified device and return a handle to it */
    usb_handle = device_init(serial);
    if (usb_handle == NULL) {
        fprintf(stderr,"Error: Could not find specified My Book USB device!\n");
        fprintf(stderr,"Are the permissions on the WD HID device set correctly?\n");
        goto exit;
    }

    /* Claim the interface */    
    if (claim_interface(usb_handle)) {
        fprintf(stderr,"Failed to claim My Book HID interface!\n");
        goto release;
    }

	/* Change the pattern */
    if	(change_pattern(usb_handle, pattern)<0){
        fprintf(stderr,"An error occured setting the LEDs!\n");
        goto release;    
    }		

	/* Release the claimed interface */
    if (release_interface(usb_handle)) {
       fprintf(stderr,"Failed to release the interface!\n");
       goto release;    
    }
    retval = 0;

release:
    usb_close(usb_handle);
exit:
    return retval;
}
