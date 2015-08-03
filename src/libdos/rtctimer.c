#include "rtctimer.h"
#include "errno.h"

static unsigned char timer = 0;

int rtctset(unsigned int usecs)
{
    unsigned short dx = usecs & 0xffff;
    unsigned short cx = usecs >> 16;
    int err;

    __asm__ (
	    "movl   $0, %0	    \n\t"
	    "mov    $0x8300, %%ax   \n\t"
	    "clc		    \n\t"
	    "int    $0x15	    \n\t"
	    "jnc    rtcsetout	    \n\t"
	    "mov    %%ah, %0	    \n\t"
	    "rtcsetout:		    \n\t"
	    : "=rm" (err)
	    : "b" (&timer), "c" (cx), "d" (dx)
	    : "ax"
	    );
    if (err)
    {
	if ((err & 0xff) == 0x86) errno = ENOSYS;
	else errno = EBUSY;
	return -1;
    }
    return 0;
}

int rtctstop(void)
{
    int err;
    __asm__ (
	    "movl   $0, %0	    \n\t"
	    "mov    $0x8301, %%ax   \n\t"
	    "clc		    \n\t"
	    "int    $0x15	    \n\t"
	    "jnc    rtcstopout	    \n\t"
	    "movl   $1, %0	    \n"
	    "rtcstopout:	    \n\t"
	    : "=rm" (err)
	    :
	    : "ax"
	    );
    if (err)
    {
	errno = EBUSY;
	return -1;
    }
    timer = 0;
    return 0;
}

void rtctwait(void)
{
    while (!(timer & 0x80)) __asm__ volatile ("hlt");
}

int rtctpoll(void)
{
    return !!(timer & 0x80);
}

