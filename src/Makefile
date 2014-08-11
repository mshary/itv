# Copyright (c) 2013-2014, Muhammad Shahzad Shafi <shahzad at voip-demos dot com>
# All rights reserved.
#
# Redistribution and use in source and binary forms, with or without
# modification, are permitted per Mozilla Public License v2.0.
#
CFLAGS=-Wall -Werror -g -ansi -pedantic -std=c89
CCFLAGS=-Wall -Werror -g -std=c++11
LDFLAGS=-g -Wall -lstdc++

OBJS=itv.o itv_ascii.o itv_table.o itv_words.o itv_wrapper.o main.o
PROG=itv

all: $(PROG)
default: all

wrapper:
	$(CC) $(CCFLAGS) -c itv.cpp itv_ascii.cpp itv_table.cpp itv_words.cpp itv_wrapper.cpp
	$(CC) $(CFLAGS) -c main.c
	$(CC) $(OBJS) $(LDFLAGS) -o itv

%.o: %.cpp
	$(CC) $(CCFLAGS) -c $<

%.o: %.c
	$(CC) $(CFLAGS) -c $<

$(PROG): $(OBJS)
	$(CC) $(OBJS) $(LDFLAGS) -o $@

clean:
	rm -f $(OBJS)
	rm -f $(PROG)
	rm -f *~
