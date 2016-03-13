#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <errno.h>

#include "mymalloc.h"

void *mymalloc(size_t size)
{
    //HOW TO BRING HEAP HERE ??
    if (head)
    {
    
        block founded = findBlock(size) ;
    
        if (founded == NULL)
        {
            errno = ENOMEM ;
            return NULL ;
        }
    
        if (founded->size != size + sizeB)
        {
            splitBlock(founded, size) ;
        }
    
    return founded ;
    }
    else
    {
        errno = ENOMEM ;
        return NULL ;
    }
}


block *findBlock(size_t size)
{
    block current = head ;
    block prev    = NULL ;
    
    while (current)
    {
        if ((current->size) >= (size + sizeB) && (current->free==1))
        {
            current->free = 0 ;
            return(current) ;
        }
        current = current->next ;
        prev    = current ;
    }
    return(NULL) ;
}


void splitBlock(block ok, size_t size) 
{
    block newNext ;
    newNext       = ok + size + sizeB ; // WHATTTTTT ???
    newNext->size = ok->size - size - sizeB ;
    newNext->next = ok->next ;
    newNext->prev = ok ;
    newNext->free = 1 ;
    ok->next = newNext ;
    ok->size = size ;
    return ;
}
