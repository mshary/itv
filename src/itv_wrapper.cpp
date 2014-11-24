#include "itv_config.h"
#include "itv_ascii.h"
#include "itv_words.h"
#include "itv_wrapper.h"

#ifdef __cplusplus
extern "C" {
#endif

	CITV_ASCII* itv_ascii_new() {
		ITV_ASCII *itv = new ITV_ASCII();
		return (CITV_ASCII*) itv;
	};

	CITV_ASCII* itv_ascii_init(const char* key) {
		std::string str = std::string(key);
		ITV_ASCII *itv = new ITV_ASCII(str);
		return (CITV_ASCII*) itv;
	};

	size_t itv_ascii_load(const CITV_ASCII* obj, size_t min, size_t max) {
		ITV_ASCII *itv = (ITV_ASCII*) obj;
		return itv->load(min, max);
	};

	const char* itv_ascii_dump(const CITV_ASCII* obj, char sep) {
		ITV_ASCII *itv = (ITV_ASCII*) obj;
		std::string str = itv->dump(sep);
		size_t len = str.size() + 1;
		char* res = new char[len];
		memset(res, '\0', len);
		return strcpy(res, str.c_str());
	};

	const char* itv_ascii_encode(const CITV_ASCII* obj, const char* msg) {
		ITV_ASCII *itv = (ITV_ASCII*) obj;
		std::string str = std::string(msg);
		itv->encode(str);
		size_t len = str.size() + 1;
		char* res = new char[len];
		memset(res, '\0', len);
		return strcpy(res, str.c_str());
	};

	const char* itv_ascii_decode(const CITV_ASCII* obj, const char* msg) {
		ITV_ASCII *itv = (ITV_ASCII*) obj;
		std::string str = std::string(msg);
		itv->decode(str);
		size_t len = str.size() + 1;
		char* res = new char[len];
		memset(res, '\0', len);
		return strcpy(res, str.c_str());
	};

	size_t itv_ascii_get_random(const CITV_ASCII* obj, size_t min, size_t max) {
		ITV_ASCII *itv = (ITV_ASCII*) obj;
		return itv->get_random(min, max);
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

	const char* itv_words_encode(const CITV_Words* obj, const char* msg) {
		ITV_Words *itv = (ITV_Words*) obj;
		std::string str = std::string(msg);
		itv->encode(str);
		size_t len = str.size() + 1;
		char* res = new char[len];
		memset(res, '\0', len);
		return strcpy(res, str.c_str());
	};

	const char* itv_words_decode(const CITV_Words* obj, const char* msg) {
		ITV_Words *itv = (ITV_Words*) obj;
		std::string str = std::string(msg);
		itv->decode(str);
		size_t len = str.size() + 1;
		char* res = new char[len];
		memset(res, '\0', len);
		return strcpy(res, str.c_str());
	};

	size_t itv_words_get_expected_length(const CITV_Words* obj, const char* msg, int decrypt) {
		ITV_Words *itv = (ITV_Words*) obj;
		return itv->get_expected_length(msg, decrypt);
	};

	void do_deflate(const char* in, char* out, size_t *out_len) {
		z_stream defstream;
		defstream.zalloc = Z_NULL;
		defstream.zfree = Z_NULL;
		defstream.opaque = Z_NULL;
		defstream.avail_in = (uInt)strlen(in)+1;
		defstream.next_in = (Bytef *)in;
		defstream.avail_out = (uInt)*out_len;
		defstream.next_out = (Bytef *)out;

		deflateInit(&defstream, Z_BEST_COMPRESSION);
		deflate(&defstream, Z_FINISH);
		deflateEnd(&defstream);
		*out_len = defstream.total_out;
	};

	void do_inflate(const char* in, char* out, size_t *out_len) {
		z_stream infstream;
		infstream.zalloc = Z_NULL;
		infstream.zfree = Z_NULL;
		infstream.opaque = Z_NULL;
		infstream.avail_in = (uInt)strlen(in)+1;
		infstream.next_in = (Bytef *)in;
		infstream.avail_out = (uInt)*out_len;
		infstream.next_out = (Bytef *)out;

		inflateInit(&infstream);
		inflate(&infstream, Z_NO_FLUSH);
		inflateEnd(&infstream);
		*out_len = infstream.total_out;
	};

#ifdef __cplusplus
};
#endif
