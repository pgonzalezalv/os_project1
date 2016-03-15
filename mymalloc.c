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

#include "header.h"

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
    if (size == 0)
    {
        return NULL ;
    }
    
    if (head) /* nth mymalloc call*/
    {
        size_t sizeRounded = round4(size) ; // round the size
        void *found = findBlock(sizeRounded) ; // find the best fit for the allocation
        splitBlock(found, sizeRounded) ; // split the block into two smaller blocks if necessary
        return found ;
    }
    else /* 1st mymalloc call*/
    {
        head = (block_header *) sbrk(0) ; //create the head
        void *err = sbrk(SIZE_INIT + SIZE_BLOCK_HEADER) ;
        if (err == (void*)-1) // verification if the allocation is possible (enough place)
        {
            return NULL ;
        }
        
        // initialization of head's informations
        head->size = SIZE_INIT ;
        head->alloc = 0 ;
        tail = (block_header *) head + (SIZE_INIT + SIZE_BLOCK_HEADER) ;
        lastBlock = head ;
        
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
    block_header *current = head ; // initialization of the search
    block_header *bestFit = NULL ; // block that will be returned
    size_t bestSize = SIZE_INIT + 1 ;
    int unAlloc_size = 0 ;
    int atLimit = 0 ; //boolean
    
    while (!atLimit)
    {
        
        unAlloc_size = 0 ;
        
        while ((current + unAlloc_size)<lastBlock && (current + unAlloc_size)->alloc == 0 && unAlloc_size<=size)
        {
            unAlloc_size += ((int)(current + unAlloc_size)->size) + SIZE_BLOCK_HEADER ;
        }
        
        if (current == lastBlock || current + unAlloc_size)
        {
            atLimit = 1 ;
        }
        
        if (unAlloc_size == size)
        {
            bestFit->size = size ;
            bestFit->alloc = 1 ;
            return (bestFit) ;
        }
        if (unAlloc_size < bestSize)
        {
            bestSize = unAlloc_size ;
            bestFit = current ;
            bestFit->size = unAlloc_size ; //done
        }
        if (unAlloc_size < size && !atLimit)
        {
            current += unAlloc_size + SIZE_BLOCK_HEADER + (current + unAlloc_size)->size ;
        }
    }
    if(bestFit)
    {
        bestFit->size = bestSize ;
        bestFit->alloc = 1 ;
        printf("bestFit de taille %ld puis %ld \n", bestFit, bestFit + SIZE_BLOCK_HEADER) ;
        return ((size_t)bestFit + SIZE_BLOCK_HEADER) ;
    }
    return NULL ;
}

/*
 * SUB-FUNCTION SPLITBLOCK
 *
 * This function split a block into two pieces if the size of
 * this block is bigger than necessary.
 */
void splitBlock(block_header *B, size_t size)
{
    if (B->size > (size + SIZE_BLOCK_HEADER))
    {
        size_t currentsize = B->size ; // memory of the block's size
        B->size = size ; // change the size of B
        block_header *next = B + (size + SIZE_BLOCK_HEADER) ; // create a new block after B
        
        // initialization of next's informations
        next->size = currentsize - ((size)) ;
        next->alloc = 0 ;
    }
    return ;
}
