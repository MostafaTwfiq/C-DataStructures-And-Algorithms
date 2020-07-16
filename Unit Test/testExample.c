#include <stdio.h>
#include <string.h>
//#include "CUnit-2.1-3/CUnit/Headers/Basic.h"

/* Pointer to the file used by the tests. */
static FILE* temp_file = NULL;

/* The suite initialization function.
 * Opens the temporary file used by the tests.
 * Returns zero on success, non-zero otherwise.
 */
int init_suite1(void)
{
    if (NULL == (temp_file = fopen("temp.txt", "w+"))) {
        return -1;
    }
    else {
        return 0;
    }
}

/* The suite cleanup function.
 * Closes the temporary file used by the tests.
 * Returns zero on success, non-zero otherwise.
 */
int clean_suite1(void)
{
    if (0 != fclose(temp_file)) {
        return -1;
    }
    else {
        temp_file = NULL;
        return 0;
    }
}

/* Simple test of fprintf().
 * Writes test data to the temporary file and checks
 * whether the expected number of bytes were written.
 */
void testFPRINTF(void)
{
    int i1 = 10;

    if (NULL != temp_file) {
        //CU_ASSERT(0 == fprintf(temp_file, ""));
        //CU_ASSERT(2 == fprintf(temp_file, "Q\n"));
        //CU_ASSERT(7 == fprintf(temp_file, "i1 = %d", i1));
    }
}

/* Simple test of fread().
 * Reads the data previously written by testFPRINTF()
 * and checks whether the expected characters are present.
 * Must be run after testFPRINTF().
 */
void testFREAD(void)
{
    unsigned char buffer[20];

    if (NULL != temp_file) {
        rewind(temp_file);
      //  CU_ASSERT(9 == fread(buffer, sizeof(unsigned char), 20, temp_file));
       // CU_ASSERT(0 == strncmp(buffer, "Q\ni1 = 10", 9));
    }
}

/* The main() function for setting up and running the tests.
 * Returns a CUE_SUCCESS on successful running, another
 * CUnit error code on failure.
 */
int main()
{
   // CU_pSuite pSuite = NULL;

    /* initialize the CUnit test registry */
    //if (CUE_SUCCESS != CU_initialize_registry())
      //  return CU_get_error();

    /* add a suite to the registry */
   // pSuite = CU_add_suite("Suite_1", init_suite1, clean_suite1);
    //if (NULL == pSuite) {
      //  CU_cleanup_registry();
        //return CU_get_error();
    //}

    /* add the tests to the suite */
    /* NOTE - ORDER IS IMPORTANT - MUST TEST fread() AFTER fprintf() */
    //if ((NULL == CU_add_test(pSuite, "test of fprintf()", testFPRINTF)) ||
      //  (NULL == CU_add_test(pSuite, "test of fread()", testFREAD)))
    //{
     //   CU_cleanup_registry();
      //  return CU_get_error();
   // }

    //* Run all tests using the CUnit Basic interface */
    //CU_basic_set_mode(CU_BRM_VERBOSE);
    //CU_basic_run_tests();
    //CU_cleanup_registry();
    //return CU_get_error();
}

