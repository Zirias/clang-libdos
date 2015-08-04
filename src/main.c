#include <stdio.h>
#include <curses.h>

extern chtype virt[];
extern chtype phys[];

int main(int argc, char **argv)
{
    (void)(argc);
    (void)(argv);

    initscr();
    curs_set(0);
    
    init_pair(0, COLOR_WHITE, COLOR_BLACK);
    init_pair(1, COLOR_BLACK, COLOR_CYAN);

    WINDOW *status = newwin(1, 0, 0, 0);
    WINDOW *field = newwin(0, 0, 1, 0);

    wbkgd(status, COLOR_PAIR(1)|A_BLINK);
    wrefresh(status);

    getch();

    delwin(field);
    delwin(status);
    endwin();

    return 0;
}
