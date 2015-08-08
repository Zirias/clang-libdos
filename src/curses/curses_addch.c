#include <curses.h>

int waddch(WINDOW *win, const chtype ch)
{
    if (win->parent)
    {
	return mvwaddch(win->parent, win->row - win->parent->row + win->y,
		win->col - win->parent->col + win->x, ch);
    }
    if (ch & 0xff00)
    {
	win->data[win->y * win->cols + win->x] = ch;
    }
    else
    {
	win->data[win->y * win->cols + win->x] =
	    (win->data[win->y * win->cols + win->x] & 0xff00) | ch;
    }
    ++win->x;
    if (win->x >= win->cols)
    {
	win->x = 0;
	if (win->y < win->rows-1) ++win->y;
    }
    return OK;
}

int mvwaddch(WINDOW *win, int y, int x, const chtype ch)
{
    wmove(win, y, x);
    return waddch(win, ch);
}

