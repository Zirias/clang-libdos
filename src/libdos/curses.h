#ifndef LIBDOS_CURSES_H
#define LIBDOS_CURSES_H

#include <conio.h>

typedef struct WINDOW WINDOW;

extern WINDOW *stdscr;

void timeout(int delay);

#define wgetch(x) getch()
#define curs_set(x) setcursor((x))

#define raw()
#define nonl()
#define noecho()
#define keypad(x, y)

#endif
