#!/bin/bash

if [ "$1" == "clean" ]
then
    make uninstall
    make distclean
    exit $?
fi

if [ "$1" == "init" ]
then
    ./configure --prefix=$PWD/build
fi

make && make install
exit $?
