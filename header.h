/* MACROS */
#define SIZE_BLOCK_HEADER 4 // in BYTES
//#define SIZE_INIT 512

/* STRUCTURES*/
typedef struct block_header *block_header; /* by default a pointer */
struct block_header { /*structure representing the head*/
    unsigned int size : 29, /* int : value up to 2^29*/
    zero : 2,
    alloc : 1; /* boolean : 0 if free bloc, 1 if allocated bloc*/
};

/* GLOBAL VARIABLES */
block_header head;
void *tail ; 
int initialized;
int initSize;
size_t SIZE_INIT ;


/* FUNCTIONS SIGNATURES */

// in mymalloc.c
void *mymalloc(size_t size) ;
void *findBlock(size_t size) ;
size_t round4(size_t num) ;
void splitBlock(block_header B, size_t size) ;

// in mycalloc.c
void *mycalloc(size_t size) ;

// in myfree.c
void myfree(void *ptr) ;
