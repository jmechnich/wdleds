/*
 *   USB WD My Book Fuel Gauge - userspace usblib program header
 *
 *
 *   Copyright (C) 2007 Jonathan Krishnanantham, AsGF2MX@gmail.com
 *
 *   This program is free software; you can redistribute it and/or
 *   modify it under the terms of the GNU General Public License as
 *   published by the Free Software Foundation, version 2.
 *
 */

/* LED RING start address */
#define LED_RING                0x80
/* Segments */
#define SEG0                    0x01
#define SEG1                    0x02
#define SEG2                    0x04
#define SEG3                    0x08
#define SEG4                    0x10
#define SEG5                    0x20

/* Vendor and Product IDs */
#define VENDOR_ID               0x1058
#define PRODUCT_ID_PROI         0x0902
#define PRODUCT_ID_PRE          0x0902
#define PRODUCT_ID_PRES         0x0902
#define PRODUCT_ID_H1CS         0x1102
#define PRODUCT_ID_STUDIO       0x1103

/* WD HID interface number */
#define WD_HID_IFACE            0x1
