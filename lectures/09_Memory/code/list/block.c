/*
**	block.c - memory management module.
**
**  pat hanrahan
*/

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "block.h"

static int tallocated = 0;
static int tmemory    = 0;

#define BLOCKSIZE 256

Block *
newblock( int nelements, int nsize )
{
    Block *base, *bp;
    
    base = (Block *)malloc( nelements * nsize );
    assert(base);

    tallocated += nelements * nsize;

    /* Link forward */
    bp = base;
    for( int i=1; i<nelements; i++ ) {
      Block *bpnext = (Block *)((char*)bp + nsize);
      bp->next = bpnext;
      bp = bpnext;
    }
    bp->next = NULL;

    return base;
}

Block *
getblock( Block **block, int nsize )
{
    Block *bp;

    if( *block == NULL )
        *block = newblock( BLOCKSIZE , nsize );

    bp = *block;
    *block = bp->next;

    tmemory++;
    return bp;
}

Block *
putblock( Block **block, Block *bp )
{
  if( bp ) {
    bp->next = *block;
    *block = bp;
  }
    
  tmemory--;
  return bp;
}
