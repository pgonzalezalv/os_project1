#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <errno.h>

#include "test.h"
#include "mymalloc.h"

void *mymalloc(size_t size)
{
    if (head) /* nth mymalloc call*/
    {
        size_t sizeRounded = round4(size) ;
        void *found = findBlock(sizeRounded) ; //type QUESTION ????????
        splitBlock(found, sizeRounded) ;
        return found ;
    }
    else /* 1st mymalloc call*/
    {
        head = (block_header) sbrk(0) ;
        if (sbrk(SIZE_INIT + SIZE_BLOCK_HEADER) == (void*)-1)
        {
            return NULL ;
        }
        
        head->size = SIZE_INIT ;
        head->alloc = 0 ;
        
        return mymalloc(size) ;
    }

}

size_t round4(size_t num)
{
    size_t a = num % 4 ; // fonctionne ?? QUESTION !!!!!!!!!!!
    
    if (a==0)
    {
        return num ;
    }
    else
    {
        return (num + (4-a)) ;
    }
    
}
                       
void *findBlock(size_t size)
{
    block_header current = head ;
    block_header bestFit ;
    
    while (current)
    {
        if (current->size >= (size + SIZE_BLOCK_HEADER) && current->alloc==0)
        {
            if (current->size < bestFit->size)
            {
                bestFit = current ;
            }
        }
        current += ((current->size) * 2) ;
    }
    
    if (bestFit)
    {
    bestFit->alloc = 1 ;
    }
    return ((void*) bestFit) ;
}


void splitBlock(block_header B, size_t size)
{
    if (B->size > (size + SIZE_BLOCK_HEADER))
    {
        size_t currentsize = B->size ;
        B->size = size ;
        block_header next = B + ((size + SIZE_BLOCK_HEADER) * 2) ;
        next->size = currentsize - ((size  + SIZE_BLOCK_HEADER) * 2) ;
    }
}
