#ifndef PRIME_H
#define PRIME_H
#include <stdbool.h>

bool prime(int num);
int find(int n, int *status);
void init_primes_cache(int max_n);
void cleanup_primes_cache(void);

#endif