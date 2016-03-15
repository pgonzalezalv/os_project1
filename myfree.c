/*
 * Authors  : Pablo Gonzalez Alvarez (5243-13-00)
 *            Doriane Olewicki (3964-14-00)
 * due date : 16.03.16
 */

#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>

#include "header.h"

/*
 * FUNCTION MYFREE 
 *
 * This function frees the memory space pointed to
 * by ptr.
 */
void myfree(void *ptr)
{
    block_header *B = (block_header*) (ptr - SIZE_BLOCK_HEADER) ;
    B->alloc = 0 ;
}

