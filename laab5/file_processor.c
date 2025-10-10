#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "file_processor.h"

// Буфер для чтения строк
#define BUFFER_SIZE 1024

ProcessResult process_file(const char *input_filename, const char *output_filename, char operation) {
    switch (operation) {
        case 'd':  // Удалить цифры
            return remove_digits(input_filename, output_filename);
        case 'i':  // Посчитать буквы
            return count_letters_per_line(input_filename, output_filename);
        case 's':  // Посчитать специальные символы
            return count_special_chars_per_line(input_filename, output_filename);
        case 'a':  // Заменить не-цифры на HEX
            return replace_non_digits_with_hex(input_filename, output_filename);
        default:
            return PROCESS_ERROR_INVALID_OPERATION;
    }
}

ProcessResult remove_digits(const char *input_filename, const char *output_filename) {
    FILE *input = fopen(input_filename, "r");
    if (input == NULL) {
        return PROCESS_ERROR_OPEN_INPUT;
    }

    FILE *output = fopen(output_filename, "w");
    if (output == NULL) {
        fclose(input);
        return PROCESS_ERROR_OPEN_OUTPUT;
    }

    char buffer[BUFFER_SIZE];
    
    while (fgets(buffer, BUFFER_SIZE, input) != NULL) {
        size_t len = strlen(buffer);
        for (size_t i = 0; i < len; i++) {
            if (!is_arabic_digit(buffer[i])) {
                fputc(buffer[i], output);
            }
        }
    }

    fclose(input);
    fclose(output);
    return PROCESS_SUCCESS;
}

ProcessResult count_letters_per_line(const char *input_filename, const char *output_filename) {
    FILE *input = fopen(input_filename, "r");
    if (input == NULL) {
        return PROCESS_ERROR_OPEN_INPUT;
    }

    FILE *output = fopen(output_filename, "w");
    if (output == NULL) {
        fclose(input);
        return PROCESS_ERROR_OPEN_OUTPUT;
    }

    char buffer[BUFFER_SIZE];
    
    while (fgets(buffer, BUFFER_SIZE, input) != NULL) {
        int count = 0;
        size_t len = strlen(buffer);
        for (size_t i = 0; i < len; i++) {
            if (is_latin_letter(buffer[i])) {
                count++;
            }
        }
        // Записываем количество букв для каждой строки
        fprintf(output, "%d\n", count);
    }

    fclose(input);
    fclose(output);
    return PROCESS_SUCCESS;
}

ProcessResult count_special_chars_per_line(const char *input_filename, const char *output_filename) {
    FILE *input = fopen(input_filename, "r");
    if (input == NULL) {
        return PROCESS_ERROR_OPEN_INPUT;
    }

    FILE *output = fopen(output_filename, "w");
    if (output == NULL) {
        fclose(input);
        return PROCESS_ERROR_OPEN_OUTPUT;
    }

    char buffer[BUFFER_SIZE];
    
    while (fgets(buffer, BUFFER_SIZE, input) != NULL) {
        int count = 0;
        size_t len = strlen(buffer);
        for (size_t i = 0; i < len; i++) {
            char c = buffer[i];
            // Считаем символы, которые НЕ являются: буквами, цифрами, пробелами, переводом строки
            if (!is_latin_letter(c) && !is_arabic_digit(c) && !is_space(c) && c != '\n' && c != '\r') {
                count++;
            }
        }
        fprintf(output, "%d\n", count);
    }

    fclose(input);
    fclose(output);
    return PROCESS_SUCCESS;
}

ProcessResult replace_non_digits_with_hex(const char *input_filename, const char *output_filename) {
    FILE *input = fopen(input_filename, "r");
    if (input == NULL) {
        return PROCESS_ERROR_OPEN_INPUT;
    }

    FILE *output = fopen(output_filename, "w");
    if (output == NULL) {
        fclose(input);
        return PROCESS_ERROR_OPEN_OUTPUT;
    }

    char buffer[BUFFER_SIZE];
    
    while (fgets(buffer, BUFFER_SIZE, input) != NULL) {
        size_t len = strlen(buffer);
        for (size_t i = 0; i < len; i++) {
            char c = buffer[i];
            if (is_arabic_digit(c)) {
                // Цифры записываем как есть
                fputc(c, output);
            } else if (c == ' ') {
                // ПРОБЕЛЫ оставляем как есть
                fputc(c, output);
            } else if (c == '\t' || c == '\n' || c == '\r') {
                // Табы и переводы строк также оставляем как есть
                fputc(c, output);
            } else {
                // Остальные символы заменяем на HEX код
                fprintf(output, "%02X", (unsigned char)c);
            }
        }
    }

    fclose(input);
    fclose(output);
    return PROCESS_SUCCESS;
}

int is_latin_letter(char c) {
    return (c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z');
}

int is_arabic_digit(char c) {
    return c >= '0' && c <= '9';
}

int is_space(char c) {
    return c == ' ' || c == '\t';
}