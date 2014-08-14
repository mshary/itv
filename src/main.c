#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "itv_wrapper.h"

#define MAX_KEY_LEN		255*3+1

int main() {
	char *data = "!\"#$%&'()*+,-./0123456789:;<=>?@ABCDEFGHIJKLMNOPQRSTUVWXYZ[\\]^_`abcdefghijklmnopqrstuvwxyz{|}~";
	char *msg = "a quick brown fox jumps over the lazy dog.";
	char *buf = NULL, *key = NULL, *enc = NULL, *dec = NULL;

	CITV_ASCII *itv = itv_ascii_new();
	CITV_Words *words = itv_words_init("./wordsEn.txt", 0);

	itv_ascii_load(itv, 97, 122);
	buf = (char*) itv_ascii_encode(itv, data);
	printf("BUF: %s\n", buf);

	key = (char*) itv_ascii_dump(itv, ':');
	printf("KEY: %s\n", key);

	enc = (char*) itv_ascii_encode(itv, msg);
	printf("MSG: %s\nENC: %s\n", msg, enc);

	free(itv);
	itv = NULL;

	itv = itv_ascii_init(key);
	dec = (char*) itv_ascii_decode(itv, enc);
	printf("DEC: %s\n", dec);

	free(itv);
	itv = NULL;

	printf("\n");

	enc = (char*) itv_words_encode(words, msg);
	printf("MSG: %s\nENC: %s\n", msg, enc);

	free(words);
	words = NULL;

	words = itv_words_init("./wordsEn.txt", 0);

	dec = (char*) itv_words_decode(words, enc);
	printf("DEC: %s\n", dec);

	free(words);
	words = NULL;

	printf("\n");

	free(key);
	free(enc);
	free(dec);

	return 0;
}

