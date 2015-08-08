#include "string.h"
#include "errno.h"
#include "stdio.h"

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
    static char *strtokptr = 0;
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
    if (t && p > str)
    {
	strtokptr = 0;
	return str;
    }
    return 0;
}

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

char *strerror(int errnum)
{
    static char unknown[18];
    switch (errnum)
    {
	case EINVAL: return "Invalid argument";
	case ENOSYS: return "Function not implemented";
	case ENODEV: return "No such device";
	case ECANCELED: return "Operation canceled";
	case EBUSY: return "Device or resource busy";
	case ENOMEM: return "Not enough space";
    }
    errno = EINVAL;
    snprintf(unknown, 18, "Unknown error %03d", errnum);
    return unknown;
}

char *strqetok(char *str, const char *quot, const char *esc, const char *delim)
{
    static char *r, *w;
    static unsigned char e;
    static char q;
    char *t = 0;

    if (str)
    {
	r = w = str;
	e = 0;
	q = '\0';
    }

    if (!r) return 0;

    while (*r)
    {
	if (e)
	{
	    if (!t) t = w;
	    *w++ = *r++;
	    e = 0;
	}
	else if (q)
	{
	    if (*r == q)
	    {
		q = '\0';
		++r;
	    }
	    else if (r[1] == q && _isinstr(*r, esc))
	    {
		e = 1;
		++r;
	    }
	    else
	    {
		if (!t) t = w;
		*w++ = *r++;
	    }
	}
	else
	{
	    if (_isinstr(*r, delim))
	    {
		++r;
		if (t)
		{
		    *w++ = '\0';
		    return t;
		}
	    }
	    else if (_isinstr(*r, esc))
	    {
		e = 1;
		++r;
	    }
	    else if (_isinstr(*r, quot))
	    {
		q = *r++;
	    }
	    else
	    {
		if (!t) t = w;
		*w++ = *r++;
	    }
	}
    }
    if (t) *w = '\0';
    return t;
}

