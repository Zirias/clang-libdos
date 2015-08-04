#include <stdio.h>
#include <curses.h>

int main(int argc, char **argv)
{
    int x, y;

    (void)(argc);
    (void)(argv);

    initscr();
    getmaxyx(stdscr, y, x);
    printf("curses test: %dx%d\n", x, y);
    getch();
    endwin();

    return 0;
}
