#ifndef OPERATIONS_H
#define OPERATIONS_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <stdbool.h>

void condition(const char* program_name);
int process_flag_q(double epsilon, double a, double b, double c);
int process_flag_m(int a, int b);
int process_flag_t(double epsilon, double a, double b, double c);
int validate_numbers(int count, char* numbers[]);

#endif