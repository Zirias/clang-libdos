#include "libdos/stdio.h"
#include "libdos/conio.h"
#include "libdos/stdlib.h"
#include "libdos/string.h"
#include "libdos/dos.h"

int main(int argc, char **argv)
{
    setpage(1);
    gotoxy(0,0);
    setscroll(0);
    clrscr();
    setcursor(0);
    char *test1 = malloc(7);
    strcpy(test1, "test\n");
    char *test2 = malloc(7);
    strcpy(test2, "foot\n");
    putstr("Hello world!\n\n$Bla$.\n");
    putstr(test1);
    putstr(test2);
    free(test1);
    free(test2);
    unsigned short ver = dosversion();
    printf("%s: DOS version: %hhu.%02hhu\n", argv[0],
	    (unsigned char)(ver >> 8), (unsigned char)(ver));
    getch();
    setcursor(1);
    setpage(0);
    return 0;
}
