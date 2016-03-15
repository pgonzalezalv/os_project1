/*
 * PROJET 1 
 *
 * Authors  : Pablo Gonzalez Alvarez (5243-13-00)
 *            Doriane Olewicki (3964-14-00)
 * due date : 16.03.16
 */

#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <errno.h>

#include "test.h"
#include "mymalloc.h"

/* FUNCTION MYMALLOC
 *
 * This function allocates "size" bytes and returns a pointer
 * to the allocated memory.
 *
 * If it is the first call of mymalloc, the programme creates a
 * block "head" in the heap that limitates the memory mymalloc
 * can use.
 */
void *mymalloc(size_t size)
{
    if (head) /* nth mymalloc call*/
    {
        size_t sizeRounded = round4(size) ; // round the size
        void *found = findBlock(sizeRounded) ; // find the best fit for the allocation
        splitBlock(found, sizeRounded) ; // split the block into two smaller blocks if necessary
        return found ;
    }
    else /* 1st mymalloc call*/
    {
        head = (block_header) sbrk(0) ; //create the head
        if (sbrk(SIZE_INIT + SIZE_BLOCK_HEADER) == (void*)-1) // verification if the allocation is possible (enough place)
        {
            return NULL ;
        }
        
        // initialization of head's informations
        head->size = SIZE_INIT ;
        head->alloc = 0 ;
        
        return mymalloc(size) ; // recursive call
    }

}


/*
 * SUB-FUNCTION ROUND4
 *
 * This function rounds num to a multiple of 4, bigger or
 * equal to num.
 */
size_t round4(size_t num)
{
    size_t a = num % 4 ;
    
    if (a==0) // if it is a multiple of 4
    {
        return num ;
    }
    else
    {
        return (num + (4-a)) ;
    }
    
}


/*
 * SUB-FUNCTION FINDBLOCK
 * 
 * This function finds the best block possible to be allocated
 * by mymalloc. This means a block who is not allocated yet an 
 * whos size is the closest to the size needed.
 */
void *findBlock(size_t size)
{
    block_header current = head ; // initialization of the search
    block_header bestFit ; // block that will be returned
    
    while (current) // while we are in the allocable zone in the heap
    {
        if ((current->size >= (size + SIZE_BLOCK_HEADER) && current->alloc==0) && (current->size < bestFit->size))
        {
            bestFit = current ;
        }
        current += (current->size) ; // add a step
    }
    
    if (bestFit) // allocate the bestFit if it existe
    {
    bestFit->alloc = 1 ;
    }
    return ((void*) bestFit) ;
}

/*
 * SUB-FUNCTION SPLITBLOCK
 *
 * This function split a block into two pieces if the size of
 * this block is bigger than necessary.
 */
void splitBlock(block_header B, size_t size)
{
    if (B->size > (size + SIZE_BLOCK_HEADER))
    {
        size_t currentsize = B->size ; // memory of the block's size
        B->size = size ; // change the size of B
        block_header next = B + ((size + SIZE_BLOCK_HEADER)) ; // create a new block after B
        
        // initialization of next's informations
        next->size = currentsize - ((size  + SIZE_BLOCK_HEADER)) ;
        next->alloc = 0 ;
    }
    return ;
}
