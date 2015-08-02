#include "string.h"
#include "stdlib.h"

int main();
static char *progname(void);
void _getcinfo(void);

static int argc = 0;
static char *argv[32];

static void __attribute__((__noreturn__, __used__)) start(void)
{
    char *cmdline = (char *)0x81;
    argc = 1;
    argv[0] = progname();

    if ((argv[argc] = strtok(cmdline, " \t\r\n")))
    {
	++argc;
	while (argc < 32)
	{
	    if (!(argv[argc] = strtok(0, " \t\r\n"))) break;
	    ++argc;
	}
    }

    _getcinfo();
    exit(main(argc, argv));
}

void __attribute__((__noreturn__)) exit(int status)
{
    __asm__ volatile (
	    "mov    $0x4c, %%ah	    \n\t"
	    "int    $0x21	    \n\t"
	    :
	    : "a" (status)
	    );
    __builtin_unreachable();
}

short dosversion(void)
{
    short v1, v2;
    __asm__ (
	    "mov    $0x30, %%ah	    \n\t"
	    "int    $0x21	    \n\t"
	    : "=a" (v1)
	    :
	    : "bx", "cx"
	    );
    if (!(v1 & 0xff)) v1 = 0x0001;
    v2 = v1 >> 8 & 0xff;
    v1 = v1 << 8 | v2;
    return v1;
}

static char *progname(void)
{
    if (dosversion() < 0x0300) return "";

    unsigned int envaddr = (*(char *)0x2d << 8 | *(char *)0x2c) ;
    char *envptr = (char *)envaddr;

    while (*envptr) envptr += strlen(envptr) + 1;
    return envptr + 3;
}

