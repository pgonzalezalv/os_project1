#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>

#include "main.h"
#include "mymalloc.h"

int main(int argc, char *argv[]) {
  initSize = (int) argv[1]; // TO BE INITIALIZED

  head = sbrk(0); // save a pointer to the last break

  //sbrk((sizeof(block)) + initSize) ; // NEEDED ??

  // TEST1 : HEAP WELL CREATED
  if((sbrk(SIZE_BLOCK_HEADER + initSize)) == (void*)-1) {
    return NULL;
  }
  head->size = initSize;

  return 0;

}
