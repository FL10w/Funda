#include "func.h"
#include <ctype.h>
#include <math.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdarg.h>

// Все вспомогательные функции остаются без изменений...
char * func_Ro(int num) {
    if (num <= 0 || num > 3999) {
        char* error = malloc(6);
        strcpy(error, "ERROR");
        return error;
    }
    
    char* result = malloc(16);
    int pos = 0;
    
    struct {
        int value;
        char* numeral;
    } roman[] = {
        {1000, "M"}, {900, "CM"}, {500, "D"}, {400, "CD"},
        {100, "C"}, {90, "XC"}, {50, "L"}, {40, "XL"},
        {10, "X"}, {9, "IX"}, {5, "V"}, {4, "IV"}, {1, "I"}
    };
    
    for (int j = 0; j < 13; j++) {
        while (num >= roman[j].value) {
            char* numeral = roman[j].numeral;
            while (*numeral) {
                result[pos++] = *numeral++;
            }
            num -= roman[j].value;
        }
    }
    result[pos] = '\0';
    return result;
}

char * func_Zr(unsigned int num) {
    if (num == 0) {
        char* result = malloc(3);
        strcpy(result, "01");
        return result;
    }
    if (num == 1) {
        char* result = malloc(3);
        strcpy(result, "11");
        return result;
    }
    
    // Generate Fibonacci numbers up to num
    unsigned int fib[100];
    fib[0] = 1;
    fib[1] = 2;
    int len = 2;
    
    for (int i = 2; i < 100; i++) {
        fib[i] = fib[i-1] + fib[i-2];
        if (fib[i] > num || fib[i] < fib[i-1]) break;
        len++;
    }
    
    // Build representation from highest to lowest
    char* repr = calloc(len + 3, 1);
    int idx = 0;
    unsigned int n = num;
    
    // Start from the largest Fibonacci number <= num
    for (int i = len - 1; i >= 0; i--) {
        if (n >= fib[i]) {
            repr[idx++] = '1';
            n -= fib[i];
            // Skip the next Fibonacci number to avoid consecutive 1s
            if (i > 0) i--;
        } else {
            if (idx > 0) { // Only add zeros after we started
                repr[idx++] = '0';
            }
        }
    }
    
    // Add final 1 (Zeckendorf representation always ends with 1)
    if (idx == 0 || repr[idx-1] != '1') {
        repr[idx++] = '1';
    }
    repr[idx] = '\0';
    
    return repr;
}

char * func_Cv(int num, int base) {
    if (base < 2 || base > 36) base = 10;
    
    if (num == 0) {
        char* result = malloc(2);
        strcpy(result, "0");
        return result;
    }
    
    char digits[] = "0123456789abcdefghijklmnopqrstuvwxyz";
    char* result = calloc(65, 1);
    
    int is_negative = 0;
    unsigned int n;
    
    if (num < 0) {
        is_negative = 1;
        n = -num;
    } else {
        n = num;
    }
    
    // Convert to string in reverse order
    char buffer[65];
    int i = 0;
    
    while (n > 0) {
        buffer[i++] = digits[n % base];
        n /= base;
    }
    
    // Add minus sign if negative
    if (is_negative) {
        buffer[i++] = '-';
    }
    
    // Reverse the string
    int pos = 0;
    for (int j = i - 1; j >= 0; j--) {
        result[pos++] = buffer[j];
    }
    result[pos] = '\0';
    
    return result;
}

char * func_CV(int num, int base) {
    char* result = func_Cv(num, base);
    for (int i = 0; result[i] != '\0'; i++) {
        result[i] = toupper(result[i]);
    }
    return result;
}

int func_to(const char *num, int base) {
    if (base < 2 || base > 36) base = 10;
    if (num == NULL || *num == '\0') return 0;
    
    int result = 0;
    const char* digits = "0123456789abcdefghijklmnopqrstuvwxyz";
    
    for (int i = 0; num[i] != '\0'; i++) {
        char c = tolower(num[i]);
        const char* pos = strchr(digits, c);
        if (pos == NULL) return -1;
        
        int digit = pos - digits;
        if (digit >= base) return -1;
        
        result = result * base + digit;
    }
    return result;
}

