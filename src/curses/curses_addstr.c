#include <curses.h>

static void _waddnstr(WINDOW *win, int idx, const char *str, int n)
{
    int wr = 0;
    const char *p = str;

    while (*p && wr != n)
    {
	win->data[idx] = (win->data[idx]&0xff00) | (unsigned char)*p++;
	++idx;
	++wr;
    }
    win->x += wr;
    while (win->x > win->cols)
    {
	if (win->y < win->rows-2) ++win->y;
	win->x -= win->cols;
    }
}

int mvwaddnstr(WINDOW *win, int y, int x, const char *str, int n)
{
    if (y >= 0 && x >= 0) wmove(win, y, x);
    if (win->parent) _waddnstr(win->parent,
	    (win->y+win->row-win->parent->row)*win->parent->cols
	    +win->x+win->col-win->parent->col, str, n);
    else _waddnstr(win, win->cols*win->y+win->x, str, n);

    return OK;
}

