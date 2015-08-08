#include <time.h>

#include <errno.h>

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
