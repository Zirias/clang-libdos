#include <curses.h>

#include <stdio.h>

int vw_printw(WINDOW *win, const char *fmt, va_list varglist)
{
    char buf[800];
    vsnprintf(buf, 800, fmt, varglist);
    return mvwaddnstr(win, -1, -1, buf, -1);
}

int mvwprintw(WINDOW *win, int y, int x, const char *fmt, ...)
{
    va_list ap;
    int rc;

    if (y >= 0 && x >= 0) wmove(win, y, x);
    va_start(ap, fmt);
    rc = vw_printw(win, fmt, ap);
    va_end(ap);
    return rc;
}

