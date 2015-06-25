#!/bin/sh
gcc -Wall -fPIC -c *.c -I/usr/include/python2.7
gcc -shared -Wl,-soname,libctest.so.1 -o libctest.so.1.0   *.o -lpython2.7

