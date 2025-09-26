#include <stdio.h>
#include <assert.h>
#include "prime.h"

void test() {
    int status;
    
    int test_cases[][2] = {
        {1, 2}, {2, 3}, {3, 5}, {4, 7}, {5, 11},
        {10, 29}, {25, 97}, {50, 229}, {100, 541}
    };
    
    size_t num_cases = sizeof(test_cases) / sizeof(test_cases[0]);
    for (size_t i = 0; i < num_cases; i++) {
        int n = test_cases[i][0];
        int expected = test_cases[i][1];
        int result = find(n, &status);
        
        assert(status == 0);
        assert(result == expected);
        assert(prime(result) == true);
    }
    
    printf("тест пройден\n");
}

int main() {
    printf("Начало тестирования:\n");
    test();
    printf("Тесты закончились\n");
    return 0;
}