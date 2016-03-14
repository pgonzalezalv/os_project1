#ifndef _MAIN_H
#define _MAIN_H

/* GLOBAL VARIABLES */
extern int initialized;
extern int initSize;

/* STRUCTURES*/
typedef struct block_header *block_header; /* by default a pointer */
struct block_header { /*structure representing the head*/
    unsigned int size : 29, /* int : value up to 2^29*/
    zero : 2,
    alloc : 1; /* boolean : 0 if free bloc, 1 if allocated bloc*/
};

#endif
