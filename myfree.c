#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>

// sub-function to fusion the block with free blocks that would be around it
void fusion(block a) ;
void *myfree(void *ptr)
{
    block toFree = ptr - sizeof(block) ;
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
        a->size += prev->size + sizeof(block) ;
        prev = NULL ;
    }
    if (next != NULL && next->free)
    {
        a->next = next->next ;
        a->size += next->size + sizeof(block) ;
        next = NULL ;
    }
    return ;
}