#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "file_processor.h"

int main(int argc, char *argv[]) {
    if (argc < 2) {
        printf("Использование: %s <флаг> <входной_файл> [выходной_файл]\n", argv[0]);
        printf("Флаги: -d, -i, -s, -a (с опциональным 'n' для явного указания выходного файла)\n");
        return 1;
    }

    const char *flag = argv[1];
    if ((flag[0] != '-' && flag[0] != '/') || strlen(flag) < 2) {
        printf("Ошибка: Неверный формат флага. Используйте '-' или '/' followed by one letter.\n");
        return 1;
    }

    char operation;
    
    int has_n = (strlen(flag) == 3 && flag[1] == 'n');
    
    if (has_n) {
        operation = flag[2];
    } else {
        operation = flag[1];  
    }

    if (operation != 'd' && operation != 'i' && operation != 's' && operation != 'a') {
        printf("Ошибка: Неверная операция. Используйте d, i, s или a.\n");
        return 1;
    }

    const char *input_file;
    const char *output_file = NULL;
    char *generated_name = NULL;
    
    if (has_n) {
        if (argc < 4) {
            printf("Ошибка: Для флага с 'n' требуется указать выходной файл.\n");
            return 1;
        }
        input_file = argv[2];      // Входной файл - второй аргумент
        output_file = argv[3];     // Выходной файл - третий аргумент
    } else {
        // Для обычных флагов выходной файл генерируется автоматически
        if (argc < 3) {
            printf("Ошибка: Требуется указать входной файл.\n");
            return 1;
        }
        input_file = argv[2];      
        
        // Генерация имени выходного файла путем добавления префикса "out_"
        const char *base_name = strrchr(input_file, '/');
        if (base_name == NULL) {
            base_name = strrchr(input_file, '\\'); 
        }
        if (base_name == NULL) {
            base_name = input_file;  
        } else {
            base_name++; 
        }
        
        // Выделяем память для сгенерированного имени
        size_t name_length = strlen(base_name) + 5; //для "out_" и терминатора
        generated_name = (char *)malloc(name_length);
        if (generated_name == NULL) {
            printf("Ошибка: Не удалось выделить память.\n");
            return 1;
        }
        snprintf(generated_name, name_length, "out_%s", base_name);
        output_file = generated_name;
    }

    printf("Обработка: входной='%s', выходной='%s', операция='%c'\n", 
           input_file, output_file, operation);

    ProcessResult result = process_file(input_file, output_file, operation);
    
    // Освобождаем память если выделяли для имени выходного файла
    if (generated_name != NULL) {
        free(generated_name);
    }

    switch (result) {
        case PROCESS_SUCCESS:
            printf("Файл успешно обработан.\n");
            return 0;
        case PROCESS_ERROR_OPEN_INPUT:
            printf("Ошибка: Не удалось открыть входной файл.\n");
            return 1;
        case PROCESS_ERROR_OPEN_OUTPUT:
            printf("Ошибка: Не удалось открыть выходной файл.\n");
            return 1;
        case PROCESS_ERROR_MEMORY:
            printf("Ошибка: Не удалось выделить память\n");
            return 1;
        case PROCESS_ERROR_INVALID_OPERATION:
            printf("Ошибка: Неверная операция\n");
            return 1;
        default:
            printf("Ошибка: Произошла неизвестная ошибка\n");
            return 1;
    }
}