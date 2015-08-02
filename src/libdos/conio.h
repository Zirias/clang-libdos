#ifndef LIBDOS_CONIO_H
#define LIBDOS_CONIO_H

int setpage(int page);
int getpage(void);
void setattr(int attr);
void setscroll(int scroll);
void setcursor(int show);
void setblink(int blink);
void clrscr(void);
void gotoxy(int x, int y);
int getch(void);
void putchrp(char c, int repeat);
void putch(char c);
int putstr(const char *s);

#endif
