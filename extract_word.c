#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <stdint.h>
#include <stdlib.h>

// Получаем очередное слово
uint32_t extract_word(uint8_t *word, const uint8_t *file_name, uint32_t *pcount) {
	FILE *fp = NULL;
	fp = fopen(file_name, "r");
	uint32_t ch = 0;

	for (uint32_t k = 0; k <= *pcount; ++k)
		ch = getc(fp);

	uint32_t i = 0;
	while (!(isspace(ch)) && !(ispunct(ch))) {
		word[i++] = ch;
		ch = getc(fp);
		if (ch == EOF) {
			word[i] = '\0';
			fclose(fp);
			*pcount += i;
			return 0;
		}
	}
	word[i] = '\0';
	*pcount += i;
	fclose(fp);
	return 1;
}
