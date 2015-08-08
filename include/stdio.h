#ifndef LIBDOS_STDIO_H
#define LIBDOS_STDIO_H

#include "stddef.h"

#define EOF -1

extern const FILE *stdin;
extern const FILE *stdout;
extern const FILE *stderr;

int printf(const char *format, ...)
    __attribute__((format(__printf__, 1, 2)));

int fprintf(FILE *stream, const char *format, ...)
    __attribute__((format(__printf__, 2, 3)));

int sprintf(char *str, const char *format, ...)
    __attribute__((format(__printf__, 2, 3)));

int snprintf(char *str, size_t size, const char *format, ...)
    __attribute__((format(__printf__, 3, 4)));

int puts(const char *s);
int fputs(const char *s, FILE *stream);
void perror(const char *s);

#endif
