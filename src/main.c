#include <curses.h>

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
    WINDOW *field = newwin(10, 40, 5, 20);

    wbkgd(status, COLOR_PAIR(1)|A_BLINK);
    mvwaddstr(status, 0, 1, "example title bar");
    wrefresh(status);
    wbkgd(field, COLOR_PAIR(2)|A_BOLD);
    box(field, 0, 0);
    mvwaddstr(field, 2, 12, "EXAMPLE  DIALOG");
    wrefresh(field);

    beep();
    flash();

    getch();

    delwin(field);
    delwin(status);
    endwin();

    return 0;
}
