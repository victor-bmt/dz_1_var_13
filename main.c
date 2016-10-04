#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <stdint.h>
#include <stdlib.h>
#include "main.h"

int main(int argc, char *argv[])
{
	if (argc != 3) {
		printf("Incorrect input!\nYou should enter \"./a.out (file_name) (threshold value)\". Try again.\n");
		return 0;
	}
	// Считываем требуемое количество вхождений
	uint32_t thr = extract_threshold(argv[2]);

	uint8_t *file_name = alloca(strlen(argv[1] + 1));
	file_name = argv[1];

	// Массив для текущего слова размером равным самому длинному слову в файле
	uint32_t len = find_long_in_file(file_name) + 1;
	uint8_t *word = alloca(len);
	// Начало слова
	uint32_t count_01 = 0;
	// Позиция символа после слова
	uint32_t count_02 = 0;
	// Количество вхождений данного слова
	uint32_t num = 0;

	// Флаг конца файла
	uint32_t flag = 1;

	FILE *fp = NULL;
	fp = fopen(file_name, "r");

	// Текущий символ, считанный из файла
	uint32_t ch = getc(fp);

	// Счетчик выведенных слов
	uint32_t count_output = 0;

	if (ch == EOF) {
		printf("File is empty\n");
		fclose(fp);
		return 0;
	}

	fclose(fp);

	uint32_t number_of_symb = count_symbols(file_name);

	while(flag) {
		fp = fopen(file_name, "r");

		// count_02 - на пробеле после пройденного слова
		// переместим туда count_01, чтобы пропустить в файле обработанную часть
		count_01 = count_02;
		for (int k = 0; k <= count_01; ++k)
			ch = getc(fp);
		
		// Пропускаем пробелы и знаки препинания - переходим к следующему слову
		while (isspace(ch) || ispunct(ch)) {
			ch = getc(fp);
			++count_01;
		}

		if (ch == EOF) {
			fclose(fp);
			break;
		}

		// Устанавливаем count_02 в начало следующего слова
		// Функция extract_word будет инкрементировать count_02 до разделителя после текущего слова
		count_02 = count_01;
		fclose(fp);

		flag = extract_word(word, file_name, &count_02);
		// Проверяем, было слово или нет
		if (!find_word_in_file(word, file_name, 0, count_01 ? count_01 - 1 : 0, 0))
			// Проверяем, больше порогового значения, или нет
			if (((num = find_word_in_file(word, file_name, count_02, number_of_symb, 1)) > thr)) {
				++count_output;
				printf("Word \"%s\" repeats in %d sentence(s)\n", word, num);
			}
	}

	// Если ничего нигде не повторяется
	if (!count_output)
		printf("There are no words satisfying this conditions in this file.\n");
	return 0;
}