int func_TO(const char *num, int base) {
    if (base < 2 || base > 36) base = 10;
    if (num == NULL || *num == '\0') return 0;
    
    // Check that all letters are uppercase
    for (int i = 0; num[i] != '\0'; i++) {
        if (islower(num[i])) return -1;
    }
    
    // Convert to lowercase and process
    char* temp = malloc(strlen(num) + 1);
    strcpy(temp, num);
    for (int i = 0; temp[i] != '\0'; i++) {
        temp[i] = tolower(temp[i]);
    }
    
    int result = func_to(temp, base);
    free(temp);
    return result;
}

char * func_mi(int num) {
    unsigned char* bytes = (unsigned char*)&num;
    char* result = malloc(36);
    int pos = 0;
    
    for (int i = 0; i < 4; i++) {
        for (int j = 7; j >= 0; j--) {
            result[pos++] = (bytes[i] >> j) & 1 ? '1' : '0';
        }
        if (i < 3) result[pos++] = ' ';
    }
    result[pos] = '\0';
    return result;
}

char * func_mu(unsigned int num) {
    unsigned char* bytes = (unsigned char*)&num;
    char* result = malloc(36);
    int pos = 0;
    
    for (int i = 0; i < 4; i++) {
        for (int j = 7; j >= 0; j--) {
            result[pos++] = (bytes[i] >> j) & 1 ? '1' : '0';
        }
        if (i < 3) result[pos++] = ' ';
    }
    result[pos] = '\0';
    return result;
}

char * func_md(double num) {
    unsigned char* bytes = (unsigned char*)&num;
    char* result = malloc(72);
    int pos = 0;
    
    for (int i = 0; i < 8; i++) {
        for (int j = 7; j >= 0; j--) {
            result[pos++] = (bytes[i] >> j) & 1 ? '1' : '0';
        }
        if (i < 7) result[pos++] = ' ';
    }
    result[pos] = '\0';
    return result;
}

char * func_mf(float num) {
    unsigned char* bytes = (unsigned char*)&num;
    char* result = malloc(36);
    int pos = 0;
    
    for (int i = 0; i < 4; i++) {
        for (int j = 7; j >= 0; j--) {
            result[pos++] = (bytes[i] >> j) & 1 ? '1' : '0';
        }
        if (i < 3) result[pos++] = ' ';
    }
    result[pos] = '\0';
    return result;
}

