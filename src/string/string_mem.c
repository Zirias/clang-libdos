#include <string.h>

void *memcpy(void *dest, const void *src, size_t n)
{
    if (!dest) return 0;
    for (size_t i = 0; i < n; ++i)
    {
	((unsigned char *)dest)[i] = ((const unsigned char *)src)[i];
    }
    return dest;
}

void *memset(void *s, int c, size_t n)
{
    if (!s) return 0;
    for (size_t i = 0; i < n; ++i)
    {
	((unsigned char *)s)[i] = (unsigned char)c;
    }
    return s;
}

