#include <stdlib.h>
#include <string.h>

typedef void CITV_ASCII;
typedef void CITV_Words;

#ifdef __cplusplus
extern "C" {
#endif

	CITV_ASCII* itv_ascii_new();
	CITV_ASCII* itv_ascii_init(const char*);

	size_t itv_ascii_load(const CITV_ASCII*, size_t, size_t);
	size_t itv_ascii_dump(const CITV_ASCII*, char, char*);

	size_t itv_ascii_encode(const CITV_ASCII*, const char*, char*);
	size_t itv_ascii_decode(const CITV_ASCII*, const char*, char*);

	CITV_Words* itv_words_new();
	CITV_Words* itv_words_init(const char*, size_t);

	size_t itv_words_save(const CITV_Words*, const char*);
	size_t itv_words_encode(const CITV_Words*, const char*, char*);
	size_t itv_words_decode(const CITV_Words*, const char*, char*);
	size_t itv_words_get_expected_length(const CITV_Words*, const char*, int);

#ifdef __cplusplus
}
#endif
