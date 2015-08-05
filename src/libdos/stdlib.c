#include "stdlib.h"

#include "string.h"

typedef struct hhdr hhdr;
struct hhdr
{
    void *next;
    int free;
};

extern char _heap;
static char *hbreak = &_heap;
static hhdr hhead = { &_heap, 0 };
static unsigned int randval = 1;

static void *newchunk(size_t size)
{
    if (size < 1024) size = 1024;
    hhdr *chunk = (hhdr *)hbreak;
    hbreak += size;
    chunk->next = hbreak;
    chunk->free = 1;
    return chunk;
}

void *malloc(size_t size)
{
    if (!size) return 0;
    if (size % sizeof(hhdr)) size += sizeof(hhdr) - (size % sizeof(hhdr));

    hhdr *hdr = &hhead;
    while ((char *)hdr->next < hbreak)
    {
	hdr = hdr->next;
	if (hdr->free && 
		(char *)hdr->next - (char *)hdr - sizeof(hhdr) >= size)
	{
	    if ((char *)hdr->next - (char *)hdr - 2*sizeof(hhdr) > size)
	    {
		hhdr *hdr2 = (hhdr *)((char *)hdr + sizeof(hhdr) + size);
		hdr2->free = 1;
		hdr2->next = hdr->next;
		hdr->next = hdr2;
	    }
	    hdr->free = 0;
	    return (char *)hdr + sizeof(hhdr);
	}
    }

    hdr->next = newchunk(size + sizeof(hhdr));
    return malloc(size);
}

void free(void *ptr)
{
    if (!ptr) return;
    hhdr *hdr = (hhdr *)((char *)ptr - sizeof(hhdr));
    hdr->free = 1;
    if ((void *)hdr != hhead.next)
    {
	hhdr *hdr2 = hhead.next;
	while (hdr2->next != hdr) hdr2 = hdr2->next;
	if (hdr2->free) hdr = hdr2;
    }
    hhdr *next = hdr->next;
    while ((char *)next < hbreak)
    {
	if (!next->free) break;
	hdr->next = next;
	next = next->next;
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
    size_t oldsize = (char *)hdr->next - (char *)ptr;
    if (size <= oldsize)
    {
	if (oldsize - size <= 2*sizeof(hhdr)) return ptr;
	hhdr *hdr2 = (hhdr *)((char *)ptr + size);
	hdr2->free = 0;
	hdr2->next = hdr->next;
	hdr->next = hdr2;
	free((char *)hdr2 + sizeof(hhdr));
	return ptr;
    }
    else
    {
	if ((char *)hdr->next < hbreak
		&& ((hhdr *)hdr->next)->free
		&& (char *)((hhdr *)hdr->next)->next - (char *)ptr >= oldsize)
	{
	    hdr->next = ((hhdr *)hdr->next)->next;
	    return realloc(ptr, size);
	}
	else
	{
	    void *ptr2 = malloc(size);
	    memcpy(ptr2, ptr, size);
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
    return (int)(randval & 0x7fffffff);
}

float _invSqrt(float x)
{
    float xhalf = 0.5f*x;
    union
    {
	float x;
	int i;
    } u;
    u.x = x;
    u.i = 0x5f3759df - (u.i >> 1);
    u.x = u.x * (1.5f - xhalf * u.x * u.x);
    return u.x;
}

double sqrt(double x)
{
    return 1.0f/_invSqrt(x);
}

