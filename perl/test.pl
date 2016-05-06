#!/usr/bin/perl -w
# Copyright (c) 2013-2015, Muhammad Shahzad Shafi <shahzad at voip-demos dot com>
# All rights reserved.
#
# Redistribution and use in source and binary forms, with or without
# modification, are permitted per Mozilla Public License v2.0.
#
use strict;
use warnings;

use ITV;

my $msg = "A Quick Brown Fox Jumps Over The Lazy Dog.";

my $sender = ITV::ITV_Characters->new(65, 65, 126 - 65);
$sender->load(32, 32, 1);

my $sender_cs = $sender->shuffle();
my $key = $sender->dump_table();
my $enc = $sender->encode($msg);

print "Key: $key\nCS: $sender_cs\n\n";
print "MSG: $msg\nENC: $enc\n\n";

my $receiver = ITV::ITV_Characters->new($key);
my $receiver_cs = $receiver->checksum();

if ($sender_cs eq $receiver_cs) {
	print "Checksum OK: $receiver_cs\n";
} else {
	print "ERROR: Checksum Mismatch: $sender_cs != $receiver_cs\n";
	exit;
};

my $dec = $receiver->decode($enc);
print "DEC: $dec\n";

exit;
