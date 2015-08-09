int main();
void _getcinfo(void);

#ifndef NOARGV
#include <string.h>
#include <dos.h>

static void argstart(void) __attribute__((__noreturn__, __used__));
static char *progname(void);
static int argc = 0;
static char *argv[32];
#endif

__asm__ (
	"   .section	.comstartup		\n"
	"   .globl	__com__start		\n"
	"__com__start:				\n"
	"   call	_getcinfo		\n"
#ifdef NOARGV
	"   call	main			\n"
	"   jmp		exit			\n"
#else
	"   jmp		argstart		\n"
#endif
	"   .text				\n");

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

#ifndef NOARGV
static void argstart(void)
{
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
}

static char *progname(void)
{
    if (dosversion() < 0x0300) return "";

    unsigned int envaddr = (*(char *)0x2d << 8 | *(char *)0x2c) ;
    char *envptr = (char *)envaddr;

    while (*envptr) envptr += strlen(envptr) + 1;
    return envptr + 3;
}
#endif

