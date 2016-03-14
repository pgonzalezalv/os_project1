#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>

void myfree(void *ptr)
{
    ptr->alloc = 0 ;
}