int over(char *str, const char *format, va_list args) {
    char buffer[2048] = {0};
    int buf_pos = 0;
    
    // Создаем копию va_list для безопасного использования
    va_list args_copy;
    va_copy(args_copy, args);
    
    for (int i = 0; format[i] != '\0'; i++) {
        if (format[i] == '%') {
            // Check for 3-character special formats
            if (format[i+1] == 'R' && format[i+2] == 'o') {
                int val = va_arg(args_copy, int);
                char* res = func_Ro(val);
                strcpy(buffer + buf_pos, res);
                buf_pos += strlen(res);
                free(res);
                i += 2;
            }
            else if (format[i+1] == 'Z' && format[i+2] == 'r') {
                unsigned int val = va_arg(args_copy, unsigned int);
                char* res = func_Zr(val);
                strcpy(buffer + buf_pos, res);
                buf_pos += strlen(res);
                free(res);
                i += 2;
            }
            else if (format[i+1] == 'C' && format[i+2] == 'v') {
                int val = va_arg(args_copy, int);
                int base = va_arg(args_copy, int);
                char* res = func_Cv(val, base);
                strcpy(buffer + buf_pos, res);
                buf_pos += strlen(res);
                free(res);
                i += 2;
            }
            else if (format[i+1] == 'C' && format[i+2] == 'V') {
                int val = va_arg(args_copy, int);
                int base = va_arg(args_copy, int);
                char* res = func_CV(val, base);
                strcpy(buffer + buf_pos, res);
                buf_pos += strlen(res);
                free(res);
                i += 2;
            }
            else if (format[i+1] == 't' && format[i+2] == 'o') {
                char* str_val = va_arg(args_copy, char*);
                int base = va_arg(args_copy, int);
                int val = func_to(str_val, base);
                buf_pos += sprintf(buffer + buf_pos, "%d", val);
                i += 2;
            }
            else if (format[i+1] == 'T' && format[i+2] == 'O') {
                char* str_val = va_arg(args_copy, char*);
                int base = va_arg(args_copy, int);
                int val = func_TO(str_val, base);
                buf_pos += sprintf(buffer + buf_pos, "%d", val);
                i += 2;
            }
            else if (format[i+1] == 'm' && format[i+2] == 'i') {
                int val = va_arg(args_copy, int);
                char* res = func_mi(val);
                strcpy(buffer + buf_pos, res);
                buf_pos += strlen(res);
                free(res);
                i += 2;
            }
            else if (format[i+1] == 'm' && format[i+2] == 'u') {
                unsigned int val = va_arg(args_copy, unsigned int);
                char* res = func_mu(val);
                strcpy(buffer + buf_pos, res);
                buf_pos += strlen(res);
                free(res);
                i += 2;
            }
            else if (format[i+1] == 'm' && format[i+2] == 'd') {
                double val = va_arg(args_copy, double);
                char* res = func_md(val);
                strcpy(buffer + buf_pos, res);
                buf_pos += strlen(res);
                free(res);
                i += 2;
            }
            else if (format[i+1] == 'm' && format[i+2] == 'f') {
                double val = va_arg(args_copy, double);
                float float_val = (float)val;
                char* res = func_mf(float_val);
                strcpy(buffer + buf_pos, res);
                buf_pos += strlen(res);
                free(res);
                i += 2;
            }
            else {
                // Handle standard 2-character formats
                switch (format[i+1]) {
                    case 'd': case 'i': {
                        int val = va_arg(args_copy, int);
                        buf_pos += sprintf(buffer + buf_pos, "%d", val);
                        i++;
                        break;
                    }
                    case 'u': {
                        unsigned int val = va_arg(args_copy, unsigned int);
                        buf_pos += sprintf(buffer + buf_pos, "%u", val);
                        i++;
                        break;
                    }
                    case 'f': {
                        double val = va_arg(args_copy, double);
                        buf_pos += sprintf(buffer + buf_pos, "%f", val);
                        i++;
                        break;
                    }
                    case 's': {
                        char* val = va_arg(args_copy, char*);
                        buf_pos += sprintf(buffer + buf_pos, "%s", val);
                        i++;
                        break;
                    }
                    case 'c': {
                        int val = va_arg(args_copy, int);
                        buffer[buf_pos++] = (char)val;
                        i++;
                        break;
                    }
                    case '%': {
                        buffer[buf_pos++] = '%';
                        i++;
                        break;
                    }
                    default:
                        // Unknown format, copy as-is
                        buffer[buf_pos++] = format[i];
                }
            }
        } else {
            buffer[buf_pos++] = format[i];
        }
    }
    
    buffer[buf_pos] = '\0';
    strcpy(str, buffer);
    va_end(args_copy);
    return buf_pos;
}

int oversprintf(char *str, const char *format, ...) {
    va_list args;
    va_start(args, format);
    int result = over(str, format, args);
    va_end(args);
    return result;
}

int overfprintf(FILE *stream, const char *format, ...) {
    va_list args;
    va_start(args, format);
    
    char buffer[2048];
    int len = over(buffer, format, args);
    va_end(args);
    
    fputs(buffer, stream);
    return len;
}