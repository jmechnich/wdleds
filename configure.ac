AC_INIT([wdleds], [0.9.4])
AC_CONFIG_SRCDIR([src/wdleds.c])
AM_INIT_AUTOMAKE
AC_CONFIG_HEADERS([config.h])

AC_ISC_POSIX
AC_PROG_CC
AM_PROG_CC_STDC
AC_HEADER_STDC
PKG_CHECK_MODULES([libusb],[libusb])

AC_CONFIG_FILES([
 Makefile
 essential_scripts/Makefile
 src/Makefile
])
AC_OUTPUT
