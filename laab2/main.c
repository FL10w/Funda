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
    
    int *queries = (int*)malloc(T * sizeof(int));
    if (queries == NULL) {
        printf("Ошибка выделения памяти\n");
        return 1;
    }
    
    printf("Введите %d номеров простых чисел (по одному в строке):\n", T);
    int max_query = 0;
    for (int i = 0; i < T; i++) {
        printf("Запрос %d: ", i + 1);
        if (scanf("%d", &queries[i]) != 1 || queries[i] <= 0) {
            printf("Ошибка: номер должен быть положительным числом\n");
            free(queries);
            return 1;
        }
        if (queries[i] > max_query) {
            max_query = queries[i];
        }
    }
    
    init_primes_cache(max_query);
    
    int *results = (int*)malloc(T * sizeof(int));
    if (results == NULL) {
        printf("Ошибка выделения памяти\n");
        free(queries);
        cleanup_primes_cache();
        return 1;
    }
    
    for (int i = 0; i < T; i++) {
        int status;
        results[i] = find(queries[i], &status);
        
        if (status != 0) {
            printf("Ошибка обработки запроса\n");
            free(queries);
            free(results);
            cleanup_primes_cache();
            return 1;
        }
    }
    
    printf("\nРезультаты:\n");
    for (int i = 0; i < T; i++) {
        printf("%d\n", results[i]);
    }
    
    free(queries);
    free(results);
    cleanup_primes_cache();
    
    return 0;
}