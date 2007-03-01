## Process this file with automake to produce Makefile.in

## Created by Anjuta

INCLUDES = \
	-DPACKAGE_LOCALE_DIR=\""$(prefix)/$(DATADIRNAME)/locale"\" \
	-DPACKAGE_SRC_DIR=\""$(srcdir)"\" \
	-DPACKAGE_DATA_DIR=\""$(datadir)"\" 

AM_CFLAGS =\
	 -Wall

bin_PROGRAMS = wdleds

wdleds_SOURCES = \
	wdleds.c				\
	wdleds.h

wdleds_LDFLAGS =

wdleds_LDADD = -L /lib/ -lusb
