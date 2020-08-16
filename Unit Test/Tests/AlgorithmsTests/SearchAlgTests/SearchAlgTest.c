#include "SearchAlgTest.h"
#include "../../../CuTest/CuTest.h"
#include "../../../../System/Utils.h"
#include "../../../../Algorithms/Searching/Headers/Searching.h"
#include "../../../../DataStructure/Lists/Headers/Vector.h"


int intCompareFunSeAT1(const void *a, const void *b) {
    return *(int *) a - *(int *) b;
}


void testLinearSearch(CuTest *cuTest) {

    int arr[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    int value;
    linearSearch(NULL, NULL, -1, 0, NULL);
    CuAssertIntEquals(cuTest, NULL_POINTER, ERROR_TEST->errorCode);

    linearSearch(arr, NULL, -1, 0, NULL);
    CuAssertIntEquals(cuTest, INVALID_ARG, ERROR_TEST->errorCode);

    linearSearch(arr, &value, -1, 0, NULL);
    CuAssertIntEquals(cuTest, INVALID_ARG, ERROR_TEST->errorCode);

    linearSearch(arr, &value, 0, 0, NULL);
    CuAssertIntEquals(cuTest, INVALID_ARG, ERROR_TEST->errorCode);

    linearSearch(arr, &value, 0, 1, NULL);
    CuAssertIntEquals(cuTest, INVALID_ARG, ERROR_TEST->errorCode);

    linearSearchGetLast(NULL, NULL, -1, 0, NULL);
    CuAssertIntEquals(cuTest, NULL_POINTER, ERROR_TEST->errorCode);

    linearSearchGetLast(arr, NULL, -1, 0, NULL);
    CuAssertIntEquals(cuTest, INVALID_ARG, ERROR_TEST->errorCode);

    linearSearchGetLast(arr, &value, -1, 0, NULL);
    CuAssertIntEquals(cuTest, INVALID_ARG, ERROR_TEST->errorCode);

    linearSearchGetLast(arr, &value, 0, 0, NULL);
    CuAssertIntEquals(cuTest, INVALID_ARG, ERROR_TEST->errorCode);

    linearSearchGetLast(arr, &value, 0, 1, NULL);
    CuAssertIntEquals(cuTest, INVALID_ARG, ERROR_TEST->errorCode);

    linearSearchGetAll(NULL, NULL, -1, 0, NULL);
    CuAssertIntEquals(cuTest, NULL_POINTER, ERROR_TEST->errorCode);

    linearSearchGetAll(arr, NULL, -1, 0, NULL);
    CuAssertIntEquals(cuTest, INVALID_ARG, ERROR_TEST->errorCode);

    linearSearchGetAll(arr, &value, -1, 0, NULL);
    CuAssertIntEquals(cuTest, INVALID_ARG, ERROR_TEST->errorCode);

    linearSearchGetAll(arr, &value, 0, 0, NULL);
    CuAssertIntEquals(cuTest, INVALID_ARG, ERROR_TEST->errorCode);

    linearSearchGetAll(arr, &value, 0, 1, NULL);
    CuAssertIntEquals(cuTest, INVALID_ARG, ERROR_TEST->errorCode);

    for (int i = 1; i <= 10; i++)
        CuAssertIntEquals(cuTest, i - 1, linearSearch(arr, &i, 10, sizeof(int), intCompareFunSeAT1));

    int arr2[] = {1, 1, 2, 2, 3, 3, 4, 4};
    value = 1;
    for (int i = 0; i < 8; i += 2, value++) {
        CuAssertIntEquals(cuTest, i, linearSearch(arr2, &value, 8, sizeof(int), intCompareFunSeAT1));
        CuAssertIntEquals(cuTest, i + 1, linearSearchGetLast(arr2, &value, 8, sizeof(int), intCompareFunSeAT1));
    }


    value = 1;
    Vector *indices = linearSearchGetAll(arr2, &value, 8, sizeof(int), intCompareFunSeAT1);
    CuAssertIntEquals(cuTest, 2, vectorGetLength(indices));
    CuAssertIntEquals(cuTest, 0, *(int *) vectorGet(indices, 0));
    CuAssertIntEquals(cuTest, 1, *(int *) vectorGet(indices, 1));
    destroyVector(indices);

    value = 3;
    indices = linearSearchGetAll(arr2, &value, 8, sizeof(int), intCompareFunSeAT1);
    CuAssertIntEquals(cuTest, 2, vectorGetLength(indices));
    CuAssertIntEquals(cuTest, 4, *(int *) vectorGet(indices, 0));
    CuAssertIntEquals(cuTest, 5, *(int *) vectorGet(indices, 1));
    destroyVector(indices);

}


void testBinarySearch(CuTest *cuTest) {

    int arr[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    int value;
    binarySearchI(NULL, NULL, -1, 0, NULL);
    CuAssertIntEquals(cuTest, NULL_POINTER, ERROR_TEST->errorCode);

    binarySearchI(arr, NULL, -1, 0, NULL);
    CuAssertIntEquals(cuTest, INVALID_ARG, ERROR_TEST->errorCode);

    binarySearchI(arr, &value, -1, 0, NULL);
    CuAssertIntEquals(cuTest, INVALID_ARG, ERROR_TEST->errorCode);

    binarySearchI(arr, &value, 0, 0, NULL);
    CuAssertIntEquals(cuTest, INVALID_ARG, ERROR_TEST->errorCode);

    binarySearchI(arr, &value, 0, 1, NULL);
    CuAssertIntEquals(cuTest, INVALID_ARG, ERROR_TEST->errorCode);

    binarySearchR(NULL, NULL, -1, 0, NULL);
    CuAssertIntEquals(cuTest, NULL_POINTER, ERROR_TEST->errorCode);

    binarySearchR(arr, NULL, -1, 0, NULL);
    CuAssertIntEquals(cuTest, INVALID_ARG, ERROR_TEST->errorCode);

    binarySearchR(arr, &value, -1, 0, NULL);
    CuAssertIntEquals(cuTest, INVALID_ARG, ERROR_TEST->errorCode);

    binarySearchR(arr, &value, 0, 0, NULL);
    CuAssertIntEquals(cuTest, INVALID_ARG, ERROR_TEST->errorCode);

    binarySearchR(arr, &value, 0, 1, NULL);
    CuAssertIntEquals(cuTest, INVALID_ARG, ERROR_TEST->errorCode);

    for (int i = 1; i <= 10; i++)
        CuAssertIntEquals(cuTest, i - 1, binarySearchI(arr, &i, 10, sizeof(int), intCompareFunSeAT1));

    for (int i = 1; i <= 10; i++)
        CuAssertIntEquals(cuTest, i - 1, binarySearchR(arr, &i, 10, sizeof(int), intCompareFunSeAT1));

}


void testTernarySearch(CuTest *cuTest) {

    int arr[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    int value;
    ternarySearchI(NULL, NULL, -1, 0, NULL);
    CuAssertIntEquals(cuTest, NULL_POINTER, ERROR_TEST->errorCode);

    ternarySearchI(arr, NULL, -1, 0, NULL);
    CuAssertIntEquals(cuTest, INVALID_ARG, ERROR_TEST->errorCode);

    ternarySearchI(arr, &value, -1, 0, NULL);
    CuAssertIntEquals(cuTest, INVALID_ARG, ERROR_TEST->errorCode);

    ternarySearchI(arr, &value, 0, 0, NULL);
    CuAssertIntEquals(cuTest, INVALID_ARG, ERROR_TEST->errorCode);

    ternarySearchI(arr, &value, 0, 1, NULL);
    CuAssertIntEquals(cuTest, INVALID_ARG, ERROR_TEST->errorCode);

    ternarySearchR(NULL, NULL, -1, 0, NULL);
    CuAssertIntEquals(cuTest, NULL_POINTER, ERROR_TEST->errorCode);

    ternarySearchR(arr, NULL, -1, 0, NULL);
    CuAssertIntEquals(cuTest, INVALID_ARG, ERROR_TEST->errorCode);

    ternarySearchR(arr, &value, -1, 0, NULL);
    CuAssertIntEquals(cuTest, INVALID_ARG, ERROR_TEST->errorCode);

    ternarySearchR(arr, &value, 0, 0, NULL);
    CuAssertIntEquals(cuTest, INVALID_ARG, ERROR_TEST->errorCode);

    ternarySearchR(arr, &value, 0, 1, NULL);
    CuAssertIntEquals(cuTest, INVALID_ARG, ERROR_TEST->errorCode);

    for (int i = 1; i <= 10; i++)
        CuAssertIntEquals(cuTest, i - 1, ternarySearchI(arr, &i, 10, sizeof(int), intCompareFunSeAT1));

    for (int i = 1; i <= 10; i++)
        CuAssertIntEquals(cuTest, i - 1, ternarySearchR(arr, &i, 10, sizeof(int), intCompareFunSeAT1));

}


void testJumpSearch(CuTest *cuTest) {

    int arr[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    int value;
    jumpSearch(NULL, NULL, -1, 0, NULL);
    CuAssertIntEquals(cuTest, NULL_POINTER, ERROR_TEST->errorCode);

    jumpSearch(arr, NULL, -1, 0, NULL);
    CuAssertIntEquals(cuTest, INVALID_ARG, ERROR_TEST->errorCode);

    jumpSearch(arr, &value, -1, 0, NULL);
    CuAssertIntEquals(cuTest, INVALID_ARG, ERROR_TEST->errorCode);

    jumpSearch(arr, &value, 0, 0, NULL);
    CuAssertIntEquals(cuTest, INVALID_ARG, ERROR_TEST->errorCode);

    jumpSearch(arr, &value, 0, 1, NULL);
    CuAssertIntEquals(cuTest, INVALID_ARG, ERROR_TEST->errorCode);

    for (int i = 1; i <= 10; i++)
        CuAssertIntEquals(cuTest, i - 1, jumpSearch(arr, &i, 10, sizeof(int), intCompareFunSeAT1));

}


void testExponentialSearch(CuTest *cuTest) {

    int arr[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    int value;
    exponentialSearch(NULL, NULL, -1, 0, NULL);
    CuAssertIntEquals(cuTest, NULL_POINTER, ERROR_TEST->errorCode);

    exponentialSearch(arr, NULL, -1, 0, NULL);
    CuAssertIntEquals(cuTest, INVALID_ARG, ERROR_TEST->errorCode);

    exponentialSearch(arr, &value, -1, 0, NULL);
    CuAssertIntEquals(cuTest, INVALID_ARG, ERROR_TEST->errorCode);

    exponentialSearch(arr, &value, 0, 0, NULL);
    CuAssertIntEquals(cuTest, INVALID_ARG, ERROR_TEST->errorCode);

    exponentialSearch(arr, &value, 0, 1, NULL);
    CuAssertIntEquals(cuTest, INVALID_ARG, ERROR_TEST->errorCode);

    for (int i = 1; i <= 10; i++)
        CuAssertIntEquals(cuTest, i - 1, exponentialSearch(arr, &i, 10, sizeof(int), intCompareFunSeAT1));

}


CuSuite *createSearchAlgTestsSuite(void) {

    CuSuite *suite = CuSuiteNew();

    SUITE_ADD_TEST(suite, testLinearSearch);
    SUITE_ADD_TEST(suite, testBinarySearch);
    SUITE_ADD_TEST(suite, testTernarySearch);
    SUITE_ADD_TEST(suite, testJumpSearch);
    SUITE_ADD_TEST(suite, testExponentialSearch);

    return suite;

}


void searchAlgUnitTest(void) {

    ERROR_TEST = (ErrorTestStruct *) malloc(sizeof(ErrorTestStruct));

    CuString *output = CuStringNew();
    CuStringAppend(output, "**Searching Algorithms Test**\n");

    CuSuite *suite = createSearchAlgTestsSuite();

    CuSuiteRun(suite);
    CuSuiteSummary(suite, output);
    CuSuiteDetails(suite, output);
    printf("%s\n", output->buffer);

    free(ERROR_TEST);

}