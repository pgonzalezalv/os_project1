#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <errno.h>

#include "mymalloc.h"

void *mymalloc(size_t size) {
  if (initialized == 0) { /* 1st mymalloc call*/
    int initSize = argv[1];
  } else { /* nth mymalloc call*/
    /* code */
  }

}
