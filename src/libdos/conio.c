#include "conio.h"

static int cpage = 0;
static int crow;
static int ccol;
static unsigned short ccsh;
static int cattr = 0x07;
static int cscroll = 1;

void _getcinfo(void)
{
    unsigned int pos;
    __asm__ (
	    "mov    $0x0300, %%ax   \n\t"
	    "int    $0x10	    \n\t"
	    : "=c" (ccsh), "=d" (pos)
	    : "b" (cpage)
	    : "ax"
	    );
    ccol = pos & 0xff;
    crow = (pos >> 8) & 0xff;

}

static void _gotoxy(void)
{
    __asm__ volatile (
	    "mov    $0x02, %%ah	    \n\t"
	    "int    $0x10	    \n\t"
	    :
	    : "b" (cpage << 8), "d" (crow << 8 | ccol)
	    : "ax"
	    );
}

static void _scroll(int lines)
{
    __asm__ volatile (
	    "int    $0x10	    \n\t"
	    :
	    : "a" (lines | 0x0600), "b" (cattr << 8),
		"c" (0), "d" (24 << 8 | 79)
	    : "ebp"
	    );
}

int setpage(int page)
{
    if (page == cpage) return page;
    __asm__ (
	    "mov    $0x05, %%ah	    \n\t"
	    "int    $0x10	    \n\t"
	    "mov    $0x0f, %%ah	    \n\t"
	    "int    $0x10	    \n\t"
	    : "=b" (page)
	    : "a" (page)
	    );
    page = (page >> 8) & 0xff;
    if (page != cpage)
    {
	_getcinfo();
	cpage = page;
    }
    return page;
}

int getpage(void)
{
    return cpage;
}

void setattr(int attr)
{
    cattr = attr;
}

void setscroll(int scroll)
{
    cscroll = scroll;
}

void setcursor(int show)
{
    if (show) ccsh &= 0x1fff;
    else ccsh |= 0x2000;
    __asm__ volatile (
	    "mov    $0x01, %%ah	    \n\t"
	    "int    $0x10	    \n\t"
	    :
	    : "c" (ccsh)
	    );
}

void setblink(int blink)
{
    __asm__ volatile (
	    "mov    $0x1003, %%ax   \n\t"
	    "int    $0x10	    \n\t"
	    :
	    : "b" (!!blink)
	    );
}

void clrscr(void)
{
    _scroll(0);
    gotoxy(0,0);
}

void gotoxy(int x, int y)
{
    crow = y;
    ccol = x;
    _gotoxy();
}

int getch(void)
{
    int ch;
    __asm__ volatile (
	    "mov    $0x00, %%ah	    \n\t"
	    "int    $0x16	    \n\t"
	    "and    $0xffff, %%eax  \n\t"
	    : "=a" (ch)
	    );
    if (((ch&0xff) >= ' ') && ((ch&0xff) <= '~')) ch &= 0xff;
    else ch &= 0xff00;
    return ch;
}

void putchrp(char c, int repeat)
{
    __asm__ volatile (
	    "mov    $0x09, %%ah	    \n\t"
	    "int    $0x10	    \n\t"
	    :
	    : "a" (c), "b" ((cpage << 8) | cattr), "c" (repeat)
	    : "cx"
	    );
}

void putch(char c)
{
    putchrp(c, 1);
}

int putstr(const char *s)
{
    int l = 0;
    const char *p = s;

    while (*p)
    {
	switch (*p)
	{
	    case '\r':
		ccol = 0;
		_gotoxy();
		break;

	    case '\n':
		ccol = 0;
		if (crow < 24) ++crow;
		else if (cscroll) _scroll(1);
		_gotoxy();
		break;

	    default:
		putch(*p);
		if (++ccol > 79)
		{
		    ccol = 0;
		    if (crow < 24) ++crow;
		    else if (cscroll) _scroll(1);
		}
		_gotoxy();
		break;
	}
	++p;
	++l;
    }
    return l;
}

