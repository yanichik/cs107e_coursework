#include "malloc.h"

// A simple "bump allocator" that 
// just increments the heap segment to allocate space
// never recycles memory (free is a no-op)


extern int __bss_end__;

// Round up x to next multiple of n. Requires
// that n be a power of two to work correctly
#define roundup(x,n) (((x)+((n)-1))&(~((n)-1)))

static void *heap_next = (void *)&__bss_end__;

void *malloc(size_t nbytes) 
{
    nbytes = roundup(nbytes, 8);
    void *alloc = heap_next;
    heap_next += nbytes;

    return alloc;
}

void free(void *ptr) 
{
    // move along, nothing to see here
}

