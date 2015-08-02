#ifndef LIBDOS_STDIO_H
#define LIBDOS_STDIO_H

#include "stddef.h"

#define EOF -1

int printf(const char *format, ...)
    __attribute__((format(__printf__, 1, 2)));

#endif
