#include "time.h"
#include "errno.h"

int readrtc(struct tm *tm)
{
    unsigned int bcdcy = 0;
    unsigned int bcdmd = 0;
    unsigned int bcdhm = 0;
    unsigned int bcdsd = 0;
    int try;
    int err;

    try = 2;
    do
    {
	__asm__ (
		"movl	$0, %0		\n\t"
		"mov	$0x04, %%ah	\n\t"
		"clc			\n\t"
		"int	$0x1a		\n\t"
		"jnc	1f		\n\t"
		"movl	$1, %0		\n"
		"1:			\n\t"
		: "=rm" (err), "=c" (bcdcy), "=d" (bcdmd)
		:
		: "ax"
		);
	--try;
    } while (try && (err || (!bcdcy && !bcdmd)));

    if (err)
    {
	errno = EBUSY;
	return -1;
    }

    try = 2;
    do
    {
	__asm__ (
		"movl	$0, %0		\n\t"
		"mov	$0x02, %%ah	\n\t"
		"clc			\n\t"
		"int	$0x1a		\n\t"
		"jnc	1f		\n\t"
		"movl	$1, %0		\n"
		"1:			\n\t"
		: "=rm" (err), "=c" (bcdhm), "=d" (bcdsd)
		:
		: "ax"
		);
	--try;
    } while (try && err);

    if (err)
    {
	errno = EBUSY;
	return -1;
    }

    if (!bcdcy && !bcdmd && !bcdhm && !bcdsd)
    {
	errno = ENODEV;
	return -1;
    }

    tm->tm_year = ((bcdcy >> 12) & 0xf) * 1000 + ((bcdcy >> 8) & 0xf) * 100
	+ ((bcdcy >> 4) & 0xf) * 10 + (bcdcy & 0xf) - 1900;
    tm->tm_mon = ((bcdmd >> 12) & 0xf) * 10 + ((bcdmd >> 8) & 0xf) -1;
    tm->tm_mday = ((bcdmd >> 4) & 0xf) * 10 + (bcdmd & 0xf);
    tm->tm_hour = ((bcdhm >> 12) & 0xf) * 10 + ((bcdhm >> 8) & 0xf);
    tm->tm_min = ((bcdhm >> 4) & 0xf) * 10 + (bcdhm & 0xf);
    tm->tm_sec = ((bcdsd >> 12) & 0xf) * 10 + ((bcdsd >> 8) & 0xf);
    tm->tm_isdst = bcdsd & 0xf;
    tm->tm_yday = -1;
    tm->tm_wday = -1;

    return 0;
}

void completetm(struct tm *tm)
{
    static int t[] = {0, 3, 2, 5, 0, 3, 5, 1, 4, 6, 2, 4};
    static int d[] = {31, 0, 31, 30, 31, 30, 31, 31, 30, 31, 30};

    int y = tm->tm_year+1900;

    d[1] = (!(y%4) && (!(y%400) || y%100)) ? 29 : 28;
    tm->tm_yday = 0;
    for (int i = 0; i < tm->tm_mon; ++i) tm->tm_yday += d[i];
    tm->tm_yday += tm->tm_mday - 1;

    y -= (tm->tm_mon < 2);
    tm->tm_wday = (y + y/4 - y/100 + y/400 + t[tm->tm_mon] + tm->tm_mday) % 7;
}

int getrtctm(struct tm *tm)
{
    if (readrtc(tm) < 0) return -1;
    completetm(tm);
    
    return 0;
}

time_t mktime(struct tm *tm)
{
    time_t time = 0;

    if (tm->tm_yday < 0) completetm(tm);
    int y = tm->tm_year+1900;
    int s = y < 1970 ? -1 : 1;
    while (y != 1970)
    {
	time += s * ((!(y%4) && (!(y%400) || y%100)) ? 31622400 : 31536000);
	y -= s;
    }
    time += 86400 * tm->tm_yday + 3600 * tm->tm_hour
	+ 60 * tm->tm_min + tm->tm_sec;
    return time;
}

time_t time(time_t *t)
{
    struct tm tm;
    time_t time;

    if (getrtctm(&tm) < 0)
    {
	unsigned short cx, dx;
	__asm__ (
		"mov	$0, %%ah    \n\t"
		"int	$0x1a	    \n\t"
		: "=c" (cx), "=d" (dx)
		:
		: "ax"
		);
	time = cx;
	time <<= 16;
	time |= dx;
	time = (time_t) ((double)time / 18.2);
    }
    else
    {
	time = mktime(&tm);
    }
    if (t) *t = time;
    return time;
}
