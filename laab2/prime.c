#include "prime.h"
#include <math.h>
#include <stdlib.h>
#include <stdio.h>

static int *prime_cache = NULL;
static int cache_size = 0;
static int max_cached_n = 0;

bool prime(int num) {
    if (num < 2) return false;
    if (num == 2) return true;
    if (num % 2 == 0) return false;
    
    int limit = (int)sqrt(num) + 1;
    for (int i = 3; i <= limit; i += 2) {
        if (num % i == 0) return false;
    }
    return true;
}

int estimate_prime_limit(int n) {
    if (n <= 0) return 100;
    if (n <= 10) return 100;
    
    double estimate = n * (log(n) + log(log(n)));
    int limit = (int)(estimate * 1.2) + 100;
    const int MAX_LIMIT = 10000000;
    if (limit > MAX_LIMIT) {
        return MAX_LIMIT;
    }
    return limit;
}

void init_primes_cache(int max_n) {
    if (prime_cache != NULL && max_n <= max_cached_n) {
        return;
    }
    
    if (prime_cache != NULL) {
        free(prime_cache);
    }
    
    int estimated_limit = estimate_prime_limit(max_n);
    
    bool *is_prime = (bool*)malloc((estimated_limit + 1) * sizeof(bool));
    if (is_prime == NULL) {
        printf("Ошибка: не удалось выделить память для решета\n");
        return;
    }

    for (int i = 0; i <= estimated_limit; i++) {
        is_prime[i] = true;
    }
    is_prime[0] = is_prime[1] = false;
    
    for (int i = 2; i * i <= estimated_limit; i++) {
        if (is_prime[i]) {
            for (int j = i * i; j <= estimated_limit; j += i) {
                is_prime[j] = false;
            }
        }
    }
    
    cache_size = 0;
    for (int i = 2; i <= estimated_limit; i++) {
        if (is_prime[i]) cache_size++;
    }
    
    prime_cache = (int*)malloc(cache_size * sizeof(int));
    if (prime_cache == NULL) {
        printf("Ошибка: не удалось выделить память для кэша простых чисел\n");
        free(is_prime);
        return;
    }
    
    int idx = 0;
    for (int i = 2; i <= estimated_limit; i++) {
        if (is_prime[i]) {
            prime_cache[idx++] = i;
        }
    }
    
    max_cached_n = cache_size;
    free(is_prime);
}

void cleanup_primes_cache(void) {
    if (prime_cache != NULL) {
        free(prime_cache);
        prime_cache = NULL;
    }
    cache_size = 0;
    max_cached_n = 0;
}

int find(int n, int *status) {
    if (n <= 0) {
        *status = -1;
        return 0;
    }
    
    if (n <= max_cached_n) {
        *status = 0;
        return prime_cache[n - 1];
    }
    
    int count = max_cached_n;
    int candidate = (max_cached_n > 0) ? prime_cache[count - 1] + 1 : 2;
    
    while (count < n) {
        if (prime(candidate)) {
            count++;
            if (count == n) {
                *status = 0;
                return candidate;
            }
        }
        candidate++;
    }
    
    *status = 0;
    return candidate;
}   