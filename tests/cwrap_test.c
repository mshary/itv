#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "itv_wrapper.h"

int main() {
	char msg[] = "أزمة اليمن: الحوثيون يتقدمون في عدن رغم الغارات الجوية";
	char key[4096];
	char enc[sizeof(msg)*2];
	char dec[sizeof(msg)];

	CITV_Characters *itv = itv_characters_init(0x100, 0x600, 0x6FF - 0x600);

	/* randomly shuffle IDs */
	itv_characters_shuffle(itv);

	itv_characters_dump(itv, key, sizeof(key));
	/* printf("KEY: %s\n", key); */

	itv_characters_encode(itv, msg, enc, sizeof(enc));
	printf("MSG: %s\nENC: %s\n", msg, enc);

	free(itv);
	itv = NULL;

	itv = itv_characters_init2(key);
	itv_characters_decode(itv, enc, dec, sizeof(dec));
	printf("DEC: %s\nRandom: %lu\n", dec, (unsigned long)get_random(0x6FF - 0x600));

	free(itv);
	itv = NULL;

	printf("\n");
	return 0;
}

