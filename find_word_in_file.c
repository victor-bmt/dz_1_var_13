#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <stdint.h>
#include <stdlib.h>

// Возвращает 0, если слово не найдено в заданном промежутке и количество предложений, в которых слово есть, если слово найдено
// !!! Для start == 0, обязательно передавать end == i - 1, num == 0
// !!! Только так программа будет универсальна для обоих случаев
uint32_t find_word_in_file(const uint8_t *word, const uint8_t *file_name, const uint32_t start, const uint32_t end, uint32_t num) {
	if (start == end)
		return 0;

	FILE *fp = fopen(file_name, "r");
	uint32_t ch = 0;
	// Флаг нахождения идентичного слова
	uint32_t flag = 1;
	
	// Счетчик пройденных символов
	uint32_t i = 0;
	for (i = 0; i <= start; ++i)
		ch = getc(fp);
	--i;
	// Переходим к следующему предложению, если ищем повторяющиеся слова
	if (start)
		while ((ch != (uint32_t)'.')
			&& (ch != (uint32_t)'!')
	       		&& (ch != (uint32_t)'?')) {
				ch = getc(fp);
				if (++i == end) {
					fclose(fp);
					return num;
				}
		}

	ch = getc(fp);
	if (++i == end) {
		fclose(fp);
		return num;
	}
	// Ищем слово, аналогичное текущему
	while(1) {
		uint32_t buf = ch;
		ch = getc(fp);
		if (++i == end) {
			fclose(fp);
			return num;
		}
	
		while (!((isspace(buf) || ispunct(buf)) && (ch == word[0]))) {
			buf = ch;
			ch = getc(fp);
			if (++i == end) {
				fclose(fp);
				return num;
			}
		}

		flag = 1;
		for (uint32_t k = 1; k < strlen(word); ++k) {
			ch = getc(fp);
			if (++i == end) {
				fclose(fp);
				return num;
			}
			if (ch != word[k]) {
				flag = 0;
				break;
			}
		}

		if (flag) {
			ch = getc(fp);
			++i;

			if ((isspace(ch)) || (ispunct(ch)) || (i == end))  {
				// Если ищем повторы перед словом (start == 0), возвращаем положительный результат
				// В случае поиска количества вхождений, используем рекурсию
				if (start) {
					fclose(fp);
					num = find_word_in_file(word, file_name, i, end, ++num);
					return num;
				}
				else {
					fclose(fp);
					return ++num;
				}
			}
		}
	}

}
