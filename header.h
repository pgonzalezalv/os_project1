/* STRUCTURES*/
typedef struct block_header block_header; /* by default a pointer */
struct block_header { /*structure representing the head*/
  unsigned int size : 29, /* int : value up to 2^29*/
  zero : 2,
  alloc : 1; /* boolean : 0 if free bloc, 1 if allocated bloc*/
};

/* MACROS */
#define SIZE_BLOCK_HEADER 4 // in BYTES

#define SIZE_INIT (1024 * 1024) /* MODIFY HERE HEAP SIZE*/

/* GLOBAL VARIABLES */
static block_header *head = NULL ;
static block_header *lastBlock = NULL ;
static void *tail = NULL ;
static int initialized;
static int initSize;

/* FUNCTIONS SIGNATURES */

// for mymalloc.c
void *mymalloc(size_t size) ;
void *findBlock(size_t size) ;
size_t round4(size_t num) ;
void splitBlock(block_header *B, size_t size) ;

// for mycalloc.c
void *mycalloc(size_t size) ;

// for myfree.c
void myfree(void *ptr) ;
