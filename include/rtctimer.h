#ifndef LIBDOS_RTCTIMER_H
#define LIBDOS_RTCTIMER_H

#include "stddef.h"

/* typical precision: 977 usecs */
int rtctset(unsigned int usecs);
int rtctstop(void);
int rtctwait(void);
int rtctpoll(void);

#endif
