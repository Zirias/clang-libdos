#ifndef LIBDOS_TIME_H
#define LIBDOS_TIME_H

#include "stddef.h"

typedef int time_t;

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

int readrtc(struct tm *tm);
void completetm(struct tm *tm);
int getrtctm(struct tm *tm);
time_t mktime(struct tm *tm);
time_t time(time_t *t);

#endif
