typedef void CITV_ASCII;

#ifdef __cplusplus
extern "C" {
#endif

	CITV_ASCII* itv_ascii_new();
	CITV_ASCII* itv_ascii_init(const char*);

	size_t itv_ascii_load(const CITV_ASCII*, size_t, size_t);
	size_t itv_ascii_dump(const CITV_ASCII*, char, char*);

	size_t itv_ascii_encode(const CITV_ASCII*, const char*, char*);
	size_t itv_ascii_decode(const CITV_ASCII*, const char*, char*);

#ifdef __cplusplus
}
#endif
