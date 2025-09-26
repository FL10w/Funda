#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "operations.h"

int main(int argc, char* argv[]) {
    int status = 0;
    char* interactive_argv[10];
    char* saved_argv0 = argv[0];
    
    if (argc == 1) {
        condition(saved_argv0);
        printf("\nВведите команду: ");
        
        char input[256];
        if (fgets(input, sizeof(input), stdin) == NULL) {
            fprintf(stderr, "Ошибка чтения ввода\n");
            return 1;
        }
        
        char* tokens[10] = {NULL};
        int token_count = 0;
        char* token = strtok(input, " \t\n");
        
        while (token != NULL && token_count < 10) {
            tokens[token_count++] = token;
            token = strtok(NULL, " \t\n");
        }
        
        if (token_count == 0) {
            return 0;
        }
        
        interactive_argv[0] = saved_argv0;
        for (int i = 0; i < token_count; i++) {
            interactive_argv[i + 1] = tokens[i];
        }
        argc = token_count + 1;
        argv = interactive_argv;
    }
    
    if (argc < 2) {
        fprintf(stderr, "Ошибка: Не указан флаг\n");
        condition(saved_argv0);
        return 1;
    }
    
    char* flag = argv[1];
    
    if (strcmp(flag, "-q") == 0 || strcmp(flag, "/q") == 0) {
        if (argc != 6) {
            fprintf(stderr, "Ошибка: Для флага -q ожидается 4 аргумента после флага\n");
            fprintf(stderr, "Использование: %s -q <epsilon> <a> <b> <c>\n", saved_argv0);
            return 1;
        }
        
        if (validate_numbers(4, &argv[2]) != 0) {
            return 1;
        }
        
        double epsilon = atof(argv[2]);
        double a = atof(argv[3]);
        double b = atof(argv[4]);
        double c = atof(argv[5]);
        
        status = process_flag_q(epsilon, a, b, c);
    } 
    else if (strcmp(flag, "-m") == 0 || strcmp(flag, "/m") == 0) {
        if (argc != 4) {
            fprintf(stderr, "Ошибка: Для флага -m ожидается 2 аргумента после флага\n");
            fprintf(stderr, "Использование: %s -m <a> <b>\n", saved_argv0);
            return 1;
        }
        
        if (validate_numbers(2, &argv[2]) != 0) {
            return 1;
        }
        
        int a = atoi(argv[2]);
        int b = atoi(argv[3]);
        
        status = process_flag_m(a, b);
    } 
    else if (strcmp(flag, "-t") == 0 || strcmp(flag, "/t") == 0) {
        if (argc != 6) {
            fprintf(stderr, "Ошибка: Для флага -t ожидается 4 аргумента после флага\n");
            fprintf(stderr, "Использование: %s -t <epsilon> <a> <b> <c>\n", saved_argv0);
            return 1;
        }
        
        if (validate_numbers(4, &argv[2]) != 0) {
            return 1;
        }
        
        double epsilon = atof(argv[2]);
        double a = atof(argv[3]);
        double b = atof(argv[4]);
        double c = atof(argv[5]);
        
        status = process_flag_t(epsilon, a, b, c);
    } 
    else {
        fprintf(stderr, "Ошибка: Неизвестный флаг '%s'.\n", flag);
        condition(saved_argv0);
        return 1;
    }
    
    return status;
}