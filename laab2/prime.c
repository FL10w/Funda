#include "prime.h"
#include <math.h>

bool prime(int num) {
    double epsilon = 1e-9;
    if (num < 2) return false;
    if (num == 2) return true;
    if (num % 2 == 0) return false;
    
    int limit = (int)(sqrt(num) + epsilon);
    for (int i = 3; i <= limit; i += 2) {
        if (num % i == 0) return false;
    }
    return true;
}

int find(int n, int *status) {

    if (n <= 0) {
        *status = -1;
        return 0;
    }
    
    int count = 0;
    int candidate = 1;
    
    while (count < n) {
        candidate++;
        if (prime(candidate)) {
            count++;
        }
    }
    
    *status = 0;
    return candidate;
}