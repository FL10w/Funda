#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "operations.h"

int main(int argc, char* argv[]) {
    long x;
    char flag[3];
    
    if (argc == 1) {
        condition(argv[0]);
        printf("Введите число и флаг: ");
        
        char input[32];
        if (fgets(input, sizeof(input), stdin) == NULL) {
            fprintf(stderr, "Ошибка чтения ввода\n");
            return 1;
        }
        
        char* tokens[3] = {NULL};
        int token_count = 0;
        char* token = strtok(input, " \n");
        
        while (token != NULL && token_count < 3) {
            tokens[token_count++] = token;
            token = strtok(NULL, " \n");
        }
        
        if (token_count != 2) {
            fprintf(stderr, "Ошибка: Ожидается <число> <флаг>. Получено %d аргументов.\n", token_count);
            return 1;
        }
        
        char* fake_argv[3] = {argv[0], tokens[0], tokens[1]};
        if (bad_input(3, fake_argv, &x, flag) != 0) {
            return 1;
        }
    }
    else {
        if (bad_input(argc, argv, &x, flag) != 0) {
            return 1;
        }
    }
    
    int status = 0;
    
    if (strcmp(flag, "-h") == 0 || strcmp(flag, "/h") == 0) {
        status = show(x);
    }
    else if (strcmp(flag, "-p") == 0 || strcmp(flag, "/p") == 0) {
        status = check(x);
    }
    else if (strcmp(flag, "-s") == 0 || strcmp(flag, "/s") == 0) {
        status = split(x);
    }
    else if (strcmp(flag, "-e") == 0 || strcmp(flag, "/e") == 0) {
        status = exponent(x);
    }
    else if (strcmp(flag, "-a") == 0 || strcmp(flag, "/a") == 0) {
        status = summ(x);
    }
    else if (strcmp(flag, "-f") == 0 || strcmp(flag, "/f") == 0) {
        status = factorial(x);
    }
    else {
        fprintf(stderr, "Ошибка: Неизвестный флаг '%s'.\n", flag);
        return 1;
    }
    
    if (status != 0) {
        fprintf(stderr, "Ошибка: Операция не выполнена с кодом %d\n", status);
        return 1;
    }
    
    return 0;
}