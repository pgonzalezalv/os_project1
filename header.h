// creation of a type to represent our HEAP
typedef struct block
{
    size_t size ; // size of the block
    int    free ; // 1 if the block is free, 0 if not
    block  next ; // pointer to the next block
    block  prev ; // pointer to the previous block
} *block ;

block head ;

void *mymalloc(size_t size);
void *myfree(void *ptr);

#define sizeB 16 //TO DETERMINE, IS IT GOOD ?
