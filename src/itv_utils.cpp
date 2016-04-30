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
#include <random>
#include <algorithm> 

#include "itv_utils.h"

using namespace::std;

// trim string from start
std::string &ltrim(std::string &s) {
	s.erase(s.begin(), std::find_if(s.begin(), s.end(), std::not1(std::ptr_fun<int, int>(std::isspace))));
	return s;
};

// trim string from end
std::string &rtrim(std::string &s) {
	s.erase(std::find_if(s.rbegin(), s.rend(), std::not1(std::ptr_fun<int, int>(std::isspace))).base(), s.end());
	return s;
};

// trim string from both ends
std::string &trim(std::string &s) {
	return ltrim(rtrim(s));
};

// generate a random number from 0 to given number
size_t generate_random(size_t max) {
	return get_random(0, max);
};

// generate a random number within range
size_t get_random(size_t min, size_t max) {
	std::random_device generator;
	std::uniform_int_distribution<size_t> distribution(min, max);
	return distribution(generator);
};

// split string into deque according to given delimiter
std::deque<std::string>* split(std::string& s, std::string& delimiter) {
	size_t last = 0, next = 0;
	std::deque<std::string>* ret = new deque<std::string>();
	while ((next = s.find(delimiter, last)) != string::npos) {
		ret->push_back(s.substr(last, next-last));
		last = next + 1;
	};
	ret->push_back(s.substr(last));
	return ret;
};

// convert codepoint to utf8 char
std::string to_utf8(size_t cp) {
	char c[5]={ 0x00,0x00,0x00,0x00,0x00 };
	if		(cp<=0x7F)		{ c[0] = cp;  }
	else if	(cp<=0x7FF)		{ c[0] = (cp>>6)+192; c[1] = (cp&63)+128; }
	else if	(0xd800<=cp && cp<=0xdfff) { } //invalid block of utf8
	else if	(cp<=0xFFFF)	{ c[0] = (cp>>12)+224; c[1]= ((cp>>6)&63)+128; c[2]=(cp&63)+128; }
	else if	(cp<=0x10FFFF)	{ c[0] = (cp>>18)+240; c[1] = ((cp>>12)&63)+128; c[2] = ((cp>>6)&63)+128; c[3]=(cp&63)+128; }
	return std::string(c);
}

// convert codepoints to utf8 string
std::string to_utf8(std::list<size_t>& msg) {
	std::string str = std::string();
	for (auto i=msg.begin(); i!=msg.end(); i++) { str += to_utf8(*i); };
    return str;
};

// converts utf8 string to codepoint list
std::list<size_t>* from_utf8(std::string& msg) {
	std::list<size_t> *ret = new std::list<size_t>();
	size_t len = msg.length();
	if (len < 1) return ret;

	for(auto i=0; i<len; i++) {
		unsigned char u0 = msg[i+0], u1 = msg[i+1], u2 = msg[i+2], u3 = msg[i+3];
		if (u0>=0 && u0<=127)	{ ret->push_back(u0); continue; };
		if (u0>=192 && u0<=223)	{ ret->push_back((u0-192)*64 + (u1-128)); i++; continue; };
		if (u0==0xed && (u1 & 0xa0) == 0xa0) { i++; continue; }; //codepoints 0xd800 to 0xdfff are not valid
		if (u0>=224 && u0<=239)	{ ret->push_back((u0-224)*4096 + (u1-128)*64 + (u2-128)); i++; i++; continue; };
		if (u0>=240 && u0<=247)	{ ret->push_back((u0-240)*262144 + (u1-128)*4096 + (u2-128)*64 + (u3-128)); i++; i++; i++; continue; };
		i++; i++; i++;
	};

	return ret;
};

