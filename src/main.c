#include <curses.h>
#include <math.h>
#include <stdlib.h>
#include <stdio.h>
#include <conio.h>

int main(int argc, char **argv)
{
    (void)(argc);
    (void)(argv);

    initscr();
    curs_set(0);
    
    init_pair(0, COLOR_WHITE, COLOR_BLACK);
    init_pair(1, COLOR_BLACK, COLOR_CYAN);
    init_pair(2, COLOR_WHITE, COLOR_BLUE);

    WINDOW *status = newwin(1, 0, 0, 0);
    WINDOW *field = newwin(0, 0, 1, 0);

    wbkgd(status, COLOR_PAIR(1)|A_BLINK);
    mvwaddstr(status, 0, 1, "example title bar -- press key");
    wrefresh(status);
    wbkgd(field, COLOR_PAIR(0)|A_BLINK);
    wrefresh(field);
    getch();

    WINDOW *dlg = subwin(field, 10, 40, 5, 20);
    wbkgd(dlg, COLOR_PAIR(2)|A_BOLD);
    box(dlg, 0, 0);
    mvwaddstr(dlg, 2, 12, "EXAMPLE  DIALOG");
    mvwprintw(dlg, 4, 2, "Test: %d", 42);
    double sqr2 = sqrt(2);
    mvwprintw(dlg, 5, 2, "Testing sqrt(): %d", (int)(sqr2 * 100000.0));
    wrefresh(dlg);
    delwin(dlg);

    beep();
    flash();

    getch();

    delwin(field);
    delwin(status);
    endwin();

    putstr("Timeout test (setdelay(0)) -- ESC to quit:\n");

    int c = 0;
    int i = 0;
    setdelay(0);
    while (c != KEY_ESC)
    {
	static int spin[] = { '|', '/', '-', '\\' };
	putch(spin[i++]);
	if (i == 4) i = 0;
	c = getch();
	if (c >= 0) printf("0x%04x\n", c);
    }

    return 0;
}
