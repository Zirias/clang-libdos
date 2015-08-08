#include <time.h>

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
