#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>

#include "myfree.h"

void *myfree(void *ptr)
{
    block toFree = ptr - sizeB ;
    toFree->free = 1 ;
    fusion(toFree) ;
    return ;
}

void fusion(block a)
{
    block prev = a->prev ;
    block next = b->next ;
    
    if (prev && prev->free)
    {
        a->prev = prev->prev ;
        a->size += prev->size + sizeB ;
        prev = NULL ;
    }
    if (next != NULL && next->free)
    {
        a->next = next->next ;
        a->size += next->size + sizeB ;
        next = NULL ;
    }
    return ;
}