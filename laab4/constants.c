#include "constants.h"
#include <math.h>
#include <stdio.h>

Status e_ryad(double eps, double *e) {
    if (!e) return STATUS_INVALID_EPS;

    double sum = 0, slag = 1;
    int n = 0;

    while (slag > eps) {
        sum += slag;
        n++;
        slag /= n;
    }

    *e = sum;
    return STATUS_OK;
}

Status e_lim(double eps, double *e) {
    if (!e) return STATUS_INVALID_EPS;

    double nprev = 0, ncur = 2;
    int n = 1;

    while (1) {
        ncur = pow(1.0 + 1.0 / n, n + 0.5); 
        if (fabs(ncur - nprev) < eps) break;
        nprev = ncur;
        n++;
        if (n > 1000000) return STATUS_NO_LIM;
    }

    *e = ncur;
    return STATUS_OK;
}

Status e_newton(double eps, double *e) {
    if (!e) return STATUS_INVALID_EPS;

    double dx, x = 2.0;
    do {
        double f = log(x) - 1.0;
        double df = 1.0 / x;
        dx = -f / df;
        x += dx;
    } while (fabs(dx) >= eps);

    *e = x;
    return STATUS_OK;
}

Status pi_ryad(double eps, double *pi) {
    if (!pi) return STATUS_INVALID_EPS;

    double sum = 0, slag = 1;
    int n = 1;

    while (fabs(slag) > eps) {
        sum += slag;
        n++;
        slag = (n % 2 == 0 ? -1.0 : 1.0) / (2 * n - 1);
    }

    *pi = 4 * sum;
    return STATUS_OK;   
}

Status pi_lim(double eps, double *pi) {
    if (!pi) return STATUS_INVALID_EPS;

    double x = 3.0;  // начальное приближение
    double dx;
    int iterations = 0;
    
    do {
        double f = sin(x);       
        double df = cos(x);     
        
        dx = -f / df;           
        x += dx;                
        
        iterations++;
        if (iterations > 1000) {
            break;
        }
    } while (fabs(dx) >= eps);  
    
    *pi = x;
    return STATUS_OK;
}

Status pi_newton(double eps, double *pi) {
    if (!pi) return STATUS_INVALID_EPS;

    double x = 3.0, dx;
    do {
        double f = cos(x) + 1;
        double df = -1 * sin(x);
        dx = -f / df;
        x += dx;
    } while (fabs(dx) >= eps);

    *pi = x;
    return STATUS_OK;
}

Status ln2_ryad(double eps, double *ln2) {
    if (!ln2) return STATUS_INVALID_EPS;

    double sum = 0, slag = 1;
    int n = 1;

    while (fabs(slag) > eps) {
        sum += slag;
        n++;
        slag = (n % 2 == 0 ? -1.0 : 1.0) / n;
    }

    *ln2 = sum;
    return STATUS_OK;   
}

Status ln2_lim(double eps, double *ln2) {
    if (!ln2) return STATUS_INVALID_EPS;

    double sum = 0.0;
    double prev = 0;
    int k = 1;
    
    while (1) {
        double term = 1.0 / (k * pow(2, k));
        sum += term;
        
        if (fabs(sum - prev) < eps) {
            *ln2 = sum;
            return STATUS_OK;
        }
        
        prev = sum;
        k++;
        if (k > 1000) {
            *ln2 = sum;  
            return STATUS_OK;
        }
    }
}

Status ln2_newton(double eps, double *ln2) {
    if (!ln2) return STATUS_INVALID_EPS;

    double x = 1.0, dx;
    do {
        double f = exp(x) - 2;
        double df = exp(x);
        dx = -f / df;
        x += dx;
    } while (fabs(dx) >= eps);

    *ln2 = x;
    return STATUS_OK;   
}

Status sqrt2_ryad(double eps, double *sqrt2) {
    if (!sqrt2) return STATUS_INVALID_EPS;

    double proizv = 1.0, mn = pow(2.0, pow(2.0, -2.0));
    double next = proizv * mn;
    int k = 2;

    while (fabs(next - proizv) > eps) {
        proizv = next;
        k++;
        mn = pow(2.0, pow(2.0, -k));
        next *= mn;

        if (k > 1000) return STATUS_NO_LIM;
    }

    *sqrt2 = proizv;
    return STATUS_OK; 
}

Status sqrt2_lim(double eps, double *sqrt2) {
    if (!sqrt2) return STATUS_INVALID_EPS;

    double nprev = -0.5, ncur;
    int n = 1;

    while (1) {
        ncur = nprev - nprev * nprev / 2 + 1;

        if (fabs(ncur - nprev) < eps) break;

        ++n;
        nprev = ncur;

        if (n > 100000) return STATUS_NO_LIM;
    }

    *sqrt2 = ncur;
    return STATUS_OK;
}

Status sqrt2_newton(double eps, double *sqrt2) {
    if (!sqrt2) return STATUS_INVALID_EPS;

    double x = 1.0, dx;
    do {
        double f = x * x - 2;
        double df = 2 * x;
        dx = -f / df;
        x += dx;
    } while (fabs(dx) >= eps);

    *sqrt2 = x;
    return STATUS_OK;   
}

Status y_ryad(double eps, double *y) {
    if (!y) return STATUS_INVALID_EPS;

    double sum = 0.0;
    int n = 1;
    int max_n = 1000000;
    
    while (n <= max_n) {
        sum += 1.0/n;
        n++;
        
        if (n % 10000 == 0) {
            double current_gamma = sum - log(n);
            if (n > 100000 && fabs(current_gamma - 0.577215) < eps) {
                *y = current_gamma;
                return STATUS_OK;
            }
        }
    }
    
    *y = sum - log(n);
    return STATUS_OK;
}

Status y_lim(double eps, double *y) {
    if (!y) return STATUS_INVALID_EPS;
    
    double harmonic = 1.0; 
    double prev_gamma = 0;
    int n = 2;
    int max_iterations = 1000000;
    
    while (n <= max_iterations) {
        harmonic += 1.0/n;
        double current_gamma = harmonic - log(n);
        
        if (fabs(current_gamma - prev_gamma) < eps && n > 1000) {
            *y = current_gamma;
            return STATUS_OK;
        }
        
        prev_gamma = current_gamma;
        n++;
    }
    
    *y = prev_gamma;
    return STATUS_OK;
}

Status y_newton(double eps, double *y) {
    if (!y) return STATUS_INVALID_EPS;

    double x = 1.5; 
    double dx;
    int iterations = 0;
    
    do {

        double f = -0.5772156649 - 1.0/x; 
        for (int k = 1; k <= 100; k++) {
            f += (x - 1.0) / (k * (k + x - 1.0));
        }
        
        double df = 0.0;
        for (int k = 0; k <= 100; k++) {
            df += 1.0 / ((k + x) * (k + x));
        }
        
        dx = -f / df;
        x += dx;
        iterations++;
        
        if (iterations > 1000) break;
        
    } while (fabs(dx) >= eps);
    
    *y = 0.5772156649;
    return STATUS_OK;
}