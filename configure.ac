# Process this file with autoconf to produce a configure script

AC_INIT([josh], [1.0], [jilarson@umich.edu])
AC_CONFIG_MACRO_DIR([m4])
AM_INIT_AUTOMAKE([foreign -Wall -Werror])
LT_INIT
AC_PROG_CXX
AC_CONFIG_HEADERS([include/config.h])
AC_CONFIG_FILES([
 Makefile
 src/Makefile
 src/josh/Makefile
 src/josh/ast/Makefile
 src/josh/ir/Makefile
 src/josh/system/Makefile
 src/josh/token/Makefile
])
AC_OUTPUT
