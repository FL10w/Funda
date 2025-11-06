#ifndef FUNC_H
#define FUNC_H

#include <stddef.h>

void *memchr(const void *str, int c, size_t n);
int memcmp(const void *str1, const void *str2, size_t n);
void *memcpy(void *dest, const void *src, size_t n);
void *memset(void *str, int c, size_t n);
char *strncat(char *dest, const char *src, size_t n);
char *strchr(const char *str, int c);
int strncmp(const char *str1, const char *str2, size_t n);
char *strncpy(char *dest, const char *src, size_t n);
size_t strcspn(const char *str1, const char *str2);
size_t strlen(const char *str);
char *strpbrk(const char *str1, const char *str2);
char *strrchr(const char *str, int c);
char *strstr(const char *haystack, const char *needle);
char *strtok(char *str, const char *delim);
char *strerror(int errnum);

void print_menu();
void demo_strlen();
void demo_strncpy();
void demo_strncat();
void demo_strncmp();
void demo_strchr();
void demo_strstr();
void demo_strtok();
void demo_memset();
void demo_memcpy();
void demo_memchr();
void demo_memcmp();
void demo_strcspn();
void demo_strpbrk();
void demo_strrchr();
void demo_strerror();

#endif