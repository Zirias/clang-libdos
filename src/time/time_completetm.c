#include <time.h>

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

