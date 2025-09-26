#include <stdio.h>
#include <stdlib.h>
#include "prime.h"

int main() {
    int T;
    
    printf("Введите количество запросов: ");
    if (scanf("%d", &T) != 1 || T <= 0) {
        printf("Ошибка: количество запросов должно быть положительным числом\n");
        return 1;
    }
    
    int *results = (int*)malloc(T * sizeof(int));
    if (results == NULL) {
        printf("Ошибка выделения памяти\n");
        return 1;
    }
    
    printf("Введите %d номеров простых чисел (по одному в строке):\n", T);
    for (int i = 0; i < T; i++) {
        int n;
        printf("Запрос %d: ", i + 1);
        if (scanf("%d", &n) != 1 || n <= 0) {
            printf("Ошибка: номер должен быть положительным числом\n");
            free(results);
            return 1;
        }
        
        int status;
        results[i] = find(n, &status);
        
        if (status != 0) {
            printf("Ошибка обработки запроса\n");
            free(results);
            return 1;
        }
    }
    
    printf("\nРезультаты:\n");
    for (int i = 0; i < T; i++) {
        printf("%d\n", results[i]);
    }
    
    free(results);
    return 0;
}