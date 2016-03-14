#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include "../local/include/CUnit/Cunit.h"

#include "test.h"
#include "mymalloc.h"


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
    //CU_ASSERT_PTR_NOT_EQUAL(ptr, NULL) ;
    if (ptr == NULL)
    {
        CU_FAIL("Error : pointer hasn't been assigned. mymalloc failed.") ;
    }
}


int main(int argc, char *argv[])
{
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
    
    if(NULL == CU_add_test(pSuite, "test_calloc2_1", test_mymalloc_1)
       ) {
        CU_cleanup_registry();
        return CU_get_error();
    }

    CU_basic_run_tests();
    CU_cleanup_registry();
    return CU_get_error();
}



