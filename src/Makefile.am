AM_CFLAGS = \
	$(libusb_CFLAGS) \
	-Wall -fPIE -pie

wdleds_LDADD = $(libusb_LIBS)
wdleds_LDFLAGS = -z now

bin_PROGRAMS = wdleds

wdleds_SOURCES = wdleds.c wdleds.h
