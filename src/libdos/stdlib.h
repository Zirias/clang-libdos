#ifndef LIBDOS_STDLIB_H
#define LIBDOS_STDLIB_H

#include "stddef.h"

void exit(int status) __attribute__((__noreturn__));
void *malloc(size_t size);
void free(void *ptr);
void *realloc(void *ptr, size_t size);

#endif
