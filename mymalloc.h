#ifndef _MYMALLOC_H
#define _MYMALLOC_H

/* structure representing the head*/
typedef struct block_header *block_header; /* by default a pointer */
struct block_header {
  unsigned int size : 29, /* int : value up to 2^29*/
               zero : 2,
               alloc : 1; /* boolean : 0 if free bloc, 1 if allocated bloc*/
};

/* MACROS */
#define SIZE_BLOCK_HEADER 32

/* GLOBAL VARIABLES */
extern int initialized;
extern block_header head;
// sub-function to get a pointer to a block that correspond
block *findBlock(size_t size) ;

// sub-function to split the block if necessary
void splitBlock(block ok, size_t size) ;

#endif
