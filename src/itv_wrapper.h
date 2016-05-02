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
#include <stdlib.h>

typedef void CITV_Characters;

#ifdef __cplusplus
extern "C" {
#endif

	CITV_Characters* itv_characters_init(size_t, size_t, size_t);
	CITV_Characters* itv_characters_init2(const char*);

	size_t itv_characters_checksum(const CITV_Characters*);
	size_t itv_characters_read(const CITV_Characters*, const char*);
	size_t itv_characters_write(const CITV_Characters*, const char*);

	void itv_characters_shuffle(const CITV_Characters*);
	int itv_characters_dump(const CITV_Characters*, char*, size_t);
	int itv_characters_encode(const CITV_Characters*, const char*, char*, size_t);
	int itv_characters_decode(const CITV_Characters*, const char*, char*, size_t);
	int itv_characters_to_string(const CITV_Characters*, char*, size_t, size_t, size_t);

	int get_utf8(size_t, char*, size_t);
	size_t get_random(size_t);

#ifdef __cplusplus
}
#endif
