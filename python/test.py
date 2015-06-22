#!/usr/bin/python
# -*- coding: utf8 -*-

# Copyright (c) 2013-2014, Muhammad Shahzad Shafi <shahzad at voip-demos dot com>
# All rights reserved.
#
# Redistribution and use in source and binary forms, with or without
# modification, are permitted per Mozilla Public License v2.0.
#

import pyitv

# id starts with ASCII code 97 i.e. 'a'
ii = 97

# value also starts with ASCII code 97, i.e. 'a', 
# thus encrypted and decrypted text will have same character encoding
vv = 97

# how many characters with take part in encryption / decryption, 
# here all small letters of English language, i.e. a - z
ss = 26

# message to test encryption
msg = "a quick brown fox jumps over the lazy dog"

# another message for next round of encryption / decryption,
# notice the capital latters and symbols in message,
# these will not be encrypted, 
# -- the ITV Table should include them too --
next_msg = "Those who would give up essential Liberty, to purchase a little temporary Safety, deserve neither Liberty nor Safety - Benjamin Franklin"

#### Sender Side ####

# initialize the ITV Table on sender side
src = pyitv.itv_characters_init(ii, vv, ss)

# randomly shuffle the ids in ITV Table,
# this is highly recommended before saving key that will be sent to receiver
pyitv.itv_characters_shuffle(src);

# save the key before encryption, 
# receiver will need this key for decryption only the first time, 
# notice how key length is calculated
key_len = ss * 2 + 1
key = '\0'*key_len
pyitv.itv_characters_dump(src, key, len(key))

# print the key
print "Key:\t\t%s" % (key)

# create a char buffer to store encrypted text, 
# notice how the size of encrypted message is calculated
enc_len = len(msg) * 2 + 1
enc = '\0'*enc_len

# do the actual ecnryption
pyitv.itv_characters_encode(src, msg, enc, enc_len)

# save the next key, 
# neither sender nor receiver need to do anything with it,
# we are saving it here ONLY to print and demonstrate how key changes dynamically.
# notice the length of next key will be same as last key
next_key = '\0'*key_len
pyitv.itv_characters_dump(src, next_key, len(next_key))

# print the next key
print "Next Key:\t%s\n" % (next_key)

# create a char buffer to store encrypted text, 
next_enc_len = len(next_msg) * 2 + 1
next_enc = '\0'*next_enc_len

# do the actual ecnryption
pyitv.itv_characters_encode(src, next_msg, next_enc, next_enc_len)


#### Receiver Side ####

# initialize the ITV Table from key received from sender side
dst = pyitv.itv_characters_init2(key)

# create char buffer to store decrypted text, 
# notice how the size of decrypted message is calculated
dec_len = len(enc) / 2 + 1
dec = '\0'*dec_len

# do the actual decryption
pyitv.itv_characters_decode(dst, enc, dec, dec_len)

# create char buffer to store next decrypted text, 
next_dec_len = len(next_enc) / 2 + 1
next_dec = '\0'*next_dec_len

# decrypt next message,
# notice if you save / print the key before decrypting next message,
# then it will be identical to next_key
pyitv.itv_characters_decode(dst, next_enc, next_dec, next_dec_len)


# print it all
print "Original: %s\nEncrypted: %s\nDecrypted: %s\n\n" % (msg, enc, dec)
print "Original: %s\nEncrypted: %s\nDecrypted: %s\n\n" % (next_msg, next_enc, next_dec)


