#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "itv_wrapper.h"

#define MAX_KEY_LENGTH 255*3+1

int main() {
	char *data = "!\"#$%&'()*+,-./0123456789:;<=>?@ABCDEFGHIJKLMNOPQRSTUVWXYZ[\\]^_`abcdefghijklmnopqrstuvwxyz{|}~";
	char *msg = "a quick brown fox jumps over the lazy dog.";
	char *buf = NULL, *key = NULL, *enc = NULL, *dec = NULL;

	CITV_ASCII *itv = itv_ascii_new();
	itv_ascii_load(itv, 97, 122);

	buf = malloc(strlen(data) * 2 + 1);
	itv_ascii_encode(itv, data, buf);
	printf("BUF: %s\n", buf);
	free(buf);

	key = malloc(MAX_KEY_LENGTH);
	itv_ascii_dump(itv, ':', key);
	printf("KEY: %s\n", key);

	enc = malloc(strlen(msg) * 2 + 1);
	itv_ascii_encode(itv, msg, enc);
	printf("MSG: %s\nENC: %s\n", msg, enc);

	free(itv);
	itv = NULL;

	itv = itv_ascii_init(key);
	free(key);

	dec = malloc(strlen(enc) * 2 + 1);
	itv_ascii_decode(itv, enc, dec);
	printf("DEC: %s\n", dec);

	free(enc);
	free(dec);

	return 0;
}

