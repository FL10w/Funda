#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <stdbool.h>
#include <string.h>
#include "operations.h"
#include <limits.h>

void condition(const char* program_name) {
    printf("Введите число и аргумент через '-' или '/'\nАргументы:\n");
    printf("  -h  вывод в консоль натуральные числа в пределах 100 включительно, кратные x\n");
    printf("  -p  проверить, является ли число x простым; является ли x составным\n");
    printf("  -s  разделить число x на отдельные цифры системы счисления с основанием 16\n");
    printf("  -e  вывести таблицу степеней оснований от 1 до 10\n");
    printf("  -a  вычислить сумму всех натуральных чисел от 1 до x\n");
    printf("  -f  вычислить факториал x\n");
}

int bad_input(int argc, char* argv[], long* x, char* flag) {
    if (argc != 3) {
        fprintf(stderr, "Ошибка: Ожидалось 2 аргумента, получено %d\n", argc - 1);
        return 1;
    }
    
    strncpy(flag, argv[2], 2);
    flag[2] = '\0'; 
    
    char* endptr;
    *x = strtol(argv[1], &endptr, 10);
    
    if (endptr == argv[1] || *endptr != '\0') {
        fprintf(stderr, "Ошибка: '%s' не является допустимым числом.\n", argv[1]);
        return 1;
    }
    
    return 0;
}

int show(long x) {
    if (x == 0) {
        printf("Делимых чисел нет: делитель равен нулю.\n");
        return 0;
    }
    
    long abs_x = labs(x);
    if (abs_x > 100) {
        printf("Ни одно натуральное число до 100 не делится на %ld.\n", x);
        return 0;
    }
    
    bool found = false;
    printf("Числа, делящиеся на %ld до 100:\n", x);
    
    for (long i = abs_x; i <= 100; i += abs_x) {
        printf("%ld ", i);
        found = true;
    }
    
    if (!found) {
        printf("Ни одно натуральное число до 100 не делится на %ld.\n", x);
    } else {
        printf("\n");
    }
    
    return 0;
}

int check(long x) {
    if (x < 2) {
        printf("%ld не является ни простым, ни составным.\n", x);
        return 0;
    }
    
    if (x == 2) {
        printf("%ld простое.\n", x);
        return 0;
    }
    
    if (x % 2 == 0) {
        printf("%ld составное.\n", x);
        return 0;
    }
    
    bool is_prime = true;
    for (long i = 3; i * i <= x; i += 2) {
        if (x % i == 0) {
            is_prime = false;
            break;
        }
    }
    
    if (is_prime) {
        printf("%ld простое.\n", x);
    } else {
        printf("%ld составное.\n", x);
    }
    
    return 0;
}

int split(long x) {
    if (x == 0) {
        printf("0\n");
        return 0;
    }
    
    char hex_digits[16];
    int index = 0;
    long temp = labs(x);
    
    while (temp > 0) {
        int digit = temp % 16;
        hex_digits[index++] = (digit < 10) ? ('0' + digit) : ('A' + digit - 10);
        temp /= 16;
    }
    
    printf("Шестнадцатеричные цифры %ld: ", x);
    for (int i = index - 1; i >= 0; i--) {
        printf("%c ", hex_digits[i]);
    }
    printf("\n");
    
    return 0;
}

int exponent(long x) {
    if (x > 10 || x < 1) {
        fprintf(stderr, "Ошибка: для флага -e значение x должно быть в диапазоне от 1 до 10.\n");
        return 1;
    }
    
    printf("Таблица степеней для оснований 1-10 и показатели степеней 1-%ld:\n", x);

    for (long exp = 1; exp <= x; exp++) {
        printf("%8ld", exp);
    }
    printf("\n");
    
    for (long base = 1; base <= 10; base++) {
        printf("%8ld", base);
        for (long exp = 1; exp <= x; exp++) {
            double result = pow(base, exp);
            if (result < 1e6) {
                printf("%8.0f", result);
            } else {
                printf("%8.2e", result);
            }
        }
        printf("\n");
    }
    
    return 0;
}

int summ(long x) {
    if (x < 1) {
        fprintf(stderr, "Ошибка: для флага -a x должен быть положительным натуральным числом.\n");
        return 1;  
    }
    
    if (x > 0 && (unsigned long long)x > (ULLONG_MAX - 1) / 2) {
        fprintf(stderr, "Ошибка: сумма слишком велика для вычисления.\n");
        return 1;
    }
    
    unsigned long long sum = (unsigned long long)x * (x + 1) / 2;
    printf("Сумма натуральных чисел от 1 до %ld: %llu\n", x, sum);
    return 0;
}

int factorial(long x) {
    if (x < 0) {
        fprintf(stderr, "Ошибка: факториал не определен для отрицательных чисел.\n");
        return 1;
    }
    
    if (x == 0) {
        printf("Факториал 0: 1\n");
        return 0;
    }
    
    unsigned long long factorial = 1;
    
    for (long i = 1; i <= x; i++) {
        if (factorial > ULLONG_MAX / i) {
            fprintf(stderr, "Ошибка: факториал %ld слишком велик для вычисления.\n", x);
            return 1;
        }
        factorial *= i;
    }
    
    printf("Факториал %ld: %llu\n", x, factorial);
    return 0;
}