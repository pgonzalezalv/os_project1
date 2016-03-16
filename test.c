#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include "/home/tux/local/include/CUnit/Basic.h"
#include "/home/tux/local/include/CUnit/CUnit.h"

#include "header.h"


int nb_times_malloc_used = 0;
int let_malloc_fail = 0;

int initSuite(void) {
    return 0;
}

int cleanSuite(void) {
    return 0;
}

void test_mymalloc_1(void)
{
    void *ptr1 = mymalloc((size_t) 32) ;
    
    CU_ASSERT_PTR_NOT_EQUAL(ptr1, NULL) ;
}


void test_mymalloc_2(void)
{
    void *ptr2 = mymalloc((size_t) 32) ;
    block_header *b = (block_header*)(ptr2 - SIZE_BLOCK_HEADER) ;
    
    unsigned int size = b->size ;
    int alloc = b->alloc ;
    CU_ASSERT_EQUAL(size, 32 + SIZE_BLOCK_HEADER) ;
    CU_ASSERT_EQUAL(alloc, 1) ;
}

void test_mymalloc_3(void)
{
    block_header *ptr3 = (block_header*) mymalloc((size_t) 31) ;
  
    CU_ASSERT_NOT_EQUAL(ptr3, 32 + SIZE_BLOCK_HEADER) ;
}

void test_myfree(void)
{
    void *ptr4 = mymalloc((size_t) 32) ;
    myfree(ptr4) ;
    
    if (((block_header)(ptr- SIZE_BLOCK_HEADER))->alloc ==0)
    {
        CU_FAIL("Error : pointer hasn't been disassigned. mymalloc failed.") ;
    }
}

void test_mycalloc(void)
{
    block_header *ptr5 = (block_header*) mycalloc((size_t) 32) ;
    size_t i ;
    for (i=0; i<ptr->size; i++)
    {
        if (&ptr5[i*2] != NULL)
        {
            CU_FAIL("Error : pointed zone hasn't been initialized to 0 correctly. mymalloc failed.") ;
        }
    }
    myfree(ptr5) ;
    return ;
}

int main(int argc, char *argv[])
{
    //SIZE_INIT = (int) atoi (argv[1]) ;
    CU_pSuite pSuite = NULL;
    
    if(CUE_SUCCESS != CU_initialize_registry())
    {
        return CU_get_error();
    }
    
    pSuite = CU_add_suite("Suite de tests pour mymalloc, mycalloc et myFree", initSuite, cleanSuite);
    if(NULL == pSuite) {
        CU_cleanup_registry();
        return CU_get_error();
    }
    
    if(NULL == CU_add_test(pSuite, "test_mymalloc_1", test_mymalloc_1) ||
       NULL == CU_add_test(pSuite, "test_mymalloc_2", test_mymalloc_2) //||
       //NULL == CU_add_test(pSuite, "test_mymalloc_3", test_mymalloc_3) ||
       NULL == CU_add_test(pSuite, "test_myfree", test_myfree) //||
       //NULL == CU_add_test(pSuite, "test_myfree", test_myfree)
       )
        
    {
        CU_cleanup_registry();
        return CU_get_error();
    }

    CU_basic_run_tests();
    CU_cleanup_registry();
    return CU_get_error();
}




