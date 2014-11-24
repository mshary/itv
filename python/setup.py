# Copyright (c) 2013-2014, Muhammad Shahzad Shafi <shahzad at voip-demos dot com>
# All rights reserved.
#
# Redistribution and use in source and binary forms, with or without
# modification, are permitted per Mozilla Public License v2.0.
#

from distutils.core import setup, Extension
setup(name='itv', version='1.0',  \
      ext_modules=[Extension(name = 'itv', sources = ['../src/itv.cpp', '../src/itv_ascii.cpp', '../src/itv_table.cpp', '../src/itv_utils.cpp', 'PyITV.cpp'], include_dirs = ['../src'], extra_compile_args = ['-std=c++11', '-fPIC'], extra_link_args = ['-lstdc++', '-lz'])])
