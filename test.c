#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include "/home/tux/local/include/CUnit/Basic.h"
#include "/home/tux/local/include/CUnit/CUnit.h"

#include "header.h"


int nb_times_malloc_used = 0;
int let_malloc_fail = 0;

int init_suite1(void) {
    return 0;
}

int clean_suite1(void) {
    return 0;
}

void test_mymalloc_1(void)
{
    void *ptr = mymalloc((size_t) 32) ;
    
    CU_ASSERT_PTR_NOT_EQUAL(ptr, NULL) ;
    //if (ptr == NULL)
    //{
    //    CU_FAIL("Error : pointer hasn't been assigned. mymalloc failed.") ;
    //}
    //free(ptr) ;
}


void test_mymalloc_2(void)
{
    block_header *ptr = (block_header*) mymalloc((size_t) 32) ;
    block_header *b = (ptr - SIZE_BLOCK_HEADER) ;
    
    size_t size = b->size ;
    int alloc = b->alloc ;
    CU_ASSERT_EQUAL(size, 32) ;
    CU_ASSERT_EQUAL(alloc, 1) ;
    //if ((b)->size != 32)
    //{
    //    CU_FAIL("Error : pointer hasn't got the right size. mymalloc failed.") ;
    //}
    //free(ptr) ;
}

void test_mymalloc_3(void)
{
    block_header *ptr = (block_header*) mymalloc((size_t) 31) ;
  
    if (ptr->size != 32)
    {
        CU_FAIL("Error : pointer hasn't got the right size. mymalloc failed.") ;
    }
    free(ptr) ;
}

void test_myfree(void)
{
    void *ptr = mymalloc((size_t) 32) ;
    myfree(ptr) ;
    
    if (ptr != NULL)
    {
        CU_FAIL("Error : pointer hasn't been disassigned. mymalloc failed.") ;
    }
}

void test_mycalloc(void)
{
    block_header *ptr = (block_header*) mycalloc((size_t) 32) ;
    size_t i ;
    for (i=0; i<ptr->size; i++)
    {
        if (&ptr[i*2] != NULL)
        {
            CU_FAIL("Error : pointed zone hasn't been initialized to 0 correctly. mymalloc failed.") ;
        }
    }
    myfree(ptr) ;
    return ;
}

int main(int argc, char *argv[])
{
    SIZE_INIT = (size_t) atoi (argv[1]) ;
    CU_pSuite pSuite = NULL;
    
    if(CUE_SUCCESS != CU_initialize_registry())
    {
        return CU_get_error();
    }
    
    pSuite = CU_add_suite("Suite de tests pour calloc2", init_suite1, clean_suite1);
    if(NULL == pSuite) {
        CU_cleanup_registry();
        return CU_get_error();
    }
    
    if(NULL == CU_add_test(pSuite, "test_mymalloc_1", test_mymalloc_1) ||
       NULL == CU_add_test(pSuite, "test_mymalloc_2", test_mymalloc_2) //||
       //NULL == CU_add_test(pSuite, "test_mymalloc_3", test_mymalloc_3) ||
       //NULL == CU_add_test(pSuite, "test_myfree", test_myfree) ||
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




