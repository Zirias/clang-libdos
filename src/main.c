#include <stdio.h>
#include <curses.h>

extern char _data;
extern char _rodata;
extern char _common;
extern char _bss;
extern char _heap;

int main(int argc, char **argv)
{
    (void)(argc);
    (void)(argv);

    printf("DBG:   _data  0x0%08x\n", &_data);
    printf("DBG: _rodata  0x0%08x\n", &_rodata);
    printf("DBG: _common  0x0%08x\n", &_common);
    printf("DBG:    _bss  0x0%08x\n", &_bss);
    printf("DBG:   _heap  0x0%08x\n", &_heap);

    getch();

    initscr();
    curs_set(0);
    
    init_pair(0, COLOR_WHITE, COLOR_BLACK);
    init_pair(1, COLOR_BLACK, COLOR_CYAN);

    WINDOW *status = newwin(1, 0, 0, 0);
    WINDOW *field = newwin(0, 0, 1, 0);

    wbkgd(status, COLOR_PAIR(1)|A_BLINK);
    wrefresh(status);
    beep();
    flash();

    getch();

    delwin(field);
    delwin(status);
    endwin();

    return 0;
}
