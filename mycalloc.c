/*
 * PROJECT 1
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

/*
 * FUNCTION MYCALLOC
 *
 * This function allocates "size" bytes and initializes them
 * to 0. Then, it returns a pointer to the allocated memory.
 */
void *mycalloc(size_t size)
{
  size_t *founded = (size_t*) malloc(size); // malloc call
  if (founded)
  {
    int i;
    for (i=0; i<size; i++) // go through the all allocated memory
    {
      founded[i] = 0; // initialization to 0
    }
  }

  return(founded);
}
