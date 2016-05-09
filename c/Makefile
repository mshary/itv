# Copyright (c) 2013-2015, Muhammad Shahzad Shafi <shahzad at voip-demos dot com>
# All rights reserved.
#
# Redistribution and use in source and binary forms, with or without
# modification, are permitted per Mozilla Public License v2.0.
#
CFLAGS=-Wall -g -ansi -pedantic -std=c99 -I../src
LDFLAGS=-Wall -g -lstdc++ -lz -litv -L../src

all:
	cd ../src; make all
	$(CC) $(CFLAGS) -c test.c
	$(CC) test.o $(LDFLAGS) -o test
	cp -a ../src/libitv.so .

clean:
	cd ../src; make clean
	rm -fr *.o
	rm -fr *.so
	rm -fr *test
