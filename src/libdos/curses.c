#include "curses.h"

#include "stdlib.h"

static int active = 0;
static WINDOW std;
WINDOW * const stdscr = &std;

static unsigned short phys[80*25];
static unsigned short virt[80*25];

unsigned char colpairs[COLOR_PAIRS];

WINDOW *initscr(void)
{
    if (active) return stdscr;
    std.rows = 25;
    std.cols = 80;
    std.bkgd = 0x0720;
    std.parent = 0;
    setpage(1);
    setattr(0x07);
    clrscr();
    gotoxy(0,0);
    for (int i = 0; i < 80*25; ++i)
    {
	phys[i] = 0x0720;
	virt[i] = 0x0720;
	std.data[i] = 0x0720;
    }
    active = 1;
    return stdscr;
}

int endwin(void)
{
    if (!active) return ERR;
    active = 0;
    setpage(0);
    return OK;
}

WINDOW *newwin(int nlines, int ncols, int begin_y, int begin_x)
{
    if (!nlines) nlines = 25 - begin_y;
    if (!ncols) ncols = 80 - begin_x;
    WINDOW *win = malloc(sizeof(WINDOW) +
	    (nlines * ncols - 80 * 25) * sizeof (unsigned short));
    win->rows = nlines;
    win->cols = ncols;
    win->row = begin_y;
    win->col = begin_x;
    win->y = 0;
    win->x = 0;
    win->parent = 0;
    win->bkgd = 0x0720;
    for (int i = 0; i < nlines * ncols; ++i)
    {
	win->data[i] = 0x0720;
    }
    return win;
}

int delwin(WINDOW *win)
{
    if (!win) return ERR;
    free(win);
    return OK;
}

int wnoutrefresh(WINDOW *win)
{
    for (int r = 0; r < win->rows; ++r)
    {
	for (int c = 0; c < win->cols; ++c)
	{
	    virt[80*(r+win->row)+c+win->col] = win->data[win->cols*r+c];
	}
    }
    return OK;
}

int doupdate(void)
{
    for (int r = 0; r < 25; ++r)
    {
	for (int c = 0; c < 80; ++c)
	{
	    if (phys[80*r+c] != virt[80*r+c])
	    {
		gotoxy(c,r);
		putch(virt[80*r+c]);
		phys[80*r+c] = virt[80*r+c];
	    }
	}
    }
    return OK;
}

int wrefresh(WINDOW *win)
{
    wnoutrefresh(win);
    doupdate();
    return OK;
}

int init_pair(short pair, short f, short b)
{
    static const int permut[8] = {0,4,2,6,1,5,3,7};
    if (pair < 0 || pair > COLOR_PAIRS-1) return ERR;
    colpairs[pair] = COL_PAIR(permut[f], permut[b]);
    return OK;
}
