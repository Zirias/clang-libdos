#include "stdlib.h"

#include "string.h"
#include "errno.h"

#ifndef MALLOC_STACK_GAP
#define MALLOC_STACK_GAP 0x40
#endif

#define HDR_CNEXT(x) ((char *)((unsigned int)(x)->parts.next))
#define HDR_HNEXT(x) ((hhdr *)((unsigned int)(x)->parts.next))
#define HDR_FREE(x) ((x)->parts.free)

typedef union hhdr hhdr;
union hhdr {
    void *ptr;
    struct
    {
        unsigned short next;
        unsigned short free;
    } parts;
};

extern char _heap;
static char *hbreak = &_heap;
static hhdr hhead = { &_heap };
static unsigned long long int randval = 1;

unsigned short newchunk(size_t size)
{
    char *stack;
    __asm__("mov %%esp, %0": "=rm" (stack));
    if (hbreak + size > stack - MALLOC_STACK_GAP) return 0;
    if (size < 1024) size = 1024;
    hhdr *chunk = (hhdr *)hbreak;
    hbreak += size;
    if (hbreak > stack - MALLOC_STACK_GAP) hbreak = stack - MALLOC_STACK_GAP;
    chunk->ptr = hbreak;
    chunk->parts.free = 1;
    return (unsigned short)chunk;
}

void *malloc(size_t size)
{
    if (!size) return 0;
    if (size % sizeof(hhdr)) size += sizeof(hhdr) - (size % sizeof(hhdr));

    hhdr *hdr = &hhead;
    while (HDR_CNEXT(hdr) < hbreak)
    {
	hdr = HDR_HNEXT(hdr);
	if (HDR_FREE(hdr) && 
		HDR_CNEXT(hdr) - (char *)hdr - sizeof(hhdr) >= size)
	{
	    if (HDR_CNEXT(hdr) - (char *)hdr - 2*sizeof(hhdr) > size)
	    {
		hhdr *hdr2 = (hhdr *)((char *)hdr + sizeof(hhdr) + size);
		hdr2->parts.free = 1;
		hdr2->parts.next = hdr->parts.next;
		hdr->parts.next = (unsigned short)hdr2;
	    }
	    hdr->parts.free = 0;
	    return (char *)hdr + sizeof(hhdr);
	}
    }

    if (!(hdr->parts.next = newchunk(size + sizeof(hhdr))))
    {
        errno = ENOMEM;
        return 0;
    }
    return malloc(size);
}

void free(void *ptr)
{
    if (!ptr) return;
    hhdr *hdr = (hhdr *)((char *)ptr - sizeof(hhdr));
    hdr->parts.free = 1;
    if (hdr != (hhdr *)hhead.ptr)
    {
	hhdr *hdr2 = (hhdr *)hhead.ptr;
	while (hdr2->parts.next != (unsigned short)hdr) hdr2 = HDR_HNEXT(hdr2);
	if (HDR_FREE(hdr2)) hdr = hdr2;
    }
    hhdr *next = HDR_HNEXT(hdr);
    while ((char *)next < hbreak)
    {
	if (!HDR_FREE(next)) break;
	hdr->parts.next = (unsigned short)next;
	next = HDR_HNEXT(next);
    }
    if ((char *)next == hbreak) hbreak = (char *)hdr;
}

void *realloc(void *ptr, size_t size)
{
    if (!ptr) return malloc(size);
    if (!size)
    {
	free(ptr);
	return 0;
    }
    if (size % sizeof(hhdr)) size += sizeof(hhdr) - (size % sizeof(hhdr));
    hhdr *hdr = (hhdr *)((char *)ptr - sizeof(hhdr));
    size_t oldsize = HDR_CNEXT(hdr) - (char *)ptr;
    if (size <= oldsize)
    {
	if (oldsize - size <= 2*sizeof(hhdr)) return ptr;
	hhdr *hdr2 = (hhdr *)((char *)ptr + size);
	hdr2->ptr = hdr->ptr;
	hdr->ptr = hdr2;
	free((char *)hdr2 + sizeof(hhdr));
	return ptr;
    }
    else
    {
	if (HDR_CNEXT(hdr) < hbreak
		&& HDR_FREE(HDR_HNEXT(hdr)))
	{
	    hdr->ptr = HDR_HNEXT(HDR_HNEXT(hdr));
	    return realloc(ptr, size);
	}
	else
	{
	    void *ptr2 = malloc(size);
	    if (ptr2) memcpy(ptr2, ptr, size);
	    free(ptr);
	    return ptr2;
	}
    }
}

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

double sqrt(double x)
{
    double xhalf = 0.5*x;
    union
    {
	float x;
	int i;
    } u;
    u.x = x;
    u.i = 0x5f3759df - (u.i >> 1);
    x = u.x * (1.5 - xhalf * u.x * u.x);
    x = x * (1.5 - xhalf * x * x);
    x = x * (1.5 - xhalf * x * x);
    return 1.0/x;
}

