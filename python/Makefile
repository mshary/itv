# Copyright (c) 2013-2015, Muhammad Shahzad Shafi <shahzad at voip-demos dot com>
# All rights reserved.
#
# Redistribution and use in source and binary forms, with or without
# modification, are permitted per Mozilla Public License v2.0.
#
all:
	swig -python -c++ -I../src -o _pyitv_module.cc pyitv.i
	python setup.py build_ext --inplace

install:
	python setup.py install

clean:
	rm -fr _pyitv_module.cc pyitv.py* *.so build
