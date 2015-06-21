# Copyright (c) 2013-2014, Muhammad Shahzad Shafi <shahzad at voip-demos dot com>
# All rights reserved.
#
# Redistribution and use in source and binary forms, with or without
# modification, are permitted per Mozilla Public License v2.0.
#
from distutils.core import setup, Extension

setup(name='pyitv', version='1.0',  \
      ext_modules=[Extension(name = '_pyitv', sources = ['../src/itv.cpp', '../src/itv_table.cpp', '../src/itv_characters.cpp', '../src/itv_utils.cpp', '../src/itv_wrapper.cpp', '_pyitv_module.cc'], include_dirs = ['../src'], extra_compile_args = ['-std=c++11', '-fPIC', '-Wno-deprecated-register'], extra_link_args = ['-lstdc++'])])
