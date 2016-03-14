#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>

#include "test.h"

void myfree(void *ptr)
{
    block_header B = (block_header) ptr ;
    B->alloc = 0 ;
}

