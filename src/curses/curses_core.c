#include <curses.h>

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

