#include "stdio.h"

#include "conio.h"
#include "string.h"
#include "stdarg.h"

static char fpbuf[32];

typedef enum farglen
{
    FAL_HH,
    FAL_H,
    FAL_DEF,
    FAL_L
} farglen;

static size_t _fargnbuf(char **buf, const char **s, size_t n)
{
    while ((!n || n > 1) && **s)
    {
	*(*buf)++ = *(*s)++;
	if (n) --n;
    }
    **buf = 0;
    return n;
}

static size_t _ffmtnbuf(char **buf, const char **s, size_t n)
{
    while ((!n || n > 1) && **s && **s != '%')
    {
	*(*buf)++ = *(*s)++;
	if (n) --n;
    }
    **buf = 0;
    return n;
}

static void _fnumarg(long num, char pad, size_t minwidth, int sign)
{
    char tmp[11];
    int i = 0;
    char *s = fpbuf;

    if (minwidth > 31) minwidth = 31;

    if (sign)
    {
	if (num < 0)
	{
	    *s++ = '-';
	    --minwidth;
	    num = -num;
	}
	else if (pad == ' ')
	{
	    *s++ = ' ';
	    --minwidth;
	}
    }
    if (pad != '0') pad = ' ';
    do
    {
	tmp[i++] = (unsigned long)num % 10;
	num = (unsigned long)num / 10;
    } while (num > 0);
    while (minwidth-- > i) *s++ = pad;
    while (--i >= 0) *s++ = tmp[i] + '0';
    *s = 0;
}

int vprintf(const char *format, va_list ap)
{
    int n = 0;
    char *buf;

    while (*format)
    {
	if (*format == '%')
	{
	    char pad = 0;
	    size_t minwidth = 0;
	    farglen len = FAL_DEF;
	    unsigned long num;

	    while (1)
	    {
		format++;
		switch (*format)
		{
		    case 'd':
			switch (len)
			{
			    case FAL_HH:
				num = (signed char) va_arg(ap, int);
				break;
			    case FAL_H:
				num = (short) va_arg(ap, int);
				break;
			    case FAL_DEF:
				num = va_arg(ap, int);
				break;
			    case FAL_L:
				num = va_arg(ap, unsigned long);
			}
			_fnumarg((long)num, pad, minwidth, 1);
			buf = fpbuf;
			goto argdone;

		    case 'u':
			switch (len)
			{
			    case FAL_HH:
				num = (unsigned char) va_arg(ap, unsigned int);
				break;
			    case FAL_H:
				num = (unsigned short) va_arg(ap, unsigned int);
				break;
			    case FAL_DEF:
				num = va_arg(ap, unsigned int);
				break;
			    case FAL_L:
				num = va_arg(ap, unsigned long);
			}
			_fnumarg((long)num, pad, minwidth, 0);
			buf = fpbuf;
			goto argdone;

		    case 's':
			buf = va_arg(ap, char*);
			goto argdone;

		    case '0':
			if (minwidth) minwidth *= 10;
			else pad = '0';
			break;

		    case ' ':
			pad = ' ';
			break;

		    case 'h':
			if (len > FAL_HH) --len;
			break;

		    case 'l':
			if (len < FAL_L) ++len;
			break;

		    default:
			if (!*format)
			{
			    buf = 0;
			    goto argdone;
			}
			if (*format >= '1' && *format <= '9')
			{
			    minwidth *= 10;
			    minwidth += *format - '0';
			}
		}
	    }
argdone:
	    ++format;
	    n += putstr(buf);
	}
	else
	{
	    buf = fpbuf;
	    _ffmtnbuf(&buf, &format, 32);
	    n += putstr(fpbuf);
	}
    }
    return n;
}

int printf(const char *format, ...)
{
    va_list ap;

    va_start(ap, format);
    int ret = vprintf(format, ap);
    va_end(ap);

    return ret;
}
