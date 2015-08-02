#include "libdos/stdio.h"
#include "libdos/conio.h"
#include "libdos/stdlib.h"
#include "libdos/string.h"
#include "libdos/dos.h"

int main(int argc, char **argv)
{
    setpage(1);
    gotoxy(0,0);
    clrscr();
    setcursor(0);
    setblink(0);
    setattr(0xb0);
    putchrp(' ', 80);
    putstr(" example title bar\n");
    setattr(0x07);
    gotoxy(0,1);
    char *test1 = malloc(7);
    sprintf(test1, "test%d\n", 1);
    char *test2 = malloc(10);
    int num = snprintf(test2, 10, "t:%4d testing\n", 42);
    printf("snprintf() needed %d bytes for 't: %d testing\\n'\n", num, 42);
    putstr("Hello world!\n\n$Bla$.\n");
    putstr(test1);
    putstr(test2);
    free(test1);
    free(test2);
    unsigned short ver = dosversion();
    printf("%s: DOS version: %hhu.%02hhu\n", argv[0],
	    (unsigned char)(ver >> 8), (unsigned char)(ver));
    putstr("Press ESC to quit.\n");
    int ch;
    while ((ch = getch()) != KEY_ESC)
    {
	printf("Got char: 0x%04x\n", ch);
    }
    setcursor(1);
    setblink(1);
    setpage(0);
    return 0;
}
