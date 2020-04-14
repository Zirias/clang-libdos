#include <rtctimer.h>
#include <errno.h>

static volatile unsigned char timer = 0;

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
	    "jnc    1f		    \n\t"
	    "movzx  %%ah, %0	    \n"
	    "1:			    \n\t"
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
    timer = 1;
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
	    "jnc    1f		    \n\t"
	    "movl   $1, %0	    \n"
	    "1:			    \n\t"
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

int rtctwait(void)
{
    if (!timer)
    {
	errno = ECANCELED;
	return -1;
    }
    while (!(timer & 0x80)) __asm__ volatile ("hlt");
    timer = 0;
    return 0;
}

int rtctpoll(void)
{
    if (timer & 0x80)
    {
	timer = 0;
	return 1;
    }
    return 0;
}

