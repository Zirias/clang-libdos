#include <time.h>

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

