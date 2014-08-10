#include "itv_config.h"
#include "itv_wrapper.h"

extern "C" {
	CITV_ASCII* itv_ascii_new() {
		ITV_ASCII *itv = new ITV_ASCII();
		return (CITV_ASCII*) itv;
	};

	CITV_ASCII* itv_ascii_init(const char* key) {
		ITV_ASCII *itv = new ITV_ASCII(std::string(key));
		return (CITV_ASCII*) itv;
	};

	size_t itv_ascii_load(const CITV_ASCII* obj, size_t min, size_t max) {
		ITV_ASCII *itv = (ITV_ASCII*) obj;
		return itv->load(min, max);
	};

	size_t itv_ascii_dump(const CITV_ASCII* obj, char sep, char* buf) {
		ITV_ASCII *itv = (ITV_ASCII*) obj;
		std::string str = itv->dump(sep);
		size_t len = str.length();
		strncpy(buf, str.c_str(), len);
		buf[len] = '\0';
		return len;
	};

	size_t itv_ascii_encode(const CITV_ASCII* obj, const char* msg, char* buf) {
		ITV_ASCII *itv = (ITV_ASCII*) obj;
		std::string str = itv->encode(msg);
		size_t len = str.length();
		strncpy(buf, str.c_str(), len);
		buf[len] = '\0';
		return len;
	};

	size_t itv_ascii_decode(const CITV_ASCII* obj, const char* msg, char* buf) {
		ITV_ASCII *itv = (ITV_ASCII*) obj;
		std::string str = itv->decode(msg);
		size_t len = str.length();
		strncpy(buf, str.c_str(), len);
		buf[len] = '\0';
		return len;
	};

	CITV_Words* itv_words_new() {
		ITV_Words *itv = new ITV_Words();
		return (CITV_Words*) itv;
	};

	CITV_Words* itv_words_init(const char* file, size_t min_id) {
		ITV_Words *itv = new ITV_Words(file, min_id);
		return (CITV_Words*) itv;
	};

	size_t itv_words_save(const CITV_Words* obj, const char* file) {
		ITV_Words *itv = (ITV_Words*) obj;
		return itv->write(file);
	};

	size_t itv_words_encode(const CITV_Words* obj, const char* msg, char* buf) {
		ITV_Words *itv = (ITV_Words*) obj;
		std::string str = itv->encode(msg);
		size_t len = str.length();
		strncpy(buf, str.c_str(), len);
		buf[len] = '\0';
		return len;
	};

	size_t itv_words_decode(const CITV_Words* obj, const char* msg, char* buf) {
		ITV_Words *itv = (ITV_Words*) obj;
		std::string str = itv->decode(msg);
		size_t len = str.length();
		strncpy(buf, str.c_str(), len);
		buf[len] = '\0';
		return len;
	};

	size_t itv_words_get_expected_length(const CITV_Words* obj, const char* msg, int decrypt) {
		ITV_Words *itv = (ITV_Words*) obj;
		return itv->get_expected_length(msg, decrypt);
	};

};
