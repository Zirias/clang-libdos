#include <string.h>

void *memcpy(void *dest, const void *src, size_t n)
{
    if (!dest) return 0;
    for (size_t i = 0; i < n; ++i)
    {
	((char *)dest)[i] = ((const char *)src)[i];
    }
    return dest;
}

void *memset(void *s, int c, size_t n)
{
    if (!s) return 0;
    for (size_t i = 0; i < n; ++i)
    {
	((char *)s)[i] = (char)c;
    }
    return s;
}

void *memchr(const void *s, int c, size_t n)
{
    const char *p = s;
    while (n--) {
	if (*p == (char)c)
	    return (void *)p;
	p++;
    }
    return NULL;
}
