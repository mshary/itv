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

#define IS_IN_RANGE(c, f, l)    (((c) >= (f)) && ((c) <= (l)))

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
	std::string str = std::string();

	if (cp <= 0x7f) {
		str.append(1, static_cast<char>(cp));
	} else if (cp <= 0x7ff) {
		str.append(1, static_cast<char>(0xc0 | ((cp >> 6) & 0x1f)));
		str.append(1, static_cast<char>(0x80 | (cp & 0x3f)));
	} else if (cp <= 0xffff) {
		str.append(1, static_cast<char>(0xe0 | ((cp >> 12) & 0x0f)));
		str.append(1, static_cast<char>(0x80 | ((cp >> 6) & 0x3f)));
		str.append(1, static_cast<char>(0x80 | (cp & 0x3f)));
	} else {
		str.append(1, static_cast<char>(0xf0 | ((cp >> 18) & 0x07)));
		str.append(1, static_cast<char>(0x80 | ((cp >> 12) & 0x3f)));
		str.append(1, static_cast<char>(0x80 | ((cp >> 6) & 0x3f)));
		str.append(1, static_cast<char>(0x80 | (cp & 0x3f)));
	};

	return str;
};

// convert codepoints to utf8 string
std::string to_utf8(std::list<size_t>& msg) {
	std::string str = std::string();

	for (auto i=msg.begin(); i!=msg.end(); i++) {
		str += to_utf8(*i);
	};

    return str;
};

// convert utf8 string to codepoints
std::list<size_t>* from_utf8(std::string& msg) {
	unsigned char c1, c2, *ptr = (unsigned char*) msg.c_str();
	std::list<size_t> *ret = new std::list<size_t>();
	size_t len = msg.length();

	while (len) {
		size_t uc = 0, seqlen = 0;
		if (len < 1) { return ret; };
		c1 = ptr[0];

		if ((c1 & 0x80) == 0) {
			uc = (size_t) (c1 & 0x7F);
			seqlen = 1;
		} else if ((c1 & 0xE0) == 0xC0) {
			uc = (size_t) (c1 & 0x1F);
			seqlen = 2;
		} else if ((c1 & 0xF0) == 0xE0) {
			uc = (size_t) (c1 & 0x0F);
			seqlen = 3;
		} else if ((c1 & 0xF8) == 0xF0) {
			uc = (size_t) (c1 & 0x07);
			seqlen = 4;
		} else {
			break;
		};

		if (seqlen > len) { return ret; };

		for (size_t i = 1; i < seqlen; ++i) {
			c1 = ptr[i];
			if ((c1 & 0xC0) != 0x80) { return ret; };
		};

		switch (seqlen) {
			case 2: {
				c1 = ptr[0];
				if (!IS_IN_RANGE(c1, 0xC2, 0xDF)) { return ret; };
				break;
			};

			case 3: {
				c1 = ptr[0];
				c2 = ptr[1];

				if (((c1 == 0xE0) && !IS_IN_RANGE(c2, 0xA0, 0xBF)) ||
					((c1 == 0xED) && !IS_IN_RANGE(c2, 0x80, 0x9F)) ||
					(!IS_IN_RANGE(c1, 0xE1, 0xEC) && !IS_IN_RANGE(c1, 0xEE, 0xEF))) {
					return ret;
				};

				break;
			};

			case 4: {
				c1 = ptr[0];
				c2 = ptr[1];

				if (((c1 == 0xF0) && !IS_IN_RANGE(c2, 0x90, 0xBF)) ||
					((c1 == 0xF4) && !IS_IN_RANGE(c2, 0x80, 0x8F)) ||
					(!IS_IN_RANGE(c1, 0xF1, 0xF3))) {
					return ret;
				};

				break;
			};
		};

		for (size_t i = 1; i < seqlen; ++i) { uc = ((uc << 6) | (size_t)(ptr[i] & 0x3F)); };
		ret->push_back(uc);

		ptr += seqlen;
		len -= seqlen;
	};

	return ret;
};

