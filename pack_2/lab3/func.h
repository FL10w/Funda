#ifndef FUNC_H
#define FUNC_H
#include <stdio.h>
#include <stdarg.h>

char * func_Ro(int num);
char * func_Zr(unsigned int num);
char * func_Cv(int num, int base);
char * func_CV(int num, int base);
int func_to(const char *num, int base);
int func_TO(const char *num, int base);
char * func_mi(int num);
char * func_mu(unsigned int num);
char * func_md(double num);
char * func_mf(float num);
int overfprintf(FILE *stream, const char *format, ...);
int oversprintf(char *str, const char *format, ...);
int over(char *str, const char *format, va_list args);

#endif