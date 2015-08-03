#ifndef LIBDOS_STDLIB_H
#define LIBDOS_STDLIB_H

#include "stddef.h"

#define RAND_MAX 0x7fffffff

void exit(int status) __attribute__((__noreturn__));
void *malloc(size_t size);
void free(void *ptr);
void *realloc(void *ptr, size_t size);
int rand(void);
void srand(unsigned int seed);

#endif
