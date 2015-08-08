#ifndef LIBDOS_STRING_H
#define LIBDOS_STRING_H

#include "stddef.h"

size_t strlen(const char *s);
char *strcpy(char *dest, const char *src);
char *strtok(char *str, const char *delim);
void *memcpy(void *dest, const void *src, size_t n);
void *memset(void *s, int c, size_t n);
char *strerror(int errnum);

/* ---- NON-STANDARD ---- */

/* works like strtok(), but handles escapes and quotes
 * added for command-line parsing, but might be useful for other code.
 * HINT: inside a quote, an escape is only considered for the quoting chr */
char *strqetok(char *str, const char *quot, const char *esc, const char *delim);

#endif
