#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include "header.h"



int main(int argc, char *argv[])
{
    int initSize = argv[1] ; // TO BE INITIALIZED
    
    head = sbrk(0) ; // save a pointer to the last break

    //sbrk((sizeof(block)) + initSize) ; // NEEDED ??
    
    // TEST1 : HEAP WELL CREATED
    if((sbrk((sizeof(block)) + initSize)) == (void*)-1)
    {
        return NULL ;
    }
    head->size = initSize ;
    return 0 ;
    
}
