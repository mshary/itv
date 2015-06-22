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

	void itv_characters_dump(const CITV_Characters* obj, char* buf, size_t len) {
		ITV_Characters *itv = (ITV_Characters*) obj;
		std::string key = itv->dump();
		strncpy(buf, key.c_str(), len-1);
		buf[len-1] = '\0';
	};

    void itv_characters_encode(const CITV_Characters* obj, const char* msg, char* buf, size_t len) {
		ITV_Characters *itv = (ITV_Characters*) obj;
		std::string str = std::string(msg);
		std::list<size_t>* plain_text = from_utf8(str);
		std::list<size_t> *encrypted_text = itv->encode(*plain_text);
		strncpy(buf, to_utf8(*encrypted_text).c_str(), len-1);
		buf[len-1] = '\0';
	};

    void itv_characters_decode(const CITV_Characters* obj, const char* msg, char* buf, size_t len) {
		ITV_Characters *itv = (ITV_Characters*) obj;
		std::string str = std::string(msg);
		std::list<size_t>* encrypted_text = from_utf8(str);
		std::list<size_t>* plain_text = itv->decode(*encrypted_text);
		strncpy(buf, to_utf8(*plain_text).c_str(), len-1);
		buf[len-1] = '\0';
	};

    void itv_characters_to_string(const CITV_Characters* obj, char* buf, size_t len) {
		ITV_Characters *itv = (ITV_Characters*) obj;
		strncpy(buf, itv->to_string().c_str(), len-1);
		buf[len-1] = '\0';
	};

    void get_utf8(size_t cp, char* buf, size_t len) {
		strncpy(buf, to_utf8(cp).c_str(), len-1);
		buf[len-1] = '\0';
	};
    
    size_t get_random(size_t max) {
		return generate_random(max);
	};

#ifdef __cplusplus
};
#endif
