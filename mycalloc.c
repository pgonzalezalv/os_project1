#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <errno.h>

#include "main.h"
#include "mymalloc.h"

void *mycalloc(size_t size)
{
    size_t *founded = (size_t*) malloc(size) ;
    if (founded)
    {
        size_t i ;
        for (i=0; i<size; i++)
        {
            founded[i] = 0 ; // ptr bytes ou char ? QUESTION
        }
    }
    return(founded) ;
}