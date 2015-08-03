#ifndef LIBDOS_STRING_H
#define LIBDOS_STRING_H

#include "stddef.h"

size_t strlen(const char *s);
char *strcpy(char *dest, const char *src);
char *strtok(char *str, const char *delim);
void *memcpy(void *dest, const void *src, size_t n);
void *memset(void *s, int c, size_t n);
char *strerror(int errnum);

#endif
