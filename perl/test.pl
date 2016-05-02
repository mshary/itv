#!/usr/bin/perl -w
use strict;
use warnings;

use ITV;

my $len = 126 - 32;
my $sender = ITV::itv_characters_init(32, 32, $len);

ITV::itv_characters_shuffle($sender);
my $sender_cs = ITV::itv_characters_checksum($sender);

my $key_len = ($len * 2) + 1;
my $key = "\0" x $key_len;
ITV::itv_characters_dump($sender, $key, $key_len);

my $msg = "A Quick Brown Fox Jumps Over The Lazy Dog.";

my $enc_len = (length($msg) * 2) + 1;
my $enc = "\0" x $enc_len;
ITV::itv_characters_encode($sender, $msg, $enc, $enc_len);
print "MSG: $msg\nENC: $enc\n";

my $receiver = ITV::itv_characters_init2($key);
my $receiver_cs = ITV::itv_characters_checksum($receiver);

if ($sender_cs eq $receiver_cs) {
	print "\nKey: $key\nCS:  $receiver_cs\n\n";

	my $dec_len = $enc_len;
	my $dec = "\0" x $dec_len;

	ITV::itv_characters_decode($receiver, $enc, $dec, $dec_len);
	print "DEC: $dec\n";
} else {
	print "Failure: checksum mismatch $sender_cs != $receiver_cs\n";
};

exit;
