#ifndef BLOCK_H
#define BLOCK_H

typedef struct b {
	struct b *next;
} Block;

Block *newblock( int nelements, int nsize );
Block *getblock( Block **block, int nsize );
Block *putblock( Block **block, Block *bp );

#endif

