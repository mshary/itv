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
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "itv_wrapper.h"

int main() {
	char msg[] = "أزمة اليمن: الحوثيون يتقدمون في عدن رغم الغارات الجوية";
	size_t sender_checksum, receiver_checksum, len = 0x6FF - 0x600;
	char key[(len + 1) * 8];
	char enc[(strlen(msg) + 1) * 8];
	char dec[(strlen(msg) + 1) * 4];

	CITV_Characters *itv = itv_characters_init(0xd00, 0x600, len);
	len += itv_characters_load(itv, 32, 32, 1);

	/* randomly shuffle IDs */
	itv_characters_shuffle(itv);

	itv_characters_dump(itv, key, sizeof(key));
	printf("KEY: %s\n", key);

	sender_checksum = itv_characters_checksum(itv);

	itv_characters_encode(itv, msg, enc, sizeof(enc));
	printf("MSG: %s\nENC: %s\nCS: 0x%zx\n", msg, enc, sender_checksum);

	free(itv);
	itv = NULL;

	itv = itv_characters_init2(key);
	receiver_checksum = itv_characters_checksum(itv);

	if (sender_checksum == receiver_checksum) {
		itv_characters_decode(itv, enc, dec, sizeof(dec));
		printf("DEC: %s\nRandom: 0x%zx\nCS: 0x%zx\n", dec, get_random(len), receiver_checksum);
	} else {
		printf("Failure: checksum mismatch, 0x%zx != 0x%zx", sender_checksum, receiver_checksum);
	};

	free(itv);
	itv = NULL;

	printf("\n");
	return 0;
}

