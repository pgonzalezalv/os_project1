#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include "/home/tux/local/include/CUnit/Basic.h"
#include "/home/tux/local/include/CUnit/CUnit.h"

#include "header.h"

/*
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
 
    if (ptr == NULL)
    {
        CU_FAIL("Error : pointer hasn't been assigned. mymalloc failed.") ;
    }
}


void test_mymalloc_2(void)
{
    block_header *ptr = (block_header*) mymalloc((size_t) 32) ;

    if (ptr->size != 32)
    {
        CU_FAIL("Error : pointer hasn't got the right size. mymalloc failed.") ;
    }
}

void test_mymalloc_3(void)
{
    block_header *ptr = (block_header*) mymalloc((size_t) 31) ;
  
    if (ptr->size != 32)
    {
        CU_FAIL("Error : pointer hasn't got the right size. mymalloc failed.") ;
    }
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
    
    if(NULL == CU_add_test(pSuite, "test_calloc2_1", test_mymalloc_1))
    {
        CU_cleanup_registry();
        return CU_get_error();
    }

    CU_basic_run_tests();
    CU_cleanup_registry();
    return CU_get_error();
}
*/
int main(int argc, char *argv[])
{
    SIZE_INIT = 512 ;
    
    printf("Test please work \n") ;
    void* ptr_test1 = mymalloc((size_t) 32) ;
    if (ptr_test1 == NULL)
    {
        printf("ERREUR : mymalloc ne fonctionne pas") ;
    }
    else
    {
        printf("Work") ;
    }
    myfree(ptr_test1) ;
}



