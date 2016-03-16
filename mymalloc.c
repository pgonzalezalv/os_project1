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
    /*
    if (size == 0)
    {
        return NULL ;
    }
    
    block_header *current = head ;
    void* ptr = (void*) head ;
    
    while(current<tail && (current->alloc=1 && current->size < size))
    {
        ptr += current->size + SIZE_BLOCK_HEADER ;
        current = (block_header *) ptr ;
    }
    if (current<tail)
    {
        current->alloc = 1 ;
        return((void*)current + SIZE_BLOCK_HEADER) ;
    }
    else
    {
        return NULL ;
    }
     */
    /*
    while(current<tail)
    {
        currentSize = 0 ;
        while ((current + currentSize < tail) && ((current + currentSize)->alloc==0))
        {
            currentSize += ((current + currentSize)->size + (size_t)SIZE_BLOCK_HEADER)/4 ;
        }
        
        current->size = currentSize ;
        
        if (currentSize >= size && currentSize < bestSize)
        {
            bestFit->size = currentSize ;
        }
        
        current += currentSize + (current + currentSize)->size ;
        printf("un tour");

        if (current != tail)
        {
            current += SIZE_BLOCK_HEADER ;
        }
    }
    if (bestFit == NULL)
    {
        return NULL ;
    }
    bestFit->alloc = 1 ;
    return ((void*)bestFit + SIZE_BLOCK_HEADER) ;
*/
    
    
    block_header *current = head ; // initialization of the search
    block_header *bestFit = NULL ; // block that will be returned
    int bestSize = 0 ;
    int goodSize = 0 ; //boolean : is it the good size ?
    
    size_t unAlloc_size = 0 ;
    int atLimit = 0 ; //boolean : are we at the limit of the heap ?
    
    while (!atLimit)
    {
        
        unAlloc_size = 0 ;
        
        while ((current + unAlloc_size)<lastBlock && (current + unAlloc_size)->alloc == 0 && unAlloc_size != size)
        {
            unAlloc_size += (current + unAlloc_size)->size + SIZE_BLOCK_HEADER ;
        }
        if (current == lastBlock || current + unAlloc_size == lastBlock)
        {
            atLimit = 1 ; // to be looked to
        }
        if (unAlloc_size == size)
        {
            current->size = size ;
            current->alloc = 1 ;
            return (current) ;
        }
        else if (unAlloc_size > size && unAlloc_size < bestSize)
        {
            goodSize = 1 ;
            bestSize = unAlloc_size ;
            bestFit = current ;
            current += current->size ;
        }
        else if (unAlloc_size < size && !atLimit)
        {
            current += unAlloc_size + SIZE_BLOCK_HEADER + (current + unAlloc_size)->size ;
        }
    }
    if(goodSize == 0)
    {
        printf("ETAPE 7.1 \n");
        printf("current = %ld ; size = %ld ; current + size = %ld ; tail = %ld \n",current, size, current + size, tail);
        if ((void*)(current + size/4) > (void*)tail)
        {
            printf("ETAPE 7.2 \n");
            return NULL ;
        }
        printf("ETAPE 7.3 \n");
        size_t sizeLast = lastBlock->size ;
        current->size = size ;
        current->alloc = 1 ;
        lastBlock = (block_header*)(current + size + SIZE_BLOCK_HEADER) ;
        lastBlock->size = sizeLast - size + unAlloc_size ;
        return (current + SIZE_BLOCK_HEADER) ;
        printf("ETAPE 8 \n");
    }
    
    if(bestFit)
    {
        printf("ETAPE 9 \n");
        bestFit->size = (size_t)bestSize ;
        printf("bestSize = %d\n", bestSize) ;
        bestFit->alloc = 1 ;
        printf("bestFit de taille %ld puis %ld \n", bestFit, (void*)bestFit + SIZE_BLOCK_HEADER) ;
        return ((void*)bestFit + SIZE_BLOCK_HEADER) ;
    }
    printf("ETAPE 10 \n");
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
    
        // initialization of next's informations
        (B + size + SIZE_BLOCK_HEADER)->size = currentsize - ((size)) ;
        (B + size + SIZE_BLOCK_HEADER)->alloc = 0 ;
    }
    return ;
}
