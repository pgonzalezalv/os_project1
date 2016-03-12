#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include "header.h"

int main(int argc, char *argv[])
{
    int initSize ; // TO BE INITIALIZED
    
    
    // creation of a type to represent our HEAP
    typedef struct block blockT ;
    struct block
    {
        size_t size ; // size of the block
        int    free ; // 1 if the block is free, 0 if not
        block  next ; // pointer to the next block
    } ;
    
    block head ;
    head = sbrk(0) ; // save a pointer to the last break

    //sbrk((sizeof(block)) + initSize) ; // NEEDED ??
    //head->size = initSize ;
    
    // TEST1 : HEAP WELL CREATED
    if((sbrk((sizeof(block)) + initSize)) == (void*)-1)
    {
        return NULL ;
    }
    head->size = initSize ;

}
