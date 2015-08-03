#include "string.h"
#include "errno.h"
#include "stdio.h"

static char *strtokptr = 0;
static char strerrunkn[18];

size_t strlen(const char *s)
{
    size_t l = 0;
    while (*s++) ++l;
    return l;
}

char *strcpy(char *dest, const char *src)
{
    char *p = dest;
    while ((*p++ = *src++));
    return dest;
}

static int _isinstr(const char c, const char *str)
{
    while (*str)
    {
	if (c == *str) return 1;
	++str;
    }
    return 0;
}

char *strtok(char *str, const char *delim)
{
    char *p;
    int t = 0;

    if (!str) str = strtokptr;
    if (!str) return 0;

    p = str;
    while (*p)
    {
	if (_isinstr(*p, delim))
	{
	    if (!t) goto cont;
	    *p = 0;
	    strtokptr = p+1;
	    return str;
	}
	if (!t)
	{
	    t = 1;
	    str = p;
	}
cont:
	++p;
    }
    return 0;
}

void *memcpy(void *dest, const void *src, size_t n)
{
    for (size_t i = 0; i < n; ++i)
    {
	((char *)dest)[i] = ((const char *)src)[i];
    }
    return dest;
}

void *memset(void *s, int c, size_t n)
{
    for (size_t i = 0; i < n; ++i)
    {
	((char *)s)[i] = (char)c;
    }
    return s;
}

char *strerror(int errnum)
{
    switch (errnum)
    {
	case EINVAL: return "Invalid argument";
	case ENOSYS: return "Function not implemented";
	case ENODEV: return "No such device";
	case EBUSY: return "Device or resource busy";
    }
    errno = EINVAL;
    snprintf(strerrunkn, 18, "Unknown error %03d", errnum);
    return strerrunkn;
}
