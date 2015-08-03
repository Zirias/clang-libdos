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
		"mov	$0x02, %%ah	\n\t"
		"clc			\n\t"
		"int	$0x1a		\n\t"
		"jnc	rtctsuccess	\n\t"
		"movl	$1, %0		\n"
		"rtctsuccess:		\n\t"
		: "=rm" (err), "=c" (bcdhm), "=d" (bcdsd)
		:
		: "ax"
		);
	--try;
    } while (try && err);

    if (err) return -1;

    try = 2;
    do 
    {
	__asm__ (
		"movl	$0, %0		\n\t"
		"mov	$0x04, %%ah	\n\t"
		"clc			\n\t"
		"int	$0x1a		\n\t"
		"jnc	rtcdsuccess	\n\t"
		"movl	$1, %0		\n"
		"rtcdsuccess:		\n\t"
		: "=rm" (err), "=c" (bcdcy), "=d" (bcdmd)
		:
		: "ax"
		);
	--try;
    } while (try && err);

    if (err) return -1;

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
    if (readrtc(tm) < 0)
    {
	errno = EBUSY;
	return -1;
    }
    completetm(tm);
    
    return 0;
}
