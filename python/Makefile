# Copyright (c) 2013-2014, Muhammad Shahzad Shafi <shahzad at voip-demos dot com>
# All rights reserved.
#
# Redistribution and use in source and binary forms, with or without
# modification, are permitted per Mozilla Public License v2.0.
#

all:
	python setup.py build
	cp -a build/lib*/*.so .

install:
	python setup.py install

clean:
	rm -fr build
	rm -fr *.so
