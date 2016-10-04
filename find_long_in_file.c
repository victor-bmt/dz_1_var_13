#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <stdint.h>
#include <stdlib.h>

// Функция нахождения самого длинного слова в данном файле
uint32_t find_long_in_file(const uint8_t *file_name) {
	uint32_t i = 0;
	uint32_t j = 0;
	uint32_t ch = 0;
	uint32_t max = 1;

	FILE *fp = NULL;
	fp = fopen(file_name, "r");

	while (1)
	{
		j = i + 1;
		do {
			ch = getc(fp);
			++i;

		} while ((!(isspace(ch))) && (!(ispunct(ch))) && (!(ch == EOF)));

		if ((i - j) > max)
			max = i - j;
		if (ch == EOF) {
			fclose(fp);
			return max;
		}

	}
}
