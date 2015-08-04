#ifndef LIBDOS_CONIO_H
#define LIBDOS_CONIO_H

int setpage(int page);
int getpage(void);
void setattr(int attr);
void setscroll(int scroll);
void setcursor(int show);
void setblink(int blink);
void setdelay(int msecs);
void clrscr(void);
void gotoxy(int x, int y);
void getxy(int *x, int *y);
int getch(void);
void putchrp(int c, int repeat);
void putch(int c);
int putstr(const char *s);

enum keys
{
    KEY_UP	= 0x4800,
    KEY_DOWN	= 0x5000,
    KEY_LEFT	= 0x4b00,
    KEY_RIGHT	= 0x4d00,
    KEY_ENTER	= 0x1c00,
    KEY_BS	= 0x0e00,
    KEY_INS	= 0x5200,
    KEY_DEL	= 0x5300,
    KEY_HOME	= 0x4700,
    KEY_END	= 0x4f00,
    KEY_PGUP	= 0x4900,
    KEY_PGDOWN	= 0x5100,
    KEY_TAB	= 0x0f00,
    KEY_ESC	= 0x0100,
    KEY_F1	= 0x3b00,
    KEY_F2	= 0x3c00,
    KEY_F3	= 0x3d00,
    KEY_F4	= 0x3e00,
    KEY_F5	= 0x3f00,
    KEY_F6	= 0x4000,
    KEY_F7	= 0x4100,
    KEY_F8	= 0x4200,
    KEY_F9	= 0x4300,
    KEY_F10	= 0x4400,
    KEY_F11	= 0x8500,
    KEY_F12	= 0x8600,
    KEY_C_A	= 0x1e00,
    KEY_C_B	= 0x3000,
    KEY_C_C	= 0x2e00,
    KEY_C_D	= 0x2000,
    KEY_C_E	= 0x1200,
    KEY_C_F	= 0x2100,
    KEY_C_G	= 0x2200,
    KEY_C_H	= 0x2300,
    KEY_C_I	= 0x1700,
    KEY_C_J	= 0x2400,
    KEY_C_K	= 0x2500,
    KEY_C_L	= 0x2600,
    KEY_C_M	= 0x3200,
    KEY_C_N	= 0x3100,
    KEY_C_O	= 0x1800,
    KEY_C_P	= 0x1900,
    KEY_C_Q	= 0x1000,
    KEY_C_R	= 0x1300,
    KEY_C_S	= 0x1f00,
    KEY_C_T	= 0x1400,
    KEY_C_U	= 0x1600,
    KEY_C_V	= 0x2f00,
    KEY_C_W	= 0x1100,
    KEY_C_X	= 0x2d00,
    KEY_C_Y	= 0x1500,
    KEY_C_Z	= 0x2c00
};

#define KEY_BREAK KEY_C_C
#define KEY_BELL KEY_C_G
#define KEY_LF KEY_C_J
#define KEY_FF KEY_C_L
#define KEY_CR KEY_C_M
#define KEY_CUT KEY_C_X
#define KEY_COPY KEY_C_C
#define KEY_PASTE KEY_C_V

#define COL_PAIR(fg, bg) ((bg)<<4 | (fg))

enum colors
{
    COL_BLACK = 0,
    COL_BLUE,
    COL_GREEN,
    COL_CYAN,
    COL_RED,
    COL_MAGENTA,
    COL_BROWN,
    COL_LIGHTGRAY,
    COL_GRAY,
    COL_LIGHTBLUE,
    COL_LIGHTGREEN,
    COL_LIGHTCYAN,
    COL_LIGHTRED,
    COL_LIGHTMAGENTA,
    COL_YELLOW,
    COL_WHITE
};

#endif
