# Copyright (c) 2013-2015, Muhammad Shahzad Shafi <shahzad at voip-demos dot com>
# All rights reserved.
#
# Redistribution and use in source and binary forms, with or without
# modification, are permitted per Mozilla Public License v2.0.
#
CFLAGS=-Wall -Werror -g -fPIC -ansi -pedantic -std=c89
CCFLAGS=-Wall -Werror -g -fPIC -std=c++11
LDFLAGS=-g -Wall -lstdc++ -shared

#OBJS=itv.o itv_ascii.o itv_table.o itv_words.o itv_wrapper.o itv_utils.o
OBJS=itv.o itv_table.o itv_characters.o itv_utils.o itv_wrapper.o
PROG=libitv.so

PREFIX=/usr
INCDIR=$(PREFIX)/include/itv
LIBDIR=$(PREFIX)/lib

all: $(PROG)
default: all

wrapper:
	$(CC) $(CCFLAGS) -c itv.cpp itv_table.cpp itv_characters.cpp itv_utils.cpp itv_wrapper.cpp
	$(CC) $(OBJS) $(LDFLAGS) -o $(PROG)

%.o: %.cpp
	$(CC) $(CCFLAGS) -c $<

%.o: %.c
	$(CC) $(CFLAGS) -c $<

$(PROG): $(OBJS)
	$(CC) $(OBJS) $(LDFLAGS) -o $@

install: $(PROG)
	mkdir -p $(INCDIR)
	mkdir -p $(LIBDIR)
	install -m 0644 *.h $(INCDIR)
	install -m 0755 $(PROG) $(LIBDIR)
	ldconfig

uninstall:
	rm -fr $(INCDIR)
	rm -fr $(LIBDIR)/$(PROG)

clean:
	rm -f $(OBJS)
	rm -f $(PROG)
	rm -f *~ itv
