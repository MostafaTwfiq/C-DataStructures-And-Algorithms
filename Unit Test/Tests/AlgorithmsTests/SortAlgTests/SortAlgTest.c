#include "SortAlgTest.h"
#include "../../../CuTest/CuTest.h"
#include "../../../../System/Utils.h"
#include "../../../../Algorithms/Sorting/Headers/Sorting.h"


int intCompareFunSoAT1(const void *a, const void *b) {
    return *(int *) a - *(int *) b;
}

int intCompareFunSoAT2(const void *a, const void *b) {
    return *(int *) b - *(int *) a;
}


void testBubbleSort(CuTest *cuTest) {

    int arr[] = {5, 3, 9, 7, 6, 1, 2, 4, 10, 8};

    bubbleSort(NULL, 0, 0, NULL);
    CuAssertIntEquals(cuTest, NULL_POINTER, ERROR_TEST->errorCode);

    bubbleSort(arr, -1, 0, NULL);
    CuAssertIntEquals(cuTest, INVALID_ARG, ERROR_TEST->errorCode);

    bubbleSort(arr, 1, 0, NULL);
    CuAssertIntEquals(cuTest, INVALID_ARG, ERROR_TEST->errorCode);

    bubbleSort(arr, 1, 1, NULL);
    CuAssertIntEquals(cuTest, INVALID_ARG, ERROR_TEST->errorCode);

    bubbleSort(arr, 10, sizeof(int), intCompareFunSoAT1);

    for (int i = 0; i < 10; i++)
        CuAssertIntEquals(cuTest, i + 1, arr[i]);

    bubbleSort(arr, 10, sizeof(int), intCompareFunSoAT2);
    for (int i = 9; i >= 0; i--)
        CuAssertIntEquals(cuTest, i + 1, arr[9 - i]);

}


void testSelectionSort(CuTest *cuTest) {

    int arr[] = {5, 3, 9, 7, 6, 1, 2, 4, 10, 8};

    selectionSort(NULL, 0, 0, NULL);
    CuAssertIntEquals(cuTest, NULL_POINTER, ERROR_TEST->errorCode);

    selectionSort(arr, -1, 0, NULL);
    CuAssertIntEquals(cuTest, INVALID_ARG, ERROR_TEST->errorCode);

    selectionSort(arr, 1, 0, NULL);
    CuAssertIntEquals(cuTest, INVALID_ARG, ERROR_TEST->errorCode);

    selectionSort(arr, 1, 1, NULL);
    CuAssertIntEquals(cuTest, INVALID_ARG, ERROR_TEST->errorCode);

    selectionSort(arr, 10, sizeof(int), intCompareFunSoAT1);

    for (int i = 0; i < 10; i++)
        CuAssertIntEquals(cuTest, i + 1, arr[i]);

    selectionSort(arr, 10, sizeof(int), intCompareFunSoAT2);
    for (int i = 9; i >= 0; i--)
        CuAssertIntEquals(cuTest, i + 1, arr[9 - i]);

}


void testQuickSort(CuTest *cuTest) {

    int arr[] = {5, 3, 9, 7, 6, 1, 2, 4, 10, 8};

    quickSort(NULL, 0, 0, NULL);
    CuAssertIntEquals(cuTest, NULL_POINTER, ERROR_TEST->errorCode);

    quickSort(arr, -1, 0, NULL);
    CuAssertIntEquals(cuTest, INVALID_ARG, ERROR_TEST->errorCode);

    quickSort(arr, 1, 0, NULL);
    CuAssertIntEquals(cuTest, INVALID_ARG, ERROR_TEST->errorCode);

    quickSort(arr, 1, 1, NULL);
    CuAssertIntEquals(cuTest, INVALID_ARG, ERROR_TEST->errorCode);

    quickSort(arr, 10, sizeof(int), intCompareFunSoAT1);

    for (int i = 0; i < 10; i++)
        CuAssertIntEquals(cuTest, i + 1, arr[i]);

    quickSort(arr, 10, sizeof(int), intCompareFunSoAT2);
    for (int i = 9; i >= 0; i--)
        CuAssertIntEquals(cuTest, i + 1, arr[9 - i]);

}


void testMergeSort(CuTest *cuTest) {

    int arr[] = {5, 3, 9, 7, 6, 1, 2, 4, 10, 8};

    mergeSort(NULL, 0, 0, NULL);
    CuAssertIntEquals(cuTest, NULL_POINTER, ERROR_TEST->errorCode);

    mergeSort(arr, -1, 0, NULL);
    CuAssertIntEquals(cuTest, INVALID_ARG, ERROR_TEST->errorCode);

    mergeSort(arr, 1, 0, NULL);
    CuAssertIntEquals(cuTest, INVALID_ARG, ERROR_TEST->errorCode);

    mergeSort(arr, 1, 1, NULL);
    CuAssertIntEquals(cuTest, INVALID_ARG, ERROR_TEST->errorCode);

    mergeSort(arr, 10, sizeof(int), intCompareFunSoAT1);

    for (int i = 0; i < 10; i++)
        CuAssertIntEquals(cuTest, i + 1, arr[i]);

    mergeSort(arr, 10, sizeof(int), intCompareFunSoAT2);
    for (int i = 9; i >= 0; i--)
        CuAssertIntEquals(cuTest, i + 1, arr[9 - i]);

}


