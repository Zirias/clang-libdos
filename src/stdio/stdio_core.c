#include <stdio.h>

#include <errno.h>
#include <conio.h>
#include <string.h>

static const int stdinfd = 0;
static const int stdoutfd = 1;
static const int stderrfd = 2;

const FILE *stdin = &stdinfd;
const FILE *stdout = &stdoutfd;
const FILE *stderr = &stderrfd;

int puts(const char *s)
{
    putstr(s);
    putstr("\n");
    return 1;
}

int fputs(const char *s, FILE *stream)
{
    if (stream != stdout && stream != stderr)
    {
	errno = ENOSYS;
	return EOF;
    }
    return putstr(s);
}

void perror(const char *s)
{
    if (s && *s) printf("%s: %s\n", s, strerror(errno));
    else puts(strerror(errno));
}
