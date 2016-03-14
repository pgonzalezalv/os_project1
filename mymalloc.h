#ifndef _MYMALLOC_H
#define _MYMALLOC_H

/* STRUCTURES*/
typedef struct block_header *block_header; /* by default a pointer */
struct block_header { /*structure representing the head*/
  unsigned int size : 29, /* int : value up to 2^29*/
               zero : 2,
               alloc : 1; /* boolean : 0 if free bloc, 1 if allocated bloc*/
};

/* MACROS */
#define SIZE_BLOCK_HEADER 4 // in BYTES

/* GLOBAL VARIABLES */
extern block_header head;

#endif

block_header findBlock(size_t size) ;
size_t round4(size_t num) ;
void splitBlock(block_header B, size_t size) ;
