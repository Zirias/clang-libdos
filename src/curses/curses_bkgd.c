#include <curses.h>

static void _wbkgd(WINDOW *win, chtype ch, int sr, int sc, int nr, int nc)
{
    for (int r = sr; r < sr + nr; ++r)
    {
	for (int c = sc; c < sc + nc; ++c)
	{
	    if ((win->data[r*win->cols+c] & 0xff) == (win->bkgd & 0xff))
	    {
		win->data[r*win->cols+c] = ch;
	    }
	    else
	    {
		win->data[r*win->cols+c] =
		    (win->data[r*win->cols+c] & 0xff) | (ch & 0xff00);
	    }
	}
    }
}

int wbkgd(WINDOW *win, chtype ch)
{
    if (win->parent) _wbkgd(win->parent, ch,
	    win->row - win->parent->row, win->col - win->parent->col,
	    win->rows, win->cols);
    else _wbkgd(win, ch, 0, 0, win->rows, win->cols);
    win->bkgd = ch;
    return OK;
}

