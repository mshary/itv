# Copyright (c) 2013-2015, Muhammad Shahzad Shafi <shahzad at voip-demos dot com>
# All rights reserved.
#
# Redistribution and use in source and binary forms, with or without
# modification, are permitted per Mozilla Public License v2.0.
#
CCFLAGS=-Wall -g -std=c++11 -fPIC -I../src -I$(shell locate -b CORE | grep lib)
LDFLAGS=-Wall -g -lstdc++ -shared -litv -L../src

all:
	cd ../src; make all
	cd ../tests; make all
	cp -a ../src/libitv.so .
	swig -perl5 -c++ -I../src ITV.i
	$(CC) $(CCFLAGS) -c ITV_wrap.cxx
	$(CC) ITV_wrap.o $(LDFLAGS) -o ITV.so

install:
	cd ../src; make install

uninstall:
	cd ../src; make uninstall

clean:
	cd ../src; make clean
	cd ../tests; make clean
	rm -fr *.so ITV_wrap.* *.pm
