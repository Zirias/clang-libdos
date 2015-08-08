#include <stdlib.h>

static unsigned long long int randval = 1;

void srand(unsigned int seed)
{
    randval = seed;
}

int rand(void)
{
    randval *= 1103515245;
    randval += 12345;
    return (int)((randval / 65536) & 0x7fffffff);
}

