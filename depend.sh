#!/bin/sh
# Based on the paper "Recrusive Make Considered Harmful" by Peter Miller
# http://miller.emu.id.au/pmiller/books/rmch/

g++ -MM -MG "$@" |
sed -e `s@^\(.*\)\.o:@\1.d \1.o:@`
