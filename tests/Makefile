# Copyright (c) 2013-2014, Muhammad Shahzad Shafi <shahzad at voip-demos dot com>
# All rights reserved.
#
# Redistribution and use in source and binary forms, with or without
# modification, are permitted per Mozilla Public License v2.0.
#

CFLAGS=-Wall -Werror -g -ansi -pedantic -std=c89 -I../src
CCFLAGS=-Wall -Werror -g -std=c++11 -I../src
LDFLAGS=-g -Wall -lstdc++ -lz -litv -L../src

all:
	cd ../src; make all
	$(CC) $(CCFLAGS) -c cppwrap_test.cpp
	$(CC) cppwrap_test.o $(LDFLAGS) -o cppwrap_test
	$(CC) $(CFLAGS) -c cwrap_test.c
	$(CC) cwrap_test.o $(LDFLAGS) -o cwrap_test
	cp -a ../src/libitv.so .

clean:
	cd ../src; make clean
	rm -fr *.o
	rm -fr *.so
	rm -fr *_test
