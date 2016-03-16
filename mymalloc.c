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
    
    if (head && lastBlock) /* nth mymalloc call*/
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
        tail = head + (SIZE_INIT + SIZE_BLOCK_HEADER) ;
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
    int bestSize = SIZE_INIT + 1; // size of the memory zone the closest to the size asked
    int goodSize = 0 ; //boolean : is it the good size ?
    
    size_t unAlloc_size = 0 ;
    int atLimit = 0 ; //boolean : are we at the limit of the heap ?
    
    while (!atLimit) // while the end of the heap isn't reached
    {
        
        unAlloc_size = 0 ; // re-initialization at each loop
        
        while ((current + unAlloc_size)<lastBlock && (current + unAlloc_size)->alloc == 0 && unAlloc_size != size) // size of a memory zone unallocated
        {
            unAlloc_size += (current + unAlloc_size)->size ;//+ SIZE_BLOCK_HEADER ;
        }
        if (current == lastBlock || current + unAlloc_size == lastBlock) //if the current is the last block our the one before
        {
            atLimit = 1 ;
        }
        if (unAlloc_size == size) // if the sizes match
        {
            (current)->size = (unsigned int)size ;
            (current)->alloc = 1 ;
            return (current+ SIZE_BLOCK_HEADER) ;
        }
        else if (unAlloc_size > size && unAlloc_size < bestSize) // if the size is big enougth and smaller than bestSize
        {
            goodSize = 1 ;
            bestSize = unAlloc_size ;
            bestFit = (block_header*)current ;
            current += current->size ;
        }
        else if (unAlloc_size < size && !atLimit) // if the size is wrong but we can go further in the heap
        {
            current += unAlloc_size + (current + unAlloc_size)->size ; // make a step
        }
    }
    if(goodSize == 0) // no size or bestFit have been given
    {
        if ((void*)(current + size/4) > (void*)tail) // if we are at the end
        {
            return NULL ; // no place to stock the data
        }
        
        if (lastBlock->alloc == 0) // if last block hasn't been allocated
        {
            size_t sizeLast = lastBlock->size ;
            (current)->size = size ;
            (current)->alloc = 1 ;
            lastBlock = (block_header*)(current + size) ;
            (lastBlock)->size = (unsigned int)(sizeLast - size + unAlloc_size) ;
            return (current + SIZE_BLOCK_HEADER) ;
        }
        return NULL ;
    }
    else
    {
        (bestFit )->size = (unsigned int)bestSize ;
        (bestFit)->alloc = 1 ;
        return ((void*)bestFit + SIZE_BLOCK_HEADER) ;
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
    if (B->size > size)
    {
        size_t currentsize = B->size ; // memory of the block's size
        B->size = size ; // change the size of B
    
        // initialization of next block's informations
        (B + size + SIZE_BLOCK_HEADER)->size = currentsize - ((size)) ;
        (B + size + SIZE_BLOCK_HEADER)->alloc = 0 ;
    }
    return ;
}
