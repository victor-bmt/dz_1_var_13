#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <stdint.h>
#include <stdlib.h>

uint32_t extract_threshold(const char *str_thresh) {
	uint32_t l = strlen(str_thresh);

	if (!((str_thresh[0] >= '0') && (str_thresh[0] <= '9'))) {
		printf("Incorrect input!\nYou should enter \"./a.out (file_name) (threshold value)\". Try again.\n");
		exit(1);
	}

	uint32_t thr= str_thresh[0] - 48;

	for (int k = 1; k < l; ++k) {
		if (!((str_thresh[k] >= '0') && (str_thresh[k] <= '9'))) {
			printf("Incorrect input!\nYou should enter \"./a.out (file_name) (threshold value)\". Try again.\n");
			exit(1);
		}
		thr = thr * 10 + (str_thresh[k] - 48);
	}
	return thr;
}
