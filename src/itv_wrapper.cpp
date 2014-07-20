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

	int itv_ascii_load(const CITV_ASCII* obj, unsigned int min, unsigned int max) {
		ITV_ASCII *itv = (ITV_ASCII*) obj;
		return itv->load(min, max);
	};

	int itv_ascii_dump(const CITV_ASCII* obj, unsigned int sep, char* buf) {
		ITV_ASCII *itv = (ITV_ASCII*) obj;
		std::string str = itv->dump(sep);
		strcpy(buf, str.c_str());
		return str.length();
	};

	int itv_ascii_encode(const CITV_ASCII* obj, const char* msg, char* buf) {
		ITV_ASCII *itv = (ITV_ASCII*) obj;
		std::string str = itv->encode(msg);
		strcpy(buf, str.c_str());
		return str.length();
	};

	int itv_ascii_decode(const CITV_ASCII* obj, const char* msg, char* buf) {
		ITV_ASCII *itv = (ITV_ASCII*) obj;
		std::string str = itv->decode(msg);
		strcpy(buf, str.c_str());
		return str.length();
	};
};