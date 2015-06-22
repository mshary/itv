#include <stdlib.h>

typedef void CITV_Characters;

#ifdef __cplusplus
extern "C" {
#endif

	CITV_Characters* itv_characters_init(size_t, size_t, size_t);
	CITV_Characters* itv_characters_init2(const char*);

	size_t itv_characters_read(const CITV_Characters*, const char*);
	size_t itv_characters_write(const CITV_Characters*, const char*);

	void itv_characters_shuffle(const CITV_Characters*);
	void itv_characters_dump(const CITV_Characters*, char*, size_t);
	void itv_characters_encode(const CITV_Characters*, const char*, char*, size_t);
	void itv_characters_decode(const CITV_Characters*, const char*, char*, size_t);
	void itv_characters_to_string(const CITV_Characters*, char*, size_t);

	void get_utf8(size_t, char*, size_t);
	size_t get_random(size_t);

#ifdef __cplusplus
}
#endif
