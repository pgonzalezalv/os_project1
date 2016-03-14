#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <errno.h>

#include "main.h"
#include "mymalloc.h"
#include "mycalloc.h"

void *mycalloc(size_t size)
{
    size_t* founded = malloc (size) ;
    if (founded)
    {
        for (size_t i=0; i<size; i++)
        {
            founded[i] = 0 ;
        }
    }
    return(founded) ;
}
