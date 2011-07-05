#!/bin/bash

if [ "$1" == "init" ]
then
    autoreconf --install
elif [ "$1" == "remove" ]
then
    rm -r configure Makefile.in depcomp config.guess config.sub ltmain.sh \
	autom4te.cache missing aclocal.m4 install-sh m4/ltsugar.m4 \
	m4/libtool.m4 m4/ltversion.m4 m4/lt~obsolete.m4 m4/ltoptions.m4 \
	include/config.h.in src/Makefile.in src/josh/Makefile.in \
	src/josh/token/Makefile.in src/josh/system/Makefile.in \
	src/josh/ast/Makefile.in src/josh/ir/Makefile.in
else
    echo "Invalid option: $1"
    echo "Use init or remove"
    exit 1
fi
