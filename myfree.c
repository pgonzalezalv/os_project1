#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>

#include "myfree.h"

void myfree(void *ptr)
{
    ptr->alloc = 0 ;
}

void fusionForwards (block_header here)
{
    block_header next = here + here->size + SIZE_BLOCK_HEADER ;
    if (!next->alloc)
    {
        here->size += next->size + SIZE_BLOCK_HEADER ;
    }
    return ;
}

void fusionBackwards (block_header here)