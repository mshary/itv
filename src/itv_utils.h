/*
 * Copyright (c) 2013-2015, Muhammad Shahzad Shafi <shahzad at voip-demos dot com>
 *
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted per Mozilla Public License v2.0.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE
 * LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
 * CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
 * SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
 * INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
 * CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
 * ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 * POSSIBILITY OF SUCH DAMAGE.
 */
#ifndef ITV_UTILS_H
#define ITV_UTILS_H

#include <deque>
#include <list>

using namespace::std;

// trim string from start
std::string &ltrim(std::string&);

// trim string from end
std::string &rtrim(std::string&);

// trim string from both ends
std::string &trim(std::string&);

// generate a random number from 0 to given number
size_t generate_random(size_t);

// generate a random number within range
size_t get_random(size_t, size_t);

// split string into deque according to given delimiter
std::deque<std::string>* split(std::string&, std::string&);

// convert codepoint to utf8 char
std::string to_utf8(size_t);

// convert codepoints to utf8 string
std::string to_utf8(std::list<size_t>&);

// convert utf8 string to codepoints
std::list<size_t>* from_utf8(std::string&);

#endif
