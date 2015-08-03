#ifndef LIBDOS_TIME_H
#define LIBDOS_TIME_H

#include "stddef.h"

struct tm
{
    int tm_sec;
    int tm_min;
    int tm_hour;
    int tm_mday;
    int tm_mon;
    int tm_year;
    int tm_wday;
    int tm_yday;
    int tm_isdst;
};

int getrtctm(struct tm *tm);


#endif
