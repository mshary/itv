# Copyright (c) 2013-2015, Muhammad Shahzad Shafi <shahzad at voip-demos dot com>
# All rights reserved.
#
# Redistribution and use in source and binary forms, with or without
# modification, are permitted per Mozilla Public License v2.0.
#
CCFLAGS=-Wall -fpic -g -std=c++11 -I../src $(shell php-config --includes)
LDFLAGS=-g -Wall -lstdc++ -shared -litv -L../src

all:
	cd ../src; make all
	cd ../tests; make all
	cp -a ../src/libitv.so .
	swig -php -c++ -I../src ITV.i
	$(CC) $(CCFLAGS) -c ITV_wrap.cpp
	$(CC) ITV_wrap.o $(LDFLAGS) -o ITV.so

install:
	cd ../src; make install

uninstall:
	cd ../src; make uninstall

clean:
	cd ../src; make clean
	cd ../tests; make clean
	rm -fr *.so ITV_* ITVC.php php_*
