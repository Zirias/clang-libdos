#include <curses.h>

static void _wborder(WINDOW *win, chtype ls, chtype rs, chtype ts, chtype bs,
	chtype tl, chtype tr, chtype bl, chtype br, int r, int c, int h, int w)
{
    if (!ls) ls = ACS_VLINE;
    if (!rs) rs = ACS_VLINE;
    if (!ts) ts = ACS_HLINE;
    if (!bs) bs = ACS_HLINE;
    if (!tl) tl = ACS_ULCORNER;
    if (!tr) tr = ACS_URCORNER;
    if (!bl) bl = ACS_LLCORNER;
    if (!br) br = ACS_LRCORNER;

    win->data[r*win->cols+c] = (win->data[r*win->cols+c]&0xff00) | tl;
    win->data[r*win->cols+c+w-1] = (win->data[r*win->cols+c+w-1]&0xff00) | tr;
    win->data[(r+h-1)*win->cols+c] =
	(win->data[(r+h-1)*win->cols+c]&0xff00) | bl;
    win->data[(r+h-1)*win->cols+c+w-1] =
	(win->data[(r+h-1)*win->cols+c+w-1]&0xff00) | br;

    for (int ri = r+1; ri < r+h-1; ++ri)
    {
	win->data[ri*win->cols+c] = (win->data[ri*win->cols+c]&0xff00) | ls;
	win->data[ri*win->cols+c+w-1] =
	    (win->data[ri*win->cols+c+w-1]&0xff00) | rs;
    }

    for (int ci = c+1; ci < c+w-1; ++ci)
    {
	win->data[r*win->cols+ci] = (win->data[r*win->cols+ci]&0xff00) | ts;
	win->data[(r+h-1)*win->cols+ci] =
	    (win->data[(r+h-1)*win->cols+ci]&0xff00) | bs;
    }
}


int wborder(WINDOW *win, chtype ls, chtype rs, chtype ts, chtype bs,
	chtype tl, chtype tr, chtype bl, chtype br)
{
    if (win->parent) _wborder(win->parent, ls, rs, ts, bs, tl, tr, bl, br,
	    win->row - win->parent->row, win->col - win->parent->col,
	    win->rows, win->cols);
    else _wborder(win, ls, rs, ts, bs, tl, tr, bl, br,
	    0, 0, win->rows, win->cols);
    return OK;
}

