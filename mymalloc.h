#ifndef _MYMALLOC_H
#define _MYMALLOC_H

/* MACROS */
#define SIZE_BLOCK_HEADER 4 // in BYTES
#define SIZE_INIT 512

/* GLOBAL VARIABLES */
block_header head;

/* FUNCTIONS SIGNATURES */
void *mymalloc(size_t size) ;
void *findBlock(size_t size) ;
size_t round4(size_t num) ;
void splitBlock(block_header B, size_t size) ;

#endif
