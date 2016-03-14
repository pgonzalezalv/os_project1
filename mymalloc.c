#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <errno.h>

#include "main.h"
#include "mymalloc.h"

void *mymalloc(size_t size) {
  if (initialized == 0) { /* 1st mymalloc call*/
    
  } else { /* nth mymalloc call*/
    /* code */
  }

}
