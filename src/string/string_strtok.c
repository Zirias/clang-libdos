#include <string.h>

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
	    *w++ = *r;
	    e = 0;
	}
	else if (q)
	{
	    if (*r == q)
	    {
		q = '\0';
	    }
	    else if (_isinstr(*r, esc) && r[1] &&
		    (r[1] == q || _isinstr(r[1], esc)))
	    {
		e = 1;
	    }
	    else
	    {
		if (!t) t = w;
		*w++ = *r;
	    }
	}
	else
	{
	    if (_isinstr(*r, delim))
	    {
		if (t)
		{
		    *w++ = '\0';
		    return t;
		}
	    }
	    else if (_isinstr(*r, esc))
	    {
		e = 1;
	    }
	    else if (_isinstr(*r, quot))
	    {
		if (!t) t = w;
		q = *r;
	    }
	    else
	    {
		if (!t) t = w;
		*w++ = *r;
	    }
	}
	++r;
    }
    if (t) *w = '\0';
    return t;
}

