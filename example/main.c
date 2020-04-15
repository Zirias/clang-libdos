#include <curses.h>
#include <math.h>
#include <stdlib.h>
#include <stdio.h>
#include <conio.h>
#include <time.h>
#include <rtctimer.h>

#ifdef NOARGV
int main()
{
    puts("Command line disabled.");
#else
int main(int argc, char **argv)
{
    puts("Testing command line:");
    for (int i = 0; i < argc; ++i)
    {
	printf("argv[%2d] = %s\n", i, argv[i]);
    }
#endif
    puts("Any key to continue ...");
    getch();

    puts("Testing RTC:");
    struct tm tm;
    if (getrtctm(&tm) < 0)
    {
	puts("Error reading RTC");
    }
    else
    {
	printf("%04d-%02d-%02d %02d:%02d:%02d\n", tm.tm_year+1900,
		tm.tm_mon+1, tm.tm_mday, tm.tm_hour, tm.tm_min, tm.tm_sec);
    }
    puts("Any key to continue ...");
    getch();

    /*
    puts("Testing RTC timer ...");
    for (int i = 0; i < 4; ++i)
    {
	rtctset(500000);
	rtctwait();
	puts("<tick> ...");
    }
    */

    initscr();
    curs_set(0);
    
    init_pair(0, COLOR_WHITE, COLOR_BLACK);
    init_pair(1, COLOR_BLACK, COLOR_CYAN);
    init_pair(2, COLOR_WHITE, COLOR_BLUE);

    WINDOW *status = newwin(1, 0, 0, 0);
    WINDOW *field = newwin(0, 0, 1, 0);

    wbkgd(status, COLOR_PAIR(1)|A_BLINK);
    mvwaddstr(status, 0, 1, "example title bar");
    wrefresh(status);
    wbkgd(field, COLOR_PAIR(0)|A_BLINK);
    wrefresh(field);

    WINDOW *dlg = subwin(field, 10, 40, 5, 20);
    wbkgd(dlg, COLOR_PAIR(2)|A_BOLD);
    box(dlg, 0, 0);
    mvwaddstr(dlg, 2, 12, "EXAMPLE  DIALOG");
    mvwprintw(dlg, 4, 2, "Test: %d", 42);
    double sqr2 = sqrt(2);
    mvwprintw(dlg, 5, 2, "Testing sqrt(): %u",
	    (unsigned int)(sqr2 * 1000000000.0));
    wrefresh(dlg);
    delwin(dlg);

    beep();
    flash();

    getch();

    delwin(field);
    delwin(status);
    endwin();

    putstr("rand() test -- ESC to quit:\n");

    srand(time(0));
    while (getch() != KEY_ESC)
    {
	printf("rand(): %d\n", rand());
    }

    return 0;
}
