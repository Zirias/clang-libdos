#include <stdio.h>
#include <conio.h>
#include <stdlib.h>
#include <string.h>
#include <dos.h>
#include <errno.h>
#include <time.h>
#include <rtctimer.h>

int main(int argc, char **argv)
{
    (void)(argc);

    setpage(1);
    gotoxy(0,0);
    clrscr();
    setcursor(0);
    setblink(0);
    setattr(0xb0);
    putchrp(' ', 80);
    puts(" example title bar");
    setattr(0x07);
    unsigned short ver = dosversion();
    fprintf(stderr, "%s: DOS version: %hhu.%02hhu\n", argv[0],
	    (unsigned char)(ver >> 8), (unsigned char)(ver));
    struct tm tm;
    if (getrtctm(&tm) < 0)
    {
	perror("getrtctm");
    }
    else
    {
	printf("%04d-%02d-%02d %02d:%02d:%02d (doy:%03d, dow:%d)\n",
		tm.tm_year+1900, tm.tm_mon+1, tm.tm_mday,
		tm.tm_hour, tm.tm_min, tm.tm_sec,
		tm.tm_yday, tm.tm_wday);
    }
    printf("UNIX timestamp: %d\n", time(0));
    rtctset(1000000);
    rtctstop();
    if (rtctwait() < 0)
    {
	perror("rtctwait");
    }
err:
    getch();
    setcursor(1);
    setblink(1);
    setpage(0);
    return 0;
}
