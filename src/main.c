#include "libdos/stdio.h"
#include "libdos/conio.h"
#include "libdos/stdlib.h"
#include "libdos/string.h"

int main(int argc, char **argv)
{
    setpage(1);
    gotoxy(0,0);
    setscroll(0);
    clrscr();
    char *test1 = malloc(7);
    strcpy(test1, "test\n");
    char *test2 = malloc(7);
    strcpy(test2, "foot\n");
    putstr("Hello world!\n\nBla.\n");
    for (int i = 0; i < argc; ++i)
    {
	putstr(argv[i]);
	putstr("\n");
    }
    putstr(test1);
    putstr(test2);
    free(test1);
    free(test2);
    getch();
    setpage(0);
    return 0;
}
