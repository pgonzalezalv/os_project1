#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <errno.h>

#include "main.h"
#include "mymalloc.h"

void *mymalloc(size_t size)
{
    if (head) /* nth mymalloc call*/
    {
        size_t sizeRounded = round4(size) ;
        block_header founded = findBlock(sizeRounded) ;
        splitBlock(founded, sizeRounded) ;
        return(founded) ;
    }
    else /* 1st mymalloc call*/
    {
        head = sbrk(0) ;
        if (sbrk(512 + SIZE_BLOCK_HEADER) == (void*)-1)
        {
            return(NULL) ;
        }
        
        block_header init ;
        init->size = 512 ;
        init->alloc = 0 ;
        
        head = init ; // QUESTION : Comment stocker les blocs dans heapInit ??
        
        return(mymalloc(size)) ;
    }

}
                       
block_header findBlock(size_t size)
{
    block_header current = head ;
    block_header smallest ;
    
    while (current)
    {
        if (current->size >= (size + SIZE_BLOCK_HEADER) && !current->alloc)
        {
            if (current->size < smallest->size)
            {
                smallest = current ;
            }
        }
        current += current->size ;
    }
    
    if (smallest)
    {
    smallest->alloc = 1 ;
    }
    return(smallest) ;
}

size_t round4(size_t num)
{
    size_t a = num % 4 ;
    
    if (a==0)
    {
        return(num) ;
    }
    else
    {
        return(num + (4-a)) ;
    }
    
}

void splitBlock(block_header B, size_t size)
{
    if (B->size > (size + SIZE_BLOCK_HEADER))
    {
        size_t currentsize = B->size ;
        B->size = size + SIZE_BLOCK_HEADER ;
        block_header next = B + size + SIZE_BLOCK_HEADER ;
        next->size = currentsize - (size + SIZE_BLOCK_HEADER) - SIZE_BLOCK_HEADER ;
    }
    return ;
}
