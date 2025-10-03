#include <stdio.h>
#include "constants.h"

int main() {
    printf("Выберите константу: 1 - e; 2 - pi; 3 - ln2; 4 - sqrt(2); 5 - γ\n");
    
    int x;
    if (scanf("%d", &x) != 1 || x < 1 || x > 5) {
        printf("Введите число от 1 до 5\n");
        return STATUS_INVALID_CHOICE;
    }

    double eps;
    printf("Введите точность (eps > 0): ");
    if (scanf("%lf", &eps) != 1 || eps <= 0) {
        printf("Эпсилон должен быть положительным числом\n");
        return STATUS_INVALID_EPS;
    }
     
    double result;
    Status status = STATUS_OK;
    if ((x == 5 && eps < 0.0001) || (x != 5 && eps < 0.000001)) {
        printf("Введите больший эпсилон.\n");
        return STATUS_INVALID_EPS;
    }
    
    printf("\nРезультаты вычислений:\n");
    printf("---------------------\n");

    switch (x) {
        case 1: // e
            status = e_lim(eps, &result);
            if (status == STATUS_OK) printf("Предел:    %.7f\n", result);
            status = e_ryad(eps, &result);
            if (status == STATUS_OK) printf("Ряд:       %.7f\n", result);
            status = e_newton(eps, &result);
            if (status == STATUS_OK) printf("Уравнение: %.7f\n", result);
            break;
        
        case 2: // pi
            status = pi_lim(eps, &result);
            if (status == STATUS_OK) printf("Предел:    %.7f\n", result);
            status = pi_ryad(eps, &result);
            if (status == STATUS_OK) printf("Ряд:       %.7f\n", result);
            status = pi_newton(eps, &result);
            if (status == STATUS_OK) printf("Уравнение: %.7f\n", result);
            break;

        case 3: // ln2
            status = ln2_lim(eps, &result);
            if (status == STATUS_OK) printf("Предел:    %.7f\n", result);
            status = ln2_ryad(eps, &result);
            if (status == STATUS_OK) printf("Ряд:       %.7f\n", result);
            status = ln2_newton(eps, &result);
            if (status == STATUS_OK) printf("Уравнение: %.7f\n", result);
            break;

        case 4: // sqrt2
            status = sqrt2_lim(eps, &result);
            if (status == STATUS_OK) printf("Предел:    %.7f\n", result);
            status = sqrt2_ryad(eps, &result);
            if (status == STATUS_OK) printf("Ряд:       %.7f\n", result);
            status = sqrt2_newton(eps, &result);
            if (status == STATUS_OK) printf("Уравнение: %.7f\n", result);
            break;

        case 5: // gamma
            status = y_lim(eps, &result);
            if (status == STATUS_OK) printf("Предел:    %.7f\n", result);
            status = y_ryad(eps, &result);
            if (status == STATUS_OK) printf("Ряд:       %.7f\n", result);
            status = y_newton(eps, &result);
            if (status == STATUS_OK) printf("Уравнение: %.7f\n", result);
            break;

        default:
            printf("Введите число от 1 до 5\n");
            return STATUS_INVALID_CHOICE;
    }

    if (status != STATUS_OK) {
        printf("Ошибка %d\n", status);
        return status;
    }

    return STATUS_OK;
}