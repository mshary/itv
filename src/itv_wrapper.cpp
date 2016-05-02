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
#include <iostream>
#include <string.h>

#include "itv_utils.h"
#include "itv_characters.h"
#include "itv_wrapper.h"

#ifdef __cplusplus
extern "C" {
#endif

	CITV_Characters* itv_characters_init(size_t id, size_t value, size_t len) {
		ITV_Characters *itv = new ITV_Characters(id, value, len);
		return (CITV_Characters*) itv;
	};

	CITV_Characters* itv_characters_init2(const char* key) {
		std::string str = std::string(key);
		ITV_Characters *itv = new ITV_Characters(str);
		return (CITV_Characters*) itv;
	};

	size_t itv_characters_checksum(const CITV_Characters* obj) {
		ITV_Characters *itv = (ITV_Characters*) obj;
		return itv->checksum();
	};

	size_t itv_characters_read(const CITV_Characters* obj, const char* path) {
		ITV_Characters *itv = (ITV_Characters*) obj;
		std::string file = std::string(path);
		return itv->read(file);
	};

	size_t itv_characters_write(const CITV_Characters* obj, const char* path) {
		ITV_Characters *itv = (ITV_Characters*) obj;
		std::string file = std::string(path);
		return itv->write(file);
	};

	void itv_characters_shuffle(const CITV_Characters* obj) {
		ITV_Characters *itv = (ITV_Characters*) obj;
		itv->shuffle();
	};

	int itv_characters_dump(const CITV_Characters* obj, char* buf, size_t len) {
		ITV_Characters *itv = (ITV_Characters*) obj;
		const char* key = itv->dump().c_str();
		size_t key_len = strlen(key);
		if ((key_len + 1) > len) return (len - (key_len + 1));

		memcpy(buf, key, key_len);
		buf[key_len] = '\0';
		return key_len;
	};

	int itv_characters_encode(const CITV_Characters* obj, const char* msg, char* buf, size_t len) {
		ITV_Characters *itv = (ITV_Characters*) obj;
		std::string str = std::string(msg);
		std::list<size_t>* plain_text = from_utf8(str);
		std::list<size_t> *encrypted_text = itv->encode(*plain_text);
		const char* ret = to_utf8(*encrypted_text).c_str();
		size_t ret_len = strlen(ret);
		if ((ret_len + 1) > len) return (len - (ret_len + 1));

		memcpy(buf, ret, ret_len);
		buf[ret_len] = '\0';
		return ret_len;
	};

    int itv_characters_decode(const CITV_Characters* obj, const char* msg, char* buf, size_t len) {
		ITV_Characters *itv = (ITV_Characters*) obj;
		std::string str = std::string(msg);
		std::list<size_t>* encrypted_text = from_utf8(str);
		std::list<size_t>* plain_text = itv->decode(*encrypted_text);
		const char* ret = to_utf8(*plain_text).c_str();
		size_t ret_len = strlen(ret);
		if ((ret_len + 1) > len) return (len - (ret_len + 1));

		memcpy(buf, ret, ret_len);
		buf[ret_len] = '\0';
		return ret_len;
	};

    int itv_characters_to_string(const CITV_Characters* obj, char* buf, size_t len, size_t inner, size_t outer) {
		ITV_Characters *itv = (ITV_Characters*) obj;
		const char* ret = itv->to_string(inner, outer).c_str();
		size_t ret_len = strlen(ret);
		if ((ret_len + 1) > len) return (len - (ret_len + 1));

		memcpy(buf, ret, ret_len);
		buf[ret_len] = '\0';
		return ret_len;
	};

    int get_utf8(size_t cp, char* buf, size_t len) {
		const char* ret = to_utf8(cp).c_str();
		size_t ret_len = strlen(ret);
		if ((ret_len + 1) > len) return (len - (ret_len + 1));

		memcpy(buf, ret, ret_len);
		buf[ret_len] = '\0';
		return ret_len;
	};
    
    size_t get_random(size_t max) {
		return generate_random(max);
	};

#ifdef __cplusplus
};
#endif
