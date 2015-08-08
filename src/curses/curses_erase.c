#include <curses.h>

int werase(WINDOW *win)
{
    chtype ech = (win->bkgd & 0xff00) | 0x20;
    if (win->parent)
    {
	for (int r = win->row - win->parent->row;
		r < win->row - win->parent->row + win->rows; ++r)
	{
	    for (int c = win->col - win->parent->col;
		    c < win->col - win->parent->col + win->cols; ++c)
	    {
		win->parent->data[r*win->parent->cols + c] = ech;
	    }
	}
	return OK;
    }
    for (int i = 0; i < win->rows * win->cols; ++i) win->data[i] = ech;
    return OK;
}

