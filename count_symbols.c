#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <stdint.h>
#include <stdlib.h>

uint32_t count_symbols(const uint8_t *file_name) {
	FILE *fp = NULL;
	fp = fopen(file_name, "r");
	uint32_t flag = 0;
	uint32_t ch = getc(fp);

	uint32_t i = 0;
	for (i = 0; ch!= EOF; ++i) {
		ch = getc(fp);
		if (isspace(ch) || ispunct(ch))
			flag = 1;
	}

	fclose(fp);

	if (!flag) {
		printf("This file includes only one word\n");
		exit(1);
	}

	// printf("Всего символов в файле : %d\n", i);
	return i;
}
