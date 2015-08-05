#include "curses.h"

#include "stdlib.h"

static int active = 0;
static WINDOW std;
WINDOW * const stdscr = &std;

static chtype phys[80*25];
static chtype virt[80*25];

chtype colpairs[COLOR_PAIRS];

WINDOW *initscr(void)
{
    if (active) return stdscr;
    std.rows = 25;
    std.cols = 80;
    std.bkgd = 0x0720;
    std.parent = 0;
    setpage(1);
    setblink(0);
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
    setblink(1);
    setcursor(1);
    return OK;
}

WINDOW *newwin(int nlines, int ncols, int begin_y, int begin_x)
{
    if (!nlines) nlines = 25 - begin_y;
    if (!ncols) ncols = 80 - begin_x;
    WINDOW *win = malloc(sizeof(WINDOW) +
	    (nlines * ncols - 80 * 25) * sizeof (chtype));
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

WINDOW *subwin(WINDOW *orig, int nlines, int ncols, int begin_y, int begin_x)
{
    if (orig->parent) return 0;
    if (!nlines) nlines = 25 - begin_y;
    if (!ncols) ncols = 80 - begin_x;
    WINDOW *win = malloc(sizeof(WINDOW) - 80*25*sizeof(chtype));
    win->rows = nlines;
    win->cols = ncols;
    win->row = begin_y;
    win->col = begin_x;
    win->y = 0;
    win->x = 0;
    win->parent = orig;
    win->bkgd = win->parent->bkgd;
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
    if (win->parent) return (wnoutrefresh(win->parent));
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
    colpairs[pair] = COL_PAIR(permut[f], permut[b]) << 8;
    return OK;
}

int wbkgd(WINDOW *win, chtype ch)
{
    for (int r = 0; r < win->rows; ++r)
    {
	for (int c = 0; c < win->cols; ++c)
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
    win->bkgd = ch;
    return OK;
}

int werase(WINDOW *win)
{
    chtype ech = (win->bkgd & 0xff00) | 0x20;
    if (win->parent)
    {
	for (int r = win->parent->row; r < win->parent->row + win->rows; ++r)
	{
	    for (int c = win->parent->col;
		    c < win->parent->col + win->cols; ++c)
	    {
		win->parent->data[r*win->parent->cols + c] = ech;
	    }
	}
	return OK;
    }
    for (int i = 0; i < win->rows * win->cols; ++i) win->data[i] = ech;
    return OK;
}

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

int wborder(WINDOW *win, chtype ls, chtype rs, chtype ts, chtype bs,
	chtype tl, chtype tr, chtype bl, chtype br)
{
    if (!ls) ls = ACS_VLINE;
    if (!rs) rs = ACS_VLINE;
    if (!ts) ts = ACS_HLINE;
    if (!bs) bs = ACS_HLINE;
    if (!tl) tl = ACS_ULCORNER;
    if (!tr) tr = ACS_URCORNER;
    if (!bl) bl = ACS_LLCORNER;
    if (!br) br = ACS_LRCORNER;

    win->data[0] = (win->data[0]&0xff00) | tl;
    win->data[win->cols-1] = (win->data[win->cols-1]&0xff00) | tr;
    win->data[(win->rows-1)*win->cols] =
	(win->data[(win->rows-1)*win->cols]&0xff00) | bl;
    win->data[win->rows*win->cols-1] =
	(win->data[win->rows*win->cols-1]&0xff00) | br;

    for (int r = 1; r < win->rows-1;)
    {
	win->data[r*win->cols] = (win->data[r*win->cols]&0xff00) | ls;
	++r;
	win->data[r*win->cols-1] = (win->data[r*win->cols-1]&0xff00) | rs;
    }

    for (int c = 1; c < win->cols-1; ++c)
    {
	win->data[c] = (win->data[c]&0xff00) | ts;
	win->data[(win->rows-1)*win->cols+c] =
	    (win->data[(win->rows-1)*win->cols+c]&0xff00) | bs;
    }

    return OK;
}

int mvwaddnstr(WINDOW *win, int y, int x, const char *str, int n)
{
    int wr = 0;
    const char *p = str;
    int idx;

    if (y >= 0 && x >= 0) wmove(win, y, x);

    idx = win->cols * win->y + win->x;
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

    return OK;
}

