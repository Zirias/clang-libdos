#ifndef LIBDOS_CURSES_H
#define LIBDOS_CURSES_H

#include <conio.h>

typedef unsigned short chtype;

typedef struct WINDOW WINDOW;
struct WINDOW
{
    int row;
    int col;
    int rows;
    int cols;
    int y;
    int x;
    WINDOW *parent;
    chtype bkgd;
    chtype data[80*25];
};

extern WINDOW * const stdscr;
extern chtype colpairs[];

#define COLOR_BLACK	0
#define COLOR_RED	1
#define COLOR_GREEN	2
#define COLOR_YELLOW	3
#define COLOR_BLUE	4
#define COLOR_MAGENTA	5
#define COLOR_CYAN	6
#define COLOR_WHITE	7

#define timeout(x) setdelay((x))
#define wgetch(x) getch()
#define curs_set(x) setcursor((x))

#define raw()
#define nonl()
#define noecho()
#define keypad(x, y)
#define start_color()
#define leaveok(x, y)

#define ERR -1
#define OK 0
#define COLOR_PAIRS 64

#define COLOR_PAIR(x) colpairs[(x)]

#define getyx(win, uy, ux) do { (uy) = (win)->y; (ux) = (win)->x; } while (0)
#define getparyx(win, uy, ux) do { \
    if (!((win)->parent)) { (uy) = -1; (ux) = -1; } \
    else { (uy) = (win)->row - (win)->parent->row; \
	(ux) = (win)->col - (win)->parent->col; } \
    } while (0)
#define getbegyx(win, uy, ux) \
    do { (uy) = (win)->row; (ux) = (win)->col; } while (0)
#define getmaxyx(win, uy, ux) \
    do { (uy) = (win)->rows; (ux) = (win)->cols; } while (0)

#define wmove(win, uy, ux) do { (win)->y = (uy); (win)->x = (ux); } while (0)
#define move(uy, ux) wmove((uy), (ux))

#define A_BOLD 0x0800U
#define A_BLINK 0x8000U
#define A_ALTCHARSET 0

enum acs
{
    ACS_BLOCK	    = 0xdb,
    ACS_BOARD	    = 0xfe,
    ACS_BTEE	    = 0xc1,
    ACS_BULLET	    = 0x07,
    ACS_CKBOARD	    = 0xb1,
    ACS_DARROW	    = 0x19,
    ACS_DEGREE	    = 0xf8,
    ACS_DIAMOND	    = 0x04,
    ACS_GEQUAL	    = 0x3e,
    ACS_HLINE	    = 0xc4,
    ACS_LANTERN	    = 0x0f,
    ACS_LARROW	    = 0x1b,
    ACS_LEQUAL	    = 0x3c,
    ACS_LLCORNER    = 0xc0,
    ACS_LRCORNER    = 0xd9,
    ACS_LTEE	    = 0xc3,
    ACS_NEQUAL	    = 0x21,
    ACS_PI	    = 0x14,
    ACS_PLMINUS	    = 0xf1,
    ACS_PLUS	    = 0x2b,
    ACS_RARROW	    = 0x1a,
    ACS_RTEE	    = 0xb4,
    ACS_S1	    = 0xee,
    ACS_S3	    = 0xc4,
    ACS_S7	    = 0xc4,
    ACS_S9	    = 0xf2,
    ACS_STERLING    = 0x66,
    ACS_TTEE	    = 0xc2,
    ACS_UARROW	    = 0x18,
    ACS_ULCORNER    = 0xda,
    ACS_URCORNER    = 0xbf,
    ACS_VLINE	    = 0xb3
};

WINDOW *initscr(void);
int endwin(void);

WINDOW *newwin(int nlines, int ncols, int begin_y, int begin_x);
WINDOW *subwin(WINDOW *orig, int nlines, int nclos, int begin_y, int begin_x);

int delwin(WINDOW *win);

#define refresh() wrefresh(stdscr)
int wrefresh(WINDOW *win);
int wnoutrefresh(WINDOW *win);
int doupdate(void);

#define bkgd(x) wbkgd(stdscr, (x))
int wbkgd(WINDOW *win, chtype ch);

#define clear() wclear(stdscr)
#define wclear(x) werase((x))
#define erase() werase(stdscr)
int werase(WINDOW *win);

#define addch(x) waddch(stdscr, (x))
int waddch(WINDOW *win, chtype ch);
#define mvaddch(y, x, ch) mvwaddch(stdscr, (y), (x), (ch))
int mvwaddch(WINDOW *win, int y, int x, const chtype ch);

#define border(ls, rs, ts, bs, tl, tr, bl, br) \
    wborder(stdscr, (ls), (rs), (ts), (bs), (tl), (tr), (bl), (br))
#define box(win, verch, horch) \
    wborder((win), (verch), (verch), (horch), (horch), 0, 0, 0, 0)
int wborder(WINDOW *win, chtype ls, chtype rs, chtype ts, chtype bs,
	chtype tl, chtype tr, chtype bl, chtype br);

#define addstr(str) waddstr(stdscr, (str))
#define addnstr(str, n) waddnstr(stdscr, (str), (n))
#define waddstr(win, str) waddnstr((win), (str), -1)
#define waddnstr(win, str, n) mvwaddnstr((win), -1, -1, (str), (n))
#define mvaddstr(y, x, str) mvwaddstr(stdscr, (y), (x), (str))
#define mvaddnstr(y, x, str, n) mvwaddnstr(stdscr, (y), (x), (str), (n))
#define mvwaddstr(win, y, x, str) mvwaddnstr((win), (y), (x), (str), -1)
int mvwaddnstr(WINDOW *win, int y, int x, const char *str, int n);

int init_pair(short pair, short f, short b);

#endif
