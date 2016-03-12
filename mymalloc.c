#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>

// sub-function to get a pointer to a block that correspond
block *findBlock(size_t size) ;

// sub-function to split the block if necessary
void splitBlock(block ok, size_t size) ;

void *mymalloc(size_t size)
{
    //HOW TO BRING HEAP HERE ??
    
    block founded = findBlock(size) ;
    
    if (founded == NULL)
    {
        errno = ENOMEN ;
        return NULL ;
    }
    
    if (founded->size != size + size(block))
    {
        splitBlock(founded, size) ;
    }
    
    return founded ;
}


block *findBlock(size_t size)
{
    block current = head ;
    
    while (current != NULL)
    {
        if ((current->size) >= (size + sizeof(block)) && (current->free==1))
        {
            current->free = 0 ;
            return(current) ;
        }
        current = current->next ;
    }
    return(NULL) ;
}


void splitBlock(block ok, size_t size) 
{
    block newNext ;
    newNext = ok + size + sizeof(block) ;
    newNext->size = ok->size - size - sizeof(block) ;
    newNext->next = ok->next ;
    newNext->free = 1 ;
    ok->next = newNext ;
    ok->size = size ;
    return ;
}
