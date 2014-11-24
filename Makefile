# Copyright (c) 2013-2014, Muhammad Shahzad Shafi <shahzad at voip-demos dot com>
# All rights reserved.
#
# Redistribution and use in source and binary forms, with or without
# modification, are permitted per Mozilla Public License v2.0.
#

all:
	cd src; make all
	cd tests; make all
	ln -s src/libitv.so

clean:
	cd src; make clean
	cd tests; make clean
	rm -fr *.so
