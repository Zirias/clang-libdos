#include <curses.h>
#include <math.h>
#include <stdlib.h>
#include <stdio.h>

int main(int argc, char **argv)
{
    (void)(argc);
    (void)(argv);

    char *p;
    puts("Allocating 4K blocks ...");
    while ((p = malloc(4096)))
    {
	printf("Allocated block at 0x%04x.\n", p);
    }
    puts("Allocation failed.");
    exit(0);

    initscr();
    curs_set(0);
    
    init_pair(0, COLOR_WHITE, COLOR_BLACK);
    init_pair(1, COLOR_BLACK, COLOR_CYAN);
    init_pair(2, COLOR_WHITE, COLOR_BLUE);

    WINDOW *status = newwin(1, 0, 0, 0);
    WINDOW *field = newwin(10, 40, 5, 20);

    wbkgd(status, COLOR_PAIR(1)|A_BLINK);
    mvwaddstr(status, 0, 1, "example title bar");
    wrefresh(status);
    wbkgd(field, COLOR_PAIR(2)|A_BOLD);
    box(field, 0, 0);
    mvwaddstr(field, 2, 12, "EXAMPLE  DIALOG");
    mvwprintw(field, 4, 2, "Test: %d", 42);
    double sqr2 = sqrt(2);
    mvwprintw(field, 5, 2, "Testing sqrt(): %d", (int)(sqr2 * 100000.0));
    wrefresh(field);

    beep();
    flash();

    getch();

    delwin(field);
    delwin(status);
    endwin();

    return 0;
}
