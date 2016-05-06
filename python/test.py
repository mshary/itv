#!/usr/bin/python
# Copyright (c) 2013-2015, Muhammad Shahzad Shafi <shahzad at voip-demos dot com>
# All rights reserved.
#
# Redistribution and use in source and binary forms, with or without
# modification, are permitted per Mozilla Public License v2.0.
#
import pyitv

# message to test encryption
msg = "A Quick Brown Fox Jumps Over The Lazy Dog.";

# sender object - initialized with all printable ASCII
src = pyitv.ITV_Characters(32, 32, 126 - 32)

# shuffle the table and get its checksum, the receiver can
# match it to confirm it has correct itv table for decryption
src_cs = src.shuffle()

# get the table, this will be required by receiver for decryption
key = src.dump_table()

# encrypt the message
enc = src.encode(msg)

# print it out
print "Key: %s\nCS: 0x%x\n\nMSG: %s\nENC: %s\n" % (key, src_cs, msg, enc)


# initialize receiver object with itv table sent by sender
dst = pyitv.ITV_Characters(key)

# verify we have correct table for decrpytion
dst_cs = dst.checksum()

if src_cs == dst_cs:
	print "Checksum OK: 0x%x" % (dst_cs)
else:
	print "ERROR: Checksum Mismatch: 0x%x != 0x%x" % (src_cs, dst_cs)

# decrypt the message
dec = dst.decode(enc)

# print it out
print "DEC: %s" % (dec)
