// Функция подсчета количества символов в файле
uint32_t count_symbols(const uint8_t *file_name);
// Ищет слово word в файле file_name в промежутке между start и end
uint32_t find_word_in_file(const uint8_t *word, const uint8_t *file_name, const uint32_t start, const uint32_t end, uint32_t num);
// Функция нахождения самого длинного слова в файле
uint32_t find_long_in_file(const uint8_t *file_name);
// Функция получения очередного слова
uint32_t extract_word(uint8_t *word, const uint8_t *file_name, uint32_t *pcount);
// Получаем пороговое значение, переданное командной строкой
uint32_t extract_threshold(const char *str_thresh);
