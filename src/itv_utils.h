/*
 * Copyright (c) 2013-2014, Muhammad Shahzad Shafi <shahzad at voip-demos dot com>
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

#include "itv_config.h"

// trim string from start
static inline std::string &ltrim(std::string &s) {
	s.erase(s.begin(), std::find_if(s.begin(), s.end(), std::not1(std::ptr_fun<int, int>(std::isspace))));
	return s;
};

// trim string from end
static inline std::string &rtrim(std::string &s) {
	s.erase(std::find_if(s.rbegin(), s.rend(), std::not1(std::ptr_fun<int, int>(std::isspace))).base(), s.end());
	return s;
};

// trim string from both ends
static inline std::string &trim(std::string &s) {
	return ltrim(rtrim(s));
};

static inline bool compare_ids(ITV &first, ITV &second) {
	return (first.get_id() <  second.get_id());
};

static inline bool compare_tags(ITV &first, ITV &second) {
	return (first.get_tag() <  second.get_tag());
};

static inline bool is_symbol(char c) {
	return ((c < 48 || c > 57) && (c < 65 || c > 90) && (c < 97 || c > 122));
};

static inline std::string do_compress(const std::string &str, bool gz, int level = Z_BEST_COMPRESSION) {
	int ret;
	z_stream zstr;

	memset(&zstr, 0, sizeof(zstr));
	ret = (gz) ? deflateInit2(&zstr, level, Z_DEFLATED, MAX_WBITS + 16, 9, Z_DEFAULT_STRATEGY) : deflateInit(&zstr, level);

	if (ret != Z_OK) {
		return std::string();
	};

	zstr.next_in = (Bytef*)str.data();
	zstr.avail_in = str.size();

	char buf[32768];
	std::string output;

	do {
		zstr.next_out = reinterpret_cast<Bytef*>(buf);
		zstr.avail_out = sizeof(buf);
		ret = deflate(&zstr, Z_FINISH);
		if (output.size() < zstr.total_out) {
			output.append(buf, zstr.total_out - output.size());
		};
	} while (ret == Z_OK);

	deflateEnd(&zstr);
	return (ret != Z_STREAM_END) ? std::string() : output;
};

static inline std::string do_decompress(const std::string &str, bool gz) {
	int ret;
	z_stream zstr;

	memset(&zstr, 0, sizeof(zstr));
	ret = (gz) ? inflateInit2(&zstr, MAX_WBITS + 16) : inflateInit(&zstr);

	if (ret != Z_OK) {
		return std::string();
	};

	zstr.next_in = (Bytef*)str.data();
	zstr.avail_in = str.size();

	char buf[32768];
	std::string output;

	do {
		zstr.next_out = reinterpret_cast<Bytef*>(buf);
		zstr.avail_out = sizeof(buf);
		ret = inflate(&zstr, Z_NO_FLUSH);
		if (output.size() < zstr.total_out) {
			output.append(buf, zstr.total_out - output.size());
		};
	} while (ret == Z_OK);

	inflateEnd(&zstr);
	return (ret != Z_STREAM_END) ? std::string() : output;
};

#endif