void testInsertionSort(CuTest *cuTest) {

    int arr[] = {5, 3, 9, 7, 6, 1, 2, 4, 10, 8};

    insertionSort(NULL, 0, 0, NULL);
    CuAssertIntEquals(cuTest, NULL_POINTER, ERROR_TEST->errorCode);

    insertionSort(arr, -1, 0, NULL);
    CuAssertIntEquals(cuTest, INVALID_ARG, ERROR_TEST->errorCode);

    insertionSort(arr, 1, 0, NULL);
    CuAssertIntEquals(cuTest, INVALID_ARG, ERROR_TEST->errorCode);

    insertionSort(arr, 1, 1, NULL);
    CuAssertIntEquals(cuTest, INVALID_ARG, ERROR_TEST->errorCode);

    insertionSort(arr, 10, sizeof(int), intCompareFunSoAT1);

    for (int i = 0; i < 10; i++)
        CuAssertIntEquals(cuTest, i + 1, arr[i]);


    insertionSort(arr, 10, sizeof(int), intCompareFunSoAT2);
    for (int i = 9; i >= 0; i--)
        CuAssertIntEquals(cuTest, i + 1, arr[9 - i]);

}


void testHeapSort(CuTest *cuTest) {

    int arr[] = {5, 3, 9, 7, 6, 1, 2, 4, 10, 8};

    heapSort(NULL, 0, 0, NULL);
    CuAssertIntEquals(cuTest, NULL_POINTER, ERROR_TEST->errorCode);

    heapSort(arr, -1, 0, NULL);
    CuAssertIntEquals(cuTest, INVALID_ARG, ERROR_TEST->errorCode);

    heapSort(arr, 1, 0, NULL);
    CuAssertIntEquals(cuTest, INVALID_ARG, ERROR_TEST->errorCode);

    heapSort(arr, 1, 1, NULL);
    CuAssertIntEquals(cuTest, INVALID_ARG, ERROR_TEST->errorCode);

    heapSort(arr, 10, sizeof(int), intCompareFunSoAT1);

    for (int i = 0; i < 10; i++)
        CuAssertIntEquals(cuTest, i + 1, arr[i]);

    heapSort(arr, 10, sizeof(int), intCompareFunSoAT2);
    for (int i = 9; i >= 0; i--)
        CuAssertIntEquals(cuTest, i + 1, arr[9 - i]);

}


void testCountingSort(CuTest *cuTest) {

    unsigned int arr1[] = {5, 3, 9, 7, 6, 1, 2, 4, 10, 8};
    unsigned int arr2[] = {5, 3, 9, 7, 6, 1, 2, 4, 10, 8};


    countingSortA(NULL, 0, 0, 0);
    CuAssertIntEquals(cuTest, NULL_POINTER, ERROR_TEST->errorCode);

    countingSortA(arr1, -1, 0, 0);
    CuAssertIntEquals(cuTest, INVALID_ARG, ERROR_TEST->errorCode);


    countingSortA(arr1, 1, 2, 1);
    CuAssertIntEquals(cuTest, INVALID_ARG, ERROR_TEST->errorCode);

    countingSortH(NULL, 0, 0, 0);
    CuAssertIntEquals(cuTest, NULL_POINTER, ERROR_TEST->errorCode);

    countingSortH(arr1, -1, 0, 0);
    CuAssertIntEquals(cuTest, INVALID_ARG, ERROR_TEST->errorCode);

    countingSortH(arr1, 1, 2, 1);
    CuAssertIntEquals(cuTest, INVALID_ARG, ERROR_TEST->errorCode);

    countingSortA(arr1, 10, 1, 10);

    for (int i = 0; i < 10; i++)
        CuAssertIntEquals(cuTest, i + 1, arr1[i]);


    countingSortH(arr2, 10, 1, 10);

    for (int i = 0; i < 10; i++)
        CuAssertIntEquals(cuTest, i + 1, arr2[i]);

}


CuSuite *createSortAlgTestsSuite(void) {

    CuSuite *suite = CuSuiteNew();

    SUITE_ADD_TEST(suite, testBubbleSort);
    SUITE_ADD_TEST(suite, testSelectionSort);
    SUITE_ADD_TEST(suite, testQuickSort);
    SUITE_ADD_TEST(suite, testMergeSort);
    SUITE_ADD_TEST(suite, testInsertionSort);
    SUITE_ADD_TEST(suite, testHeapSort);
    SUITE_ADD_TEST(suite, testCountingSort);

    return suite;

}


void sortAlgUnitTest(void) {

    ERROR_TEST = (ErrorTestStruct *) malloc(sizeof(ErrorTestStruct));

    CuString *output = CuStringNew();
    CuStringAppend(output, "**Sorting Algorithms Test**\n");

    CuSuite *suite = createSortAlgTestsSuite();

    CuSuiteRun(suite);
    CuSuiteSummary(suite, output);
    CuSuiteDetails(suite, output);
    printf("%s\n", output->buffer);

    free(ERROR_TEST);

}