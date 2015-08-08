#include <time.h>

int getrtctm(struct tm *tm)
{
    if (readrtc(tm) < 0) return -1;
    completetm(tm);
    
    return 0;
}

