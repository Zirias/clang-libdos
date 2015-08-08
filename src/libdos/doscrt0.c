#include "string.h"
#include "stdlib.h"

int main();
void _getcinfo(void);

#ifndef NOARGV
static char *progname(void);
static int argc = 0;
static char *argv[32];
#endif

static void __attribute__((__noreturn__, __used__, __section__(".comstartup")))
start(void)
{
    _getcinfo();

#ifdef NOARGV
    exit(main());
#else
    char *cmdline = (char *)0x81;
    argc = 1;
    argv[0] = progname();

    if ((argv[argc] = strqetok(cmdline, "\"'", "\\", " \t\r\n")))
    {
	++argc;
	while (argc < 32)
	{
	    if (!(argv[argc] = strqetok(0, "\"'", "\\", " \t\r\n"))) break;
	    ++argc;
	}
    }

    exit(main(argc, argv));
#endif

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

unsigned short dosversion(void)
{
    unsigned short v1, v2;
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

#ifndef NOARGV
static char *progname(void)
{
    if (dosversion() < 0x0300) return "";

    unsigned int envaddr = (*(char *)0x2d << 8 | *(char *)0x2c) ;
    char *envptr = (char *)envaddr;

    while (*envptr) envptr += strlen(envptr) + 1;
    return envptr + 3;
}
#endif

