#include "operations.h"

void condition(const char* program_name) {
    printf("Использование: %s <флаг> <параметры>\n", program_name);
    printf("Доступные флаги:\n");
    printf("  -q <epsilon> <a> <b> <c> - решение квадратного уравнения\n");
    printf("  -m <a> <b> - проверка кратности чисел\n");
    printf("  -t <epsilon> <a> <b> <c> - проверка прямоугольного треугольника\n");
}

int validate_numbers(int count, char* numbers[]) {
    for (int i = 0; i < count; i++) {
        char* endptr;
        strtod(numbers[i], &endptr);
        if (endptr == numbers[i] || *endptr != '\0') {
            fprintf(stderr, "Ошибка: '%s' не является допустимым числом.\n", numbers[i]);
            return 1;
        }
    }
    return 0;
}

void solve_quadratic(double epsilon, double a, double b, double c) {
    if (fabs(a) < epsilon) {
        if (fabs(b) < epsilon) {
            if (fabs(c) < epsilon) {
                printf("Бесконечное количество решений\n");
            } else {
                printf("Нет решений\n");
            }
        } else {
            double x = -c / b;
            printf("Линейное уравнение: x = %g\n", x);
        }
        return;
    }
    
    double discriminant = b * b - 4 * a * c;
    
    if (fabs(discriminant) < epsilon) {
        double x = -b / (2 * a);
        printf("Один корень: x = %g\n", x);
    } else if (discriminant > 0) {
        double x1 = (-b + sqrt(discriminant)) / (2 * a);
        double x2 = (-b - sqrt(discriminant)) / (2 * a);
        printf("Два корня: x1 = %g, x2 = %g\n", x1, x2);
    } else {
        printf("Комплексные корни\n");
    }
}

int process_flag_q(double epsilon, double a, double b, double c) {
    printf("Решения квадратного уравнения с коэффициентами:\n");
    printf("a = %g, b = %g, c = %g\n", a, b, c);
    solve_quadratic(epsilon, a, b, c);
    printf("\n");
    double coefficients[3] = {a, b, c};
    bool used[3][3][3] = {false};
    
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            if (j == i) continue;
            for (int k = 0; k < 3; k++) {
                if (k == i || k == j) continue;
                
                if (!used[i][j][k]) {
                    used[i][j][k] = true;
                    printf("Перестановка: a = %g, b = %g, c = %g\n", 
                           coefficients[i], coefficients[j], coefficients[k]);
                    solve_quadratic(epsilon, coefficients[i], coefficients[j], coefficients[k]);
                    printf("\n");
                }
            }
        }
    }
    
    return 0;
}

int process_flag_m(int a, int b) {
    if (b == 0) {
        fprintf(stderr, "Ошибка: Второе число не может быть нулем.\n");
        return 1;
    }
    
    if (a % b == 0) {
        printf("%d кратно %d\n", a, b);
    } else {
        printf("%d не кратно %d\n", a, b);
    }
    
    return 0;
}

int process_flag_t(double epsilon, double a, double b, double c) {
    if (a <= 0 || b <= 0 || c <= 0) {
        printf("Числа не могут быть сторонами треугольника\n");
        return 1;
    }
    
    if (a + b <= c || a + c <= b || b + c <= a) {
        printf("Числа не могут быть сторонами треугольника (нарушено неравенство треугольника)\n");
        return 1;
    }
    
    double sides[3] = {a, b, c};
    bool is_right_triangle = false;
    
    for (int i = 0; i < 3; i++) {
        for (int j = i + 1; j < 3; j++) {
            int k = 3 - i - j; 
            
            double side1 = sides[i];
            double side2 = sides[j];
            double hypotenuse = sides[k];
            
            if (fabs(side1 * side1 + side2 * side2 - hypotenuse * hypotenuse) < epsilon) {
                printf("Числа %g, %g, %g могут быть сторонами прямоугольного треугольника\n", 
                       a, b, c);
                printf("(где %g^2 + %g^2 = %g^2)\n", side1, side2, hypotenuse);
                is_right_triangle = true;
                break;
            }
        }
        if (is_right_triangle) break;
    }
    
    if (!is_right_triangle) {
        printf("Числа %g, %g, %g не могут быть сторонами прямоугольного треугольника\n", a, b, c);
    }
    
    return 0;
}