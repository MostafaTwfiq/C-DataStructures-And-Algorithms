#include "ArraysAlgTest.h"
#include "../../../CuTest/CuTest.h"
#include "../../../../System/Utils.h"
#include "../../../../Algorithms/ArraysAlg/Headers/ArraysAlg.h"
#include "../../../../Algorithms/IntegersAlg/Headers/IntegerAlg.h"
#include "../../../../DataStructure/Lists/Headers/Vector.h"


void testArrayReverse(CuTest *cuTest) {

    int arr[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};

    reverseArray(NULL, 0, 0);
    CuAssertIntEquals(cuTest, NULL_POINTER, ERROR_TEST->errorCode);

    reverseArray(arr, -1, 0);
    CuAssertIntEquals(cuTest, INVALID_ARG, ERROR_TEST->errorCode);

    reverseArray(arr, 0, 0);
    CuAssertIntEquals(cuTest, INVALID_ARG, ERROR_TEST->errorCode);

    reverseArray(arr, 10, sizeof(int));
    for (int i = 10; i > 0; i--)
        CuAssertIntEquals(cuTest, i, arr[10 - i]);


}


void testMostFrequentArrValueH(CuTest *cuTest) {

    int arr[] = {1, 2, 2, 3, 4, 3, 3, 3, 2, 1};

    mostFrequentArrValueH(NULL, 0, 0, NULL, NULL);
    CuAssertIntEquals(cuTest, NULL_POINTER, ERROR_TEST->errorCode);

    mostFrequentArrValueH(arr, -1, 0, NULL, NULL);
    CuAssertIntEquals(cuTest, INVALID_ARG, ERROR_TEST->errorCode);

    mostFrequentArrValueH(arr, 0, 0, NULL, NULL);
    CuAssertIntEquals(cuTest, INVALID_ARG, ERROR_TEST->errorCode);

    mostFrequentArrValueH(arr, 0, 1, NULL, NULL);
    CuAssertIntEquals(cuTest, INVALID_ARG, ERROR_TEST->errorCode);

    mostFrequentArrValueH(arr, 0, 1, compareIntPointers, NULL);
    CuAssertIntEquals(cuTest, INVALID_ARG, ERROR_TEST->errorCode);

    CuAssertIntEquals(cuTest, 3, *(int *) mostFrequentArrValueH(arr, 10, sizeof(int), compareIntPointers, intHashFun));

    int arr2[] = {3, 3, 3, 3, 1, 1, 1, 1, 3, 1, 1, 1, 1, 4};
    CuAssertIntEquals(cuTest, 1, *(int *) mostFrequentArrValueH(arr2, 14, sizeof(int), compareIntPointers, intHashFun));

    int arr3[] = {0};
    CuAssertPtrEquals(cuTest, NULL, mostFrequentArrValueH(arr3, 0, sizeof(int), compareIntPointers, intHashFun));


}


void testMostFrequentArrValueA(CuTest *cuTest) {

    int arr[] = {1, 2, 2, 3, 4, 3, 3, 3, 2, 1};

    mostFrequentArrValueA(NULL, 0, 0, NULL);
    CuAssertIntEquals(cuTest, NULL_POINTER, ERROR_TEST->errorCode);

    mostFrequentArrValueA(arr, -1, 0, NULL);
    CuAssertIntEquals(cuTest, INVALID_ARG, ERROR_TEST->errorCode);

    mostFrequentArrValueA(arr, 0, 0, NULL);
    CuAssertIntEquals(cuTest, INVALID_ARG, ERROR_TEST->errorCode);

    mostFrequentArrValueA(arr, 0, 1, NULL);
    CuAssertIntEquals(cuTest, INVALID_ARG, ERROR_TEST->errorCode);

    CuAssertIntEquals(cuTest, 3, *(int *) mostFrequentArrValueA(arr, 10, sizeof(int), compareIntPointers));

    int arr2[] = {3, 3, 3, 3, 1, 1, 1, 1, 3, 1, 1, 1, 1, 4};
    CuAssertIntEquals(cuTest, 1, *(int *) mostFrequentArrValueA(arr2, 14, sizeof(int), compareIntPointers));

    int arr3[] = {0};
    CuAssertPtrEquals(cuTest, NULL, mostFrequentArrValueA(arr3, 0, sizeof(int), compareIntPointers));

}


int *printingArr;

void printItemFunArrAlgT(void *item) {
    *printingArr++ = *(int *) item;
}

void testPrintArr(CuTest *cuTest) {

    int arr[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};

    printArr(NULL, 0, 0, NULL);
    CuAssertIntEquals(cuTest, NULL_POINTER, ERROR_TEST->errorCode);

    printArr(arr, -1, 0, NULL);
    CuAssertIntEquals(cuTest, INVALID_ARG, ERROR_TEST->errorCode);

    printArr(arr, 0, 0, NULL);
    CuAssertIntEquals(cuTest, INVALID_ARG, ERROR_TEST->errorCode);

    printArr(arr, 0, 1, NULL);
    CuAssertIntEquals(cuTest, INVALID_ARG, ERROR_TEST->errorCode);

    printingArr = (int *) malloc(sizeof(int) * 10);
    int *tempPointer = printingArr;

    printArr(arr, 10, sizeof(int), printItemFunArrAlgT);


    for (int i = 0; i < 10; i++)
        CuAssertIntEquals(cuTest, i + 1, tempPointer[i]);

    free(tempPointer);

}


void testArrResize(CuTest *cuTest) {

    int *arr = (int *) malloc(sizeof(int) * 10);
    for (int i = 0; i < 10; i++)
        arr[i] = i + 1;

    arrResize(NULL, 0, 0);
    CuAssertIntEquals(cuTest, NULL_POINTER, ERROR_TEST->errorCode);

    arrResize(arr, 0, 0);
    CuAssertIntEquals(cuTest, INVALID_ARG, ERROR_TEST->errorCode);

    arrResize(arr, 1, 0);
    CuAssertIntEquals(cuTest, INVALID_ARG, ERROR_TEST->errorCode);

    arr = arrResize(arr, sizeof(int), 20);
    for (int i = 10; i < 20; i++)
        arr[i] = i + 1;

    for (int i = 0; i < 20; i++)
        CuAssertIntEquals(cuTest, i + 1, arr[i]);

    free(arr);

}


void testArrResizeAndCopy(CuTest *cuTest) {

    int *arr = (int *) malloc(sizeof(int) * 10);
    for (int i = 0; i < 10; i++)
        arr[i] = i + 1;

    arrResizeAndCpy(NULL, 0, 0, 0);
    CuAssertIntEquals(cuTest, NULL_POINTER, ERROR_TEST->errorCode);

    arrResizeAndCpy(arr, -1, 0, 0);
    CuAssertIntEquals(cuTest, INVALID_ARG, ERROR_TEST->errorCode);

    arrResizeAndCpy(arr, 0, 0, 0);
    CuAssertIntEquals(cuTest, INVALID_ARG, ERROR_TEST->errorCode);

    arrResizeAndCpy(arr, 0, 1, 0);
    CuAssertIntEquals(cuTest, INVALID_ARG, ERROR_TEST->errorCode);

    int *newArr = arrResizeAndCpy(arr, 10, sizeof(int), 20);

    for (int i = 10; i < 20; i++)
        newArr[i] = i + 1;

    for (int i = 0; i < 20; i++)
        CuAssertIntEquals(cuTest, i + 1, newArr[i]);

    free(arr);
    free(newArr);

}


void testArrResizeOfRangeAndCpy(CuTest *cuTest) {

    int *arr = (int *) malloc(sizeof(int) * 10);
    for (int i = 0; i < 10; i++)
        arr[i] = i + 1;

    arrResizeOfRangeAndCpy(NULL, 0, 0, 0, 0, 0);
    CuAssertIntEquals(cuTest, NULL_POINTER, ERROR_TEST->errorCode);

    arrResizeOfRangeAndCpy(arr, -1, 0, 0, 0, 0);
    CuAssertIntEquals(cuTest, INVALID_ARG, ERROR_TEST->errorCode);

    arrResizeOfRangeAndCpy(arr, 0, 0, 0, 0, 0);
    CuAssertIntEquals(cuTest, INVALID_ARG, ERROR_TEST->errorCode);

    arrResizeOfRangeAndCpy(arr, 0, 1, 0, -1, 0);
    CuAssertIntEquals(cuTest, INVALID_ARG, ERROR_TEST->errorCode);

    arrResizeOfRangeAndCpy(arr, 0, 1, 0, 0, 0);
    CuAssertIntEquals(cuTest, INVALID_ARG, ERROR_TEST->errorCode);

    int *newArr = arrResizeOfRangeAndCpy(arr, 10, sizeof(int), 5, 9, 10);

    for (int i = 5; i < 10; i++)
        newArr[i] = i + 6;

    for (int i = 0; i < 10; i++)
        CuAssertIntEquals(cuTest, i + 6, newArr[i]);

    free(arr);
    free(newArr);

}


void intCopyFunArrAlgT(const void *s1, const void *s2) {
    memcpy((void *) s1, (void *) s2, sizeof(int));
}


void testArrResizeAndCpyC(CuTest *cuTest) {

    int *arr = (int *) malloc(sizeof(int) * 10);
    for (int i = 0; i < 10; i++)
        arr[i] = i + 1;

    arrResizeAndCpyC(NULL, 0, 0, 0, NULL);
    CuAssertIntEquals(cuTest, NULL_POINTER, ERROR_TEST->errorCode);

    arrResizeAndCpyC(arr, -1, 0, 0, NULL);
    CuAssertIntEquals(cuTest, INVALID_ARG, ERROR_TEST->errorCode);

    arrResizeAndCpyC(arr, 0, 0, 0, intCopyFunArrAlgT);
    CuAssertIntEquals(cuTest, INVALID_ARG, ERROR_TEST->errorCode);

    arrResizeAndCpyC(arr, 0, 1, 0, intCopyFunArrAlgT);
    CuAssertIntEquals(cuTest, INVALID_ARG, ERROR_TEST->errorCode);

    arrResizeAndCpyC(arr, 0, 1, 1, intCopyFunArrAlgT);
    CuAssertIntEquals(cuTest, INVALID_ARG, ERROR_TEST->errorCode);

    int *newArr = arrResizeAndCpyC(arr, 10, sizeof(int), 20, intCopyFunArrAlgT);

    for (int i = 10; i < 20; i++)
        newArr[i] = i + 1;

    for (int i = 0; i < 20; i++)
        CuAssertIntEquals(cuTest, i + 1, newArr[i]);

    free(arr);
    free(newArr);

}


void testArrResizeOfRangeAndCpyC(CuTest *cuTest) {

    int *arr = (int *) malloc(sizeof(int) * 10);
    for (int i = 0; i < 10; i++)
        arr[i] = i + 1;

    arrResizeOfRangeAndCpyC(NULL, 0, 0, 0, 0, 0, NULL);
    CuAssertIntEquals(cuTest, NULL_POINTER, ERROR_TEST->errorCode);

    arrResizeOfRangeAndCpyC(arr, -1, 0, 0, 0, 0, NULL);
    CuAssertIntEquals(cuTest, INVALID_ARG, ERROR_TEST->errorCode);

    arrResizeOfRangeAndCpyC(arr, 0, 0, 0, 0, 0, intCopyFunArrAlgT);
    CuAssertIntEquals(cuTest, INVALID_ARG, ERROR_TEST->errorCode);

    arrResizeOfRangeAndCpyC(arr, 0, 1, 0, -1, 0, intCopyFunArrAlgT);
    CuAssertIntEquals(cuTest, INVALID_ARG, ERROR_TEST->errorCode);

    arrResizeOfRangeAndCpyC(arr, 0, 1, 0, 0, 0, intCopyFunArrAlgT);
    CuAssertIntEquals(cuTest, INVALID_ARG, ERROR_TEST->errorCode);

    arrResizeOfRangeAndCpyC(arr, 0, 1, 0, 0, 1, intCopyFunArrAlgT);
    CuAssertIntEquals(cuTest, INVALID_ARG, ERROR_TEST->errorCode);

    int *newArr = arrResizeOfRangeAndCpyC(arr, 10, sizeof(int), 5, 9, 10, intCopyFunArrAlgT);

    for (int i = 5; i < 10; i++)
        newArr[i] = i + 6;

    for (int i = 0; i < 10; i++)
        CuAssertIntEquals(cuTest, i + 6, newArr[i]);

    free(arr);
    free(newArr);

}


void testArrCopy(CuTest *cuTest) {

    int *arr = (int *) malloc(sizeof(int) * 10);
    for (int i = 0; i < 10; i++)
        arr[i] = i + 1;

    arrCopy(NULL, 0, 0);
    CuAssertIntEquals(cuTest, NULL_POINTER, ERROR_TEST->errorCode);

    arrCopy(arr, -1, 0);
    CuAssertIntEquals(cuTest, INVALID_ARG, ERROR_TEST->errorCode);

    arrCopy(arr, 0, 0);
    CuAssertIntEquals(cuTest, INVALID_ARG, ERROR_TEST->errorCode);

    int *newArr = arrCopy(arr, 10, sizeof(int));

    for (int i = 0; i < 10; i++)
        CuAssertIntEquals(cuTest, i + 1, newArr[i]);

    free(arr);
    free(newArr);

}


void testArrCopyC(CuTest *cuTest) {

    int *arr = (int *) malloc(sizeof(int) * 10);
    for (int i = 0; i < 10; i++)
        arr[i] = i + 1;

    arrCopyC(NULL, 0, 0, NULL);
    CuAssertIntEquals(cuTest, NULL_POINTER, ERROR_TEST->errorCode);

    arrCopyC(arr, 0, 0, NULL);
    CuAssertIntEquals(cuTest, INVALID_ARG, ERROR_TEST->errorCode);

    arrCopyC(arr, -1, 0, intCopyFunArrAlgT);
    CuAssertIntEquals(cuTest, INVALID_ARG, ERROR_TEST->errorCode);

    arrCopyC(arr, 0, 0, intCopyFunArrAlgT);
    CuAssertIntEquals(cuTest, INVALID_ARG, ERROR_TEST->errorCode);

    int *newArr = arrCopyC(arr, 10, sizeof(int), intCopyFunArrAlgT);

    for (int i = 0; i < 10; i++)
        CuAssertIntEquals(cuTest, i + 1, newArr[i]);

    free(arr);
    free(newArr);

}


void testArrCopyOfRange(CuTest *cuTest) {

    int *arr = (int *) malloc(sizeof(int) * 10);
    for (int i = 0; i < 10; i++)
        arr[i] = i + 1;

    arrCopyOfRange(NULL, 0, 0, 0, 0);
    CuAssertIntEquals(cuTest, NULL_POINTER, ERROR_TEST->errorCode);

    arrCopyOfRange(arr, -1, 0, 0, 0);
    CuAssertIntEquals(cuTest, INVALID_ARG, ERROR_TEST->errorCode);

    arrCopyOfRange(arr, 0, 0, 0, 0);
    CuAssertIntEquals(cuTest, INVALID_ARG, ERROR_TEST->errorCode);

    arrCopyOfRange(arr, 0, 1, 0, -1);
    CuAssertIntEquals(cuTest, INVALID_ARG, ERROR_TEST->errorCode);

    int *newArr = arrCopyOfRange(arr, 10, sizeof(int), 5, 9);

    for (int i = 0; i < 5; i++)
        CuAssertIntEquals(cuTest, i + 6, newArr[i]);

    free(arr);
    free(newArr);

}


void testArrCopyOfRangeC(CuTest *cuTest) {

    int *arr = (int *) malloc(sizeof(int) * 10);
    for (int i = 0; i < 10; i++)
        arr[i] = i + 1;

    arrCopyOfRangeC(NULL, 0, 0, 0, 0, NULL);
    CuAssertIntEquals(cuTest, NULL_POINTER, ERROR_TEST->errorCode);

    arrCopyOfRangeC(arr, 0, 0, 0, 0, NULL);
    CuAssertIntEquals(cuTest, INVALID_ARG, ERROR_TEST->errorCode);

    arrCopyOfRangeC(arr, -1, 0, 0, 0, intCopyFunArrAlgT);
    CuAssertIntEquals(cuTest, INVALID_ARG, ERROR_TEST->errorCode);

    arrCopyOfRangeC(arr, 0, 0, 0, -1, intCopyFunArrAlgT);
    CuAssertIntEquals(cuTest, INVALID_ARG, ERROR_TEST->errorCode);

    arrCopyOfRangeC(arr, 0, 1, 0, -1, intCopyFunArrAlgT);
    CuAssertIntEquals(cuTest, INVALID_ARG, ERROR_TEST->errorCode);

    int *newArr = arrCopyOfRangeC(arr, 10, sizeof(int), 5, 9, intCopyFunArrAlgT);

    for (int i = 0; i < 5; i++)
        CuAssertIntEquals(cuTest, i + 6, newArr[i]);

    free(arr);
    free(newArr);

}


void testFillArr(CuTest *cuTest) {

    int *arr = (int *) malloc(sizeof(int) * 10);
    for (int i = 0; i < 10; i++)
        arr[i] = i + 1;

    int tempValue = 1;
    fillArr(NULL, NULL, 0, 0);
    CuAssertIntEquals(cuTest, NULL_POINTER, ERROR_TEST->errorCode);

    fillArr(arr, NULL, 0, 0);
    CuAssertIntEquals(cuTest, INVALID_ARG, ERROR_TEST->errorCode);

    fillArr(arr, &tempValue, -1, 0);
    CuAssertIntEquals(cuTest, INVALID_ARG, ERROR_TEST->errorCode);

    fillArr(arr, &tempValue, 0, 0);
    CuAssertIntEquals(cuTest, INVALID_ARG, ERROR_TEST->errorCode);


    fillArr(arr, &tempValue, 10, sizeof(int));

    for (int i = 0; i < 10; i++)
        CuAssertIntEquals(cuTest, 1, arr[i]);


    free(arr);

}


void testFillArrC(CuTest *cuTest) {

    int *arr = (int *) malloc(sizeof(int) * 10);
    for (int i = 0; i < 10; i++)
        arr[i] = i + 1;

    int tempValue = 1;
    fillArrC(NULL, NULL, 0, 0, NULL);
    CuAssertIntEquals(cuTest, NULL_POINTER, ERROR_TEST->errorCode);

    fillArrC(arr, NULL, 0, 0, NULL);
    CuAssertIntEquals(cuTest, INVALID_ARG, ERROR_TEST->errorCode);

    fillArrC(arr, &tempValue, 0, 0, NULL);
    CuAssertIntEquals(cuTest, INVALID_ARG, ERROR_TEST->errorCode);

    fillArrC(arr, &tempValue, -1, 0, intCopyFunArrAlgT);
    CuAssertIntEquals(cuTest, INVALID_ARG, ERROR_TEST->errorCode);

    fillArrC(arr, &tempValue, 0, 0, intCopyFunArrAlgT);
    CuAssertIntEquals(cuTest, INVALID_ARG, ERROR_TEST->errorCode);


    fillArrC(arr, &tempValue, 10, sizeof(int), intCopyFunArrAlgT);

    for (int i = 0; i < 10; i++)
        CuAssertIntEquals(cuTest, 1, arr[i]);


    free(arr);

}


void testFillArrOfRange(CuTest *cuTest) {

    int *arr = (int *) malloc(sizeof(int) * 10);
    for (int i = 0; i < 10; i++)
        arr[i] = i + 1;

    int tempValue = 1;
    fillArrOfRange(NULL, NULL, 0, 0, 0, 0);
    CuAssertIntEquals(cuTest, NULL_POINTER, ERROR_TEST->errorCode);

    fillArrOfRange(arr, NULL, 0, 0, 0, 0);
    CuAssertIntEquals(cuTest, INVALID_ARG, ERROR_TEST->errorCode);

    fillArrOfRange(arr, &tempValue, -1, 0, 0, 0);
    CuAssertIntEquals(cuTest, INVALID_ARG, ERROR_TEST->errorCode);

    fillArrOfRange(arr, &tempValue, 0, 0, 0, 0);
    CuAssertIntEquals(cuTest, INVALID_ARG, ERROR_TEST->errorCode);

    fillArrOfRange(arr, &tempValue, 0, 1, 0, -1);
    CuAssertIntEquals(cuTest, INVALID_ARG, ERROR_TEST->errorCode);


    fillArrOfRange(arr, &tempValue, 10, sizeof(int), 5, 9);

    for (int i = 0; i < 5; i++)
        CuAssertIntEquals(cuTest, i + 1, arr[i]);

    for (int i = 5; i < 10; i++)
        CuAssertIntEquals(cuTest, 1, arr[i]);

    free(arr);

}


void testFillArrOfRangeC(CuTest *cuTest) {

    int *arr = (int *) malloc(sizeof(int) * 10);
    for (int i = 0; i < 10; i++)
        arr[i] = i + 1;

    int tempValue = 1;
    fillArrOfRangeC(NULL, NULL, 0, 0, 0, 0, NULL);
    CuAssertIntEquals(cuTest, NULL_POINTER, ERROR_TEST->errorCode);

    fillArrOfRangeC(arr, NULL, 0, 0, 0, 0, NULL);
    CuAssertIntEquals(cuTest, INVALID_ARG, ERROR_TEST->errorCode);

    fillArrOfRangeC(arr, &tempValue, 0, 0, 0, 0, NULL);
    CuAssertIntEquals(cuTest, INVALID_ARG, ERROR_TEST->errorCode);

    fillArrOfRangeC(arr, &tempValue, -1, 0, 0, 0, intCopyFunArrAlgT);
    CuAssertIntEquals(cuTest, INVALID_ARG, ERROR_TEST->errorCode);

    fillArrOfRangeC(arr, &tempValue, 0, 0, 0, 0, intCopyFunArrAlgT);
    CuAssertIntEquals(cuTest, INVALID_ARG, ERROR_TEST->errorCode);

    fillArrOfRangeC(arr, &tempValue, 0, 1, 0, -1, intCopyFunArrAlgT);
    CuAssertIntEquals(cuTest, INVALID_ARG, ERROR_TEST->errorCode);


    fillArrOfRangeC(arr, &tempValue, 10, sizeof(int), 5, 9, intCopyFunArrAlgT);

    for (int i = 0; i < 5; i++)
        CuAssertIntEquals(cuTest, i + 1, arr[i]);

    for (int i = 5; i < 10; i++)
        CuAssertIntEquals(cuTest, 1, arr[i]);

    free(arr);

}


void testArrCompare(CuTest *cuTest) {

    int arr1[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    int arr2[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    int arr3[] = {1, 2, 3, 4, 5, 5, 7, 8, 9, 10};

    arrCompare(NULL, 0, NULL, 0, 0, NULL);
    CuAssertIntEquals(cuTest, NULL_POINTER, ERROR_TEST->errorCode);

    arrCompare(arr1, 0, NULL, 0, 0, NULL);
    CuAssertIntEquals(cuTest, NULL_POINTER, ERROR_TEST->errorCode);

    arrCompare(arr1, 0, arr2, 0, 0, NULL);
    CuAssertIntEquals(cuTest, INVALID_ARG, ERROR_TEST->errorCode);

    arrCompare(arr1, -1, arr2, -1, 0, compareIntPointers);
    CuAssertIntEquals(cuTest, INVALID_ARG, ERROR_TEST->errorCode);

    arrCompare(arr1, 0, arr2, 0, 0, compareIntPointers);
    CuAssertIntEquals(cuTest, INVALID_ARG, ERROR_TEST->errorCode);

    CuAssertIntEquals(cuTest, 1, arrCompare(arr1, 10, arr2, 10, sizeof(int), compareIntPointers));
    CuAssertIntEquals(cuTest, 0, arrCompare(arr1, 10, arr3, 10, sizeof(int), compareIntPointers));
    CuAssertIntEquals(cuTest, 0, arrCompare(arr1, 10, arr2, 9, sizeof(int), compareIntPointers));
    CuAssertIntEquals(cuTest, 1, arrCompare(arr1, 0, arr2, 0, sizeof(int), compareIntPointers));

}


void testArrCompareOfRange(CuTest *cuTest) {

    int arr1[] = {1, 2, 3, 4, 11, 12, 13, 8, 9, 10};
    int arr2[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};

    arrCompareOfRange(NULL, 0, NULL, 0, 0, 0, 0, NULL);
    CuAssertIntEquals(cuTest, NULL_POINTER, ERROR_TEST->errorCode);

    arrCompareOfRange(arr1, 0, NULL, 0, 0, 0, 0, NULL);
    CuAssertIntEquals(cuTest, NULL_POINTER, ERROR_TEST->errorCode);

    arrCompareOfRange(arr1, 0, arr2, 0, 0, 0, 0, NULL);
    CuAssertIntEquals(cuTest, INVALID_ARG, ERROR_TEST->errorCode);

    arrCompareOfRange(arr1, -1, arr2, -1, 0, 0, 0, compareIntPointers);
    CuAssertIntEquals(cuTest, INVALID_ARG, ERROR_TEST->errorCode);

    arrCompareOfRange(arr1, 0, arr2, 0, 0, 0, 0, compareIntPointers);
    CuAssertIntEquals(cuTest, INVALID_ARG, ERROR_TEST->errorCode);

    arrCompareOfRange(arr1, 0, arr2, 0, 0, 0, -1, compareIntPointers);
    CuAssertIntEquals(cuTest, INVALID_ARG, ERROR_TEST->errorCode);

    CuAssertIntEquals(cuTest, 0, arrCompareOfRange(arr1, 10, arr2, 10, sizeof(int), 0, 9, compareIntPointers));
    CuAssertIntEquals(cuTest, 1, arrCompareOfRange(arr1, 10, arr2, 10, sizeof(int), 0, 3, compareIntPointers));
    CuAssertIntEquals(cuTest, 1, arrCompareOfRange(arr1, 10, arr2, 10, sizeof(int), 7, 9, compareIntPointers));
    CuAssertIntEquals(cuTest, 0, arrCompareOfRange(arr1, 10, arr2, 10, sizeof(int), 4, 6, compareIntPointers));

}


void testArrMismatch(CuTest *cuTest) {

    int arr1[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    int arr2[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    int arr3[] = {1, 2, 3, 4, 5, 5, 7, 8, 9, 10};

    arrMismatch(NULL, 0, NULL, 0, 0, NULL);
    CuAssertIntEquals(cuTest, NULL_POINTER, ERROR_TEST->errorCode);

    arrMismatch(arr1, 0, NULL, 0, 0, NULL);
    CuAssertIntEquals(cuTest, NULL_POINTER, ERROR_TEST->errorCode);

    arrMismatch(arr1, 0, arr2, 0, 0, NULL);
    CuAssertIntEquals(cuTest, INVALID_ARG, ERROR_TEST->errorCode);

    arrMismatch(arr1, -1, arr2, -1, 0, compareIntPointers);
    CuAssertIntEquals(cuTest, INVALID_ARG, ERROR_TEST->errorCode);

    arrMismatch(arr1, 0, arr2, 0, 0, compareIntPointers);
    CuAssertIntEquals(cuTest, INVALID_ARG, ERROR_TEST->errorCode);

    CuAssertIntEquals(cuTest, 5, arrMismatch(arr1, 10, arr3, 10, sizeof(int), compareIntPointers));
    CuAssertIntEquals(cuTest, -1, arrMismatch(arr1, 10, arr2, 10, sizeof(int), compareIntPointers));

}


void testArrAnagramsS(CuTest *cuTest) {

    int arr1[] = {1, 2, 3, 4, 5, 6, 3, 2, 7, 8, 9, 10};
    int arr2[] = {10, 9, 2, 3, 4, 5, 1, 8, 7, 6, 2, 3};
    int arr3[] = {10, 9, 2, 3, 4, 5, 1, 8, 8, 6, 2, 3};

    arrAnagramsS(NULL, 0, NULL, 0, 0, NULL);
    CuAssertIntEquals(cuTest, NULL_POINTER, ERROR_TEST->errorCode);

    arrAnagramsS(arr1, 0, NULL, 0, 0, NULL);
    CuAssertIntEquals(cuTest, NULL_POINTER, ERROR_TEST->errorCode);

    arrAnagramsS(arr1, 0, arr2, 0, 0, NULL);
    CuAssertIntEquals(cuTest, INVALID_ARG, ERROR_TEST->errorCode);

    arrAnagramsS(arr1, -1, arr2, -1, 0, compareIntPointers);
    CuAssertIntEquals(cuTest, INVALID_ARG, ERROR_TEST->errorCode);

    arrAnagramsS(arr1, 0, arr2, 0, 0, compareIntPointers);
    CuAssertIntEquals(cuTest, INVALID_ARG, ERROR_TEST->errorCode);

    CuAssertIntEquals(cuTest, 0, arrAnagramsS(arr1, 12, arr3, 12, sizeof(int), compareIntPointers));
    CuAssertIntEquals(cuTest, 1, arrAnagramsS(arr1, 12, arr2, 12, sizeof(int), compareIntPointers));

}


void testArrAnagramsH(CuTest *cuTest) {

    int arr1[] = {1, 2, 3, 4, 5, 6, 3, 2, 7, 8, 9, 10};
    int arr2[] = {10, 9, 2, 3, 4, 5, 1, 8, 7, 6, 2, 3};
    int arr3[] = {10, 9, 2, 3, 4, 5, 1, 8, 8, 6, 2, 3};

    arrAnagramsH(NULL, 0, NULL, 0, 0, NULL, NULL);
    CuAssertIntEquals(cuTest, NULL_POINTER, ERROR_TEST->errorCode);

    arrAnagramsH(arr1, 0, NULL, 0, 0, NULL, NULL);
    CuAssertIntEquals(cuTest, NULL_POINTER, ERROR_TEST->errorCode);

    arrAnagramsH(arr1, 0, arr2, 0, 0, NULL, NULL);
    CuAssertIntEquals(cuTest, INVALID_ARG, ERROR_TEST->errorCode);

    arrAnagramsH(arr1, -1, arr2, -1, 0, compareIntPointers, NULL);
    CuAssertIntEquals(cuTest, INVALID_ARG, ERROR_TEST->errorCode);

    arrAnagramsH(arr1, -1, arr2, -1, 0, compareIntPointers, intHashFun);
    CuAssertIntEquals(cuTest, INVALID_ARG, ERROR_TEST->errorCode);

    arrAnagramsH(arr1, 0, arr2, 0, 0, compareIntPointers, intHashFun);
    CuAssertIntEquals(cuTest, INVALID_ARG, ERROR_TEST->errorCode);

    CuAssertIntEquals(cuTest, 0, arrAnagramsH(arr1, 12, arr3, 12, sizeof(int), compareIntPointers, intHashFun));
    CuAssertIntEquals(cuTest, 1, arrAnagramsH(arr1, 12, arr2, 12, sizeof(int), compareIntPointers, intHashFun));

}


void testArrMismatchOfRange(CuTest *cuTest) {

    int arr1[] = {1, 2, 3, 4, 11, 6, 13, 8, 9, 10};
    int arr2[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};

    arrMismatchOfRange(NULL, 0, NULL, 0, 0, 0, 0, NULL);
    CuAssertIntEquals(cuTest, NULL_POINTER, ERROR_TEST->errorCode);

    arrMismatchOfRange(arr1, 0, NULL, 0, 0, 0, 0, NULL);
    CuAssertIntEquals(cuTest, NULL_POINTER, ERROR_TEST->errorCode);

    arrMismatchOfRange(arr1, 0, arr2, 0, 0, 0, 0, NULL);
    CuAssertIntEquals(cuTest, INVALID_ARG, ERROR_TEST->errorCode);

    arrMismatchOfRange(arr1, -1, arr2, -1, 0, 0, 0, compareIntPointers);
    CuAssertIntEquals(cuTest, INVALID_ARG, ERROR_TEST->errorCode);

    arrMismatchOfRange(arr1, 0, arr2, 0, 0, 0, 0, compareIntPointers);
    CuAssertIntEquals(cuTest, INVALID_ARG, ERROR_TEST->errorCode);

    arrMismatchOfRange(arr1, 0, arr2, 0, 0, 0, -1, compareIntPointers);
    CuAssertIntEquals(cuTest, INVALID_ARG, ERROR_TEST->errorCode);

    CuAssertIntEquals(cuTest, -1, arrMismatchOfRange(arr1, 10, arr2, 10, sizeof(int), 0, 3, compareIntPointers));
    CuAssertIntEquals(cuTest, 4, arrMismatchOfRange(arr1, 10, arr2, 10, sizeof(int), 0, 5, compareIntPointers));
    CuAssertIntEquals(cuTest, -1, arrMismatchOfRange(arr1, 10, arr2, 10, sizeof(int), 7, 9, compareIntPointers));
    CuAssertIntEquals(cuTest, 6, arrMismatchOfRange(arr1, 10, arr2, 10, sizeof(int), 6, 9, compareIntPointers));

}


void testArrRemoveDuplicatesA(CuTest *cuTest) {

    int arr[] = {1, 2, 3, 1, 4, 2, 2, 3, 5, 6};

    arrRemoveDuplicatesA(NULL, 0, 0, NULL, NULL);
    CuAssertIntEquals(cuTest, NULL_POINTER, ERROR_TEST->errorCode);

    arrRemoveDuplicatesA(arr, 0, 0, NULL, NULL);
    CuAssertIntEquals(cuTest, INVALID_ARG, ERROR_TEST->errorCode);

    arrRemoveDuplicatesA(arr, -1, 0, compareIntPointers, NULL);
    CuAssertIntEquals(cuTest, INVALID_ARG, ERROR_TEST->errorCode);

    arrRemoveDuplicatesA(arr, 0, 0, compareIntPointers, NULL);
    CuAssertIntEquals(cuTest, INVALID_ARG, ERROR_TEST->errorCode);

    CuAssertIntEquals(cuTest, 6, arrRemoveDuplicatesA(arr, 10, sizeof(int), compareIntPointers, NULL));
    for (int i = 0; i < 6; i++)
        CuAssertIntEquals(cuTest, i + 1, arr[i]);


}


void testArrRemoveDuplicatesH(CuTest *cuTest) {

    int arr[] = {1, 2, 3, 1, 4, 2, 2, 3, 5, 6};

    arrRemoveDuplicatesH(NULL, 0, 0, NULL, NULL, NULL);
    CuAssertIntEquals(cuTest, NULL_POINTER, ERROR_TEST->errorCode);

    arrRemoveDuplicatesH(arr, 0, 0, NULL, NULL, NULL);
    CuAssertIntEquals(cuTest, INVALID_ARG, ERROR_TEST->errorCode);

    arrRemoveDuplicatesH(arr, -1, 0, compareIntPointers, NULL, NULL);
    CuAssertIntEquals(cuTest, INVALID_ARG, ERROR_TEST->errorCode);

    arrRemoveDuplicatesH(arr, 0, 0, compareIntPointers, NULL, NULL);
    CuAssertIntEquals(cuTest, INVALID_ARG, ERROR_TEST->errorCode);

    arrRemoveDuplicatesH(arr, 0, 1, compareIntPointers, NULL, NULL);
    CuAssertIntEquals(cuTest, INVALID_ARG, ERROR_TEST->errorCode);

    CuAssertIntEquals(cuTest, 6, arrRemoveDuplicatesH(arr, 10, sizeof(int), compareIntPointers, intHashFun, NULL));
    for (int i = 0; i < 6; i++)
        CuAssertIntEquals(cuTest, i + 1, arr[i]);


}


void testArrRemoveValues(CuTest *cuTest) {

    int arr[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    int valuesArr[] = {10, 9, 8, 7, 6};

    arrRemoveValues(NULL, 0, NULL, 0, 0, NULL, NULL);
    CuAssertIntEquals(cuTest, NULL_POINTER, ERROR_TEST->errorCode);

    arrRemoveValues(arr, 0, NULL, 0, 0, NULL, NULL);
    CuAssertIntEquals(cuTest, INVALID_ARG, ERROR_TEST->errorCode);

    arrRemoveValues(arr, 0, valuesArr, 0, 0, NULL, NULL);
    CuAssertIntEquals(cuTest, INVALID_ARG, ERROR_TEST->errorCode);

    arrRemoveValues(arr, -1, valuesArr, 0, 0, compareIntPointers, NULL);
    CuAssertIntEquals(cuTest, INVALID_ARG, ERROR_TEST->errorCode);

    arrRemoveValues(arr, -1, valuesArr, 0, 0, compareIntPointers, NULL);
    CuAssertIntEquals(cuTest, INVALID_ARG, ERROR_TEST->errorCode);

    CuAssertIntEquals(cuTest, 5, arrRemoveValues(arr, 10, valuesArr, 5, sizeof(int), compareIntPointers, NULL));
    for (int i = 0; i < 5; i++)
        CuAssertIntEquals(cuTest, i + 1, arr[i]);


}


void testArrCountValues(CuTest *cuTest) {

    int arr[] = {1, 2, 7, 4, 5, 6, 7, 8, 9, 10};
    int valuesArr[] = {10, 9, 8, 7, 6};

    arrCountValues(NULL, 0, NULL, 0, 0, NULL);
    CuAssertIntEquals(cuTest, NULL_POINTER, ERROR_TEST->errorCode);

    arrCountValues(arr, 0, NULL, 0, 0, NULL);
    CuAssertIntEquals(cuTest, INVALID_ARG, ERROR_TEST->errorCode);

    arrCountValues(arr, 0, valuesArr, 0, 0, NULL);
    CuAssertIntEquals(cuTest, INVALID_ARG, ERROR_TEST->errorCode);

    arrCountValues(arr, -1, valuesArr, 0, 0, compareIntPointers);
    CuAssertIntEquals(cuTest, INVALID_ARG, ERROR_TEST->errorCode);

    arrCountValues(arr, -1, valuesArr, 0, 0, compareIntPointers);
    CuAssertIntEquals(cuTest, INVALID_ARG, ERROR_TEST->errorCode);

    CuAssertIntEquals(cuTest, 6, arrCountValues(arr, 10, valuesArr, 5, sizeof(int), compareIntPointers));


}


void testIsSubArr(CuTest *cuTest) {

    int arr[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    int arr2[] = {4, 5, 6};
    int arr3[] = {2, 3, 4, 5, 8, 7};
    int arr4[] = {0};

    isSubArr(NULL, 0, NULL, 0, 0, NULL);
    CuAssertIntEquals(cuTest, NULL_POINTER, ERROR_TEST->errorCode);

    isSubArr(arr, 0, NULL, 0, 0, NULL);
    CuAssertIntEquals(cuTest, INVALID_ARG, ERROR_TEST->errorCode);

    isSubArr(arr, 0, arr2, 0, 0, NULL);
    CuAssertIntEquals(cuTest, INVALID_ARG, ERROR_TEST->errorCode);

    isSubArr(arr, -1, arr2, 0, 0, compareIntPointers);
    CuAssertIntEquals(cuTest, INVALID_ARG, ERROR_TEST->errorCode);

    isSubArr(arr, -1, arr2, 0, 0, compareIntPointers);
    CuAssertIntEquals(cuTest, INVALID_ARG, ERROR_TEST->errorCode);

    CuAssertIntEquals(cuTest, 1, isSubArr(arr, 10, arr2, 3, sizeof(int), compareIntPointers));
    CuAssertIntEquals(cuTest, 1, isSubArr(arr, 10, arr, 10, sizeof(int), compareIntPointers));
    CuAssertIntEquals(cuTest, 0, isSubArr(arr, 10, arr3, 6, sizeof(int), compareIntPointers));
    CuAssertIntEquals(cuTest, 1, isSubArr(arr, 10, arr4, 0, sizeof(int), compareIntPointers));


}


void testArrGetStartIndex(CuTest *cuTest) {

    int arr[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    int valuesArr[] = {7, 8, 9};
    int valuesArr2[] = {1, 2, 3};
    int valuesArr3[] = {1, 2, 3, 4, 6};


    arrGetStartIndex(NULL, 0, NULL, 0, 0, NULL);
    CuAssertIntEquals(cuTest, NULL_POINTER, ERROR_TEST->errorCode);

    arrGetStartIndex(arr, 0, NULL, 0, 0, NULL);
    CuAssertIntEquals(cuTest, INVALID_ARG, ERROR_TEST->errorCode);

    arrGetStartIndex(arr, 0, valuesArr, 0, 0, NULL);
    CuAssertIntEquals(cuTest, INVALID_ARG, ERROR_TEST->errorCode);

    arrGetStartIndex(arr, -1, valuesArr, 0, 0, compareIntPointers);
    CuAssertIntEquals(cuTest, INVALID_ARG, ERROR_TEST->errorCode);

    arrGetStartIndex(arr, -1, valuesArr, 0, 0, compareIntPointers);
    CuAssertIntEquals(cuTest, INVALID_ARG, ERROR_TEST->errorCode);

    CuAssertIntEquals(cuTest, 6, arrGetStartIndex(arr, 10, valuesArr, 3, sizeof(int), compareIntPointers));
    CuAssertIntEquals(cuTest, 0, arrGetStartIndex(arr, 10, valuesArr2, 3, sizeof(int), compareIntPointers));
    CuAssertIntEquals(cuTest, -1, arrGetStartIndex(arr, 10, valuesArr3, 5, sizeof(int), compareIntPointers));

}


void testArrContains(CuTest *cuTest) {

    int arr[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    int tempValue;

    arrContains(NULL, NULL, 0, 0, NULL);
    CuAssertIntEquals(cuTest, NULL_POINTER, ERROR_TEST->errorCode);

    arrContains(arr, NULL, 0, 0, NULL);
    CuAssertIntEquals(cuTest, INVALID_ARG, ERROR_TEST->errorCode);

    arrContains(arr, &tempValue, 0, 0, NULL);
    CuAssertIntEquals(cuTest, INVALID_ARG, ERROR_TEST->errorCode);

    arrContains(arr, &tempValue, -1, 0, compareIntPointers);
    CuAssertIntEquals(cuTest, INVALID_ARG, ERROR_TEST->errorCode);

    arrContains(arr, &tempValue, 0, 0, compareIntPointers);
    CuAssertIntEquals(cuTest, INVALID_ARG, ERROR_TEST->errorCode);

    for (int i = 1; i <= 10; i++)
        CuAssertIntEquals(cuTest, 1, arrContains(arr, &i, 10, sizeof(int), compareIntPointers));


    tempValue = 11;
    CuAssertIntEquals(cuTest, 0, arrContains(arr, &tempValue, 10, sizeof(int), compareIntPointers));

}


void testArrRemoveAtIndex(CuTest *cuTest) {

    int arr[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    int tempValue;

    arrRemoveAtIndex(NULL, 0, 0, 0, NULL);
    CuAssertIntEquals(cuTest, NULL_POINTER, ERROR_TEST->errorCode);

    arrRemoveAtIndex(arr, 0, -1, 0, NULL);
    CuAssertIntEquals(cuTest, INVALID_ARG, ERROR_TEST->errorCode);

    arrRemoveAtIndex(arr, 0, 0, 0, NULL);
    CuAssertIntEquals(cuTest, INVALID_ARG, ERROR_TEST->errorCode);

    arrRemoveAtIndex(arr, 0, 0, 1, NULL);
    CuAssertIntEquals(cuTest, INVALID_ARG, ERROR_TEST->errorCode);

    for (int i = 0; i < 10; i++) {

        arrRemoveAtIndex(arr, 0, 10 - i, sizeof(int), NULL);

        for (int j = 0; j < 10 - i - 1; j++)
            CuAssertIntEquals(cuTest, j + i + 2, arr[j]);

    }

}


void testArrSort(CuTest *cuTest) {

    int arr[] = {10, 4, 5, 3, 2, 1, 6, 7, 8, 9};

    arrSort(NULL, 0, 0, NULL);
    CuAssertIntEquals(cuTest, NULL_POINTER, ERROR_TEST->errorCode);

    arrSort(arr, 0, -1, NULL);
    CuAssertIntEquals(cuTest, INVALID_ARG, ERROR_TEST->errorCode);

    arrSort(arr, -1, 0, compareIntPointers);
    CuAssertIntEquals(cuTest, INVALID_ARG, ERROR_TEST->errorCode);

    arrSort(arr, 0, 0, compareIntPointers);
    CuAssertIntEquals(cuTest, INVALID_ARG, ERROR_TEST->errorCode);

    arrSort(arr, 10, sizeof(int), compareIntPointers);
    for (int i = 0; i < 10; i++)
        CuAssertIntEquals(cuTest, i + 1, arr[i]);

}


void testArrGetFirst(CuTest *cuTest) {

    int arr[] = {1, 2, 3, 4, 5, 5, 4, 3, 2, 1};

    int tempValue;

    arrGetFirst(NULL, NULL, 0, 0, NULL);
    CuAssertIntEquals(cuTest, NULL_POINTER, ERROR_TEST->errorCode);

    arrGetFirst(arr, NULL, 0, -1, NULL);
    CuAssertIntEquals(cuTest, INVALID_ARG, ERROR_TEST->errorCode);

    arrGetFirst(arr, &tempValue, 0, 0, NULL);
    CuAssertIntEquals(cuTest, INVALID_ARG, ERROR_TEST->errorCode);

    arrGetFirst(arr, &tempValue, -1, 0, compareIntPointers);
    CuAssertIntEquals(cuTest, INVALID_ARG, ERROR_TEST->errorCode);

    arrGetFirst(arr, &tempValue, 0, 0, compareIntPointers);
    CuAssertIntEquals(cuTest, INVALID_ARG, ERROR_TEST->errorCode);

    for (int i = 1; i <= 5; i++)
        CuAssertIntEquals(cuTest, i - 1, arrGetFirst(arr, &i, 10, sizeof(int), compareIntPointers));

    tempValue = 11;
    CuAssertIntEquals(cuTest, -1, arrGetFirst(arr, &tempValue, 10, sizeof(int), compareIntPointers));

}


void testArrGetLast(CuTest *cuTest) {

    int arr[] = {1, 2, 3, 4, 5, 5, 4, 3, 2, 1};

    int tempValue;

    arrGetLast(NULL, NULL, 0, 0, NULL);
    CuAssertIntEquals(cuTest, NULL_POINTER, ERROR_TEST->errorCode);

    arrGetLast(arr, NULL, 0, -1, NULL);
    CuAssertIntEquals(cuTest, INVALID_ARG, ERROR_TEST->errorCode);

    arrGetLast(arr, &tempValue, 0, 0, NULL);
    CuAssertIntEquals(cuTest, INVALID_ARG, ERROR_TEST->errorCode);

    arrGetLast(arr, &tempValue, -1, 0, compareIntPointers);
    CuAssertIntEquals(cuTest, INVALID_ARG, ERROR_TEST->errorCode);

    arrGetLast(arr, &tempValue, 0, 0, compareIntPointers);
    CuAssertIntEquals(cuTest, INVALID_ARG, ERROR_TEST->errorCode);

    for (int i = 1; i <= 5; i++)
        CuAssertIntEquals(cuTest, 10 - i, arrGetLast(arr, &i, 10, sizeof(int), compareIntPointers));

    tempValue = 11;
    CuAssertIntEquals(cuTest, -1, arrGetLast(arr, &tempValue, 10, sizeof(int), compareIntPointers));

}


void testArrGetAll(CuTest *cuTest) {

    int arr[] = {1, 2, 3, 4, 5, 5, 4, 3, 2, 1};

    int tempValue;

    arrGetAll(NULL, NULL, 0, 0, NULL);
    CuAssertIntEquals(cuTest, NULL_POINTER, ERROR_TEST->errorCode);

    arrGetAll(arr, NULL, 0, -1, NULL);
    CuAssertIntEquals(cuTest, INVALID_ARG, ERROR_TEST->errorCode);

    arrGetAll(arr, &tempValue, 0, 0, NULL);
    CuAssertIntEquals(cuTest, INVALID_ARG, ERROR_TEST->errorCode);

    arrGetAll(arr, &tempValue, -1, 0, compareIntPointers);
    CuAssertIntEquals(cuTest, INVALID_ARG, ERROR_TEST->errorCode);

    arrGetAll(arr, &tempValue, 0, 0, compareIntPointers);
    CuAssertIntEquals(cuTest, INVALID_ARG, ERROR_TEST->errorCode);


    for (int i = 0; i < 5; i++) {
        tempValue = i + 1;
        Vector *indicesVector = arrGetAll(arr, &tempValue, 10, sizeof(int), compareIntPointers);
        CuAssertIntEquals(cuTest, 2, vectorGetLength(indicesVector));
        CuAssertIntEquals(cuTest, i, *(int *) vectorGet(indicesVector, 0));
        CuAssertIntEquals(cuTest, 9 - i, *(int *) vectorGet(indicesVector, 1));
        destroyVector(indicesVector);
    }

}


void testArrBinarySearch(CuTest *cuTest) {

    int arr[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    int tempValue;

    arrBinarySearch(NULL, NULL, 0, 0, NULL);
    CuAssertIntEquals(cuTest, NULL_POINTER, ERROR_TEST->errorCode);

    arrBinarySearch(arr, NULL, 0, -1, NULL);
    CuAssertIntEquals(cuTest, INVALID_ARG, ERROR_TEST->errorCode);

    arrBinarySearch(arr, &tempValue, 0, 0, NULL);
    CuAssertIntEquals(cuTest, INVALID_ARG, ERROR_TEST->errorCode);

    arrBinarySearch(arr, &tempValue, -1, 0, compareIntPointers);
    CuAssertIntEquals(cuTest, INVALID_ARG, ERROR_TEST->errorCode);

    arrBinarySearch(arr, &tempValue, 0, 0, compareIntPointers);
    CuAssertIntEquals(cuTest, INVALID_ARG, ERROR_TEST->errorCode);

    for (int i = 1; i <= 10; i++)
        CuAssertIntEquals(cuTest, i - 1, arrBinarySearch(arr, &i, 10, sizeof(int), compareIntPointers));

    tempValue = 11;
    CuAssertIntEquals(cuTest, -1, arrBinarySearch(arr, &tempValue, 10, sizeof(int), compareIntPointers));

}


void testArrIsPalindrome(CuTest *cuTest) {

    int arr[] = {1, 2, 3, 4, 5, 5, 4, 3, 2, 1};
    int arr2[] = {1, 2, 3, 3, 1, 1};
    int arr3[] = {0};

    arrIsPalindrome(NULL, 0, 0, NULL);
    CuAssertIntEquals(cuTest, NULL_POINTER, ERROR_TEST->errorCode);

    arrIsPalindrome(arr, 0, -1, NULL);
    CuAssertIntEquals(cuTest, INVALID_ARG, ERROR_TEST->errorCode);

    arrIsPalindrome(arr, 0, 0, NULL);
    CuAssertIntEquals(cuTest, INVALID_ARG, ERROR_TEST->errorCode);

    arrIsPalindrome(arr, -1, 0, compareIntPointers);
    CuAssertIntEquals(cuTest, INVALID_ARG, ERROR_TEST->errorCode);


    CuAssertIntEquals(cuTest, 1, arrIsPalindrome(arr, 10, sizeof(int), compareIntPointers));
    CuAssertIntEquals(cuTest, 0, arrIsPalindrome(arr2, 6, sizeof(int), compareIntPointers));
    CuAssertIntEquals(cuTest, 1, arrIsPalindrome(arr3, 0, sizeof(int), compareIntPointers));

}


void testArrIsRotation(CuTest *cuTest) {

    int arr[] = {1, 2, 3, 4, 3, 5, 6};
    int valuesArr[] = {3, 5, 6, 1, 2, 3, 4};
    int valuesArr2[] = {4, 3, 5, 6, 1, 2, 3};
    int valuesArr3[] = {3, 4, 5, 5, 6, 1, 2, 3};
    int valuesArr4[] = {1, 2, 3, 4, 3, 5, 6};


    arrIsRotation(NULL, 0, NULL, 0, 0, NULL);
    CuAssertIntEquals(cuTest, NULL_POINTER, ERROR_TEST->errorCode);

    arrIsRotation(arr, 0, NULL, 0, 0, NULL);
    CuAssertIntEquals(cuTest, NULL_POINTER, ERROR_TEST->errorCode);

    arrIsRotation(arr, 0, valuesArr, 0, 0, NULL);
    CuAssertIntEquals(cuTest, INVALID_ARG, ERROR_TEST->errorCode);

    arrIsRotation(arr, -1, valuesArr, 0, 0, compareIntPointers);
    CuAssertIntEquals(cuTest, INVALID_ARG, ERROR_TEST->errorCode);

    arrIsRotation(arr, -1, valuesArr, 0, 0, compareIntPointers);
    CuAssertIntEquals(cuTest, INVALID_ARG, ERROR_TEST->errorCode);

    CuAssertIntEquals(cuTest, 1, arrIsRotation(arr, 7, valuesArr, 7, sizeof(int), compareIntPointers));
    CuAssertIntEquals(cuTest, 1, arrIsRotation(arr, 7, valuesArr2, 7, sizeof(int), compareIntPointers));
    CuAssertIntEquals(cuTest, 0, arrIsRotation(arr, 7, valuesArr3, 7, sizeof(int), compareIntPointers));
    CuAssertIntEquals(cuTest, 1, arrIsRotation(arr, 7, valuesArr4, 7, sizeof(int), compareIntPointers));

}


void testArrUpdateElem(CuTest *cuTest) {

    int arr[] = {1, 2, 3, 4, 5, 6, 7, 8, 8, 10};
    int tempValue;

    arrUpdateElem(NULL, NULL, 0, 0, 0, NULL);
    CuAssertIntEquals(cuTest, NULL_POINTER, ERROR_TEST->errorCode);

    arrUpdateElem(arr, NULL, 0, -1, 0, NULL);
    CuAssertIntEquals(cuTest, INVALID_ARG, ERROR_TEST->errorCode);

    arrUpdateElem(arr, &tempValue, -1, 0, 0, NULL);
    CuAssertIntEquals(cuTest, INVALID_ARG, ERROR_TEST->errorCode);

    arrUpdateElem(arr, &tempValue, 0, 0, 0, NULL);
    CuAssertIntEquals(cuTest, INVALID_ARG, ERROR_TEST->errorCode);

    arrUpdateElem(arr, &tempValue, 0, 1, 0, NULL);
    CuAssertIntEquals(cuTest, INVALID_ARG, ERROR_TEST->errorCode);

    tempValue = 9;
    arrUpdateElem(arr, &tempValue, 10, sizeof(int), 8, NULL);
    for (int i = 0; i < 10; i++)
        CuAssertIntEquals(cuTest, i + 1, arr[i]);

}


void testArrAdd(CuTest *cuTest) {

    int arr[] = {1, 2, 3, 4, 5, 7, 8, 9, 10, 0};
    int tempValue;

    arrAdd(NULL, NULL, 0, 0, 0);
    CuAssertIntEquals(cuTest, NULL_POINTER, ERROR_TEST->errorCode);

    arrAdd(arr, NULL, 0, -1, 0);
    CuAssertIntEquals(cuTest, INVALID_ARG, ERROR_TEST->errorCode);

    arrAdd(arr, &tempValue, -1, 0, 0);
    CuAssertIntEquals(cuTest, INVALID_ARG, ERROR_TEST->errorCode);

    arrAdd(arr, &tempValue, 0, 0, 0);
    CuAssertIntEquals(cuTest, INVALID_ARG, ERROR_TEST->errorCode);

    arrAdd(arr, &tempValue, 0, 1, 0);
    CuAssertIntEquals(cuTest, INVALID_ARG, ERROR_TEST->errorCode);


    tempValue = 6;
    arrAdd(arr, &tempValue, 10, sizeof(int), 5);
    for (int i = 0; i < 10; i++)
        CuAssertIntEquals(cuTest, i + 1, arr[i]);

}


void testArrAddAll(CuTest *cuTest) {

    int arr[] = {1, 2, 3, 7, 8, 9, 10, 0, 0, 0};
    int tempValue[] = {4, 5, 6};

    arrAddAll(NULL, 0, NULL, 0, 0, 0);
    CuAssertIntEquals(cuTest, NULL_POINTER, ERROR_TEST->errorCode);

    arrAddAll(arr, 0, NULL, 0, -1, 0);
    CuAssertIntEquals(cuTest, INVALID_ARG, ERROR_TEST->errorCode);

    arrAddAll(arr, 0, tempValue, -1, 0, 0);
    CuAssertIntEquals(cuTest, INVALID_ARG, ERROR_TEST->errorCode);

    arrAddAll(arr, 0, tempValue, 0, 0, 0);
    CuAssertIntEquals(cuTest, INVALID_ARG, ERROR_TEST->errorCode);

    arrAddAll(arr, 0, tempValue, 0, 1, 0);
    CuAssertIntEquals(cuTest, INVALID_ARG, ERROR_TEST->errorCode);


    arrAddAll(arr, 10, tempValue, 3, sizeof(int), 3);
    for (int i = 0; i < 10; i++)
        CuAssertIntEquals(cuTest, i + 1, arr[i]);

}


CuSuite *createArraysAlgTestsSuite(void) {

    CuSuite *suite = CuSuiteNew();

    SUITE_ADD_TEST(suite, testArrayReverse);
    SUITE_ADD_TEST(suite, testMostFrequentArrValueH);
    SUITE_ADD_TEST(suite, testMostFrequentArrValueA);
    SUITE_ADD_TEST(suite, testPrintArr);
    SUITE_ADD_TEST(suite, testArrResize);
    SUITE_ADD_TEST(suite, testArrResizeAndCopy);
    SUITE_ADD_TEST(suite, testArrResizeOfRangeAndCpy);
    SUITE_ADD_TEST(suite, testArrResizeAndCpyC);
    SUITE_ADD_TEST(suite, testArrResizeOfRangeAndCpyC);
    SUITE_ADD_TEST(suite, testArrCopy);
    SUITE_ADD_TEST(suite, testArrCopyC);
    SUITE_ADD_TEST(suite, testArrCopyOfRange);
    SUITE_ADD_TEST(suite, testArrCopyOfRangeC);
    SUITE_ADD_TEST(suite, testFillArr);
    SUITE_ADD_TEST(suite, testFillArrC);
    SUITE_ADD_TEST(suite, testFillArrOfRange);
    SUITE_ADD_TEST(suite, testFillArrOfRangeC);
    SUITE_ADD_TEST(suite, testArrCompare);
    SUITE_ADD_TEST(suite, testArrCompareOfRange);
    SUITE_ADD_TEST(suite, testArrAnagramsS);
    SUITE_ADD_TEST(suite, testArrAnagramsH);
    SUITE_ADD_TEST(suite, testArrMismatch);
    SUITE_ADD_TEST(suite, testArrMismatchOfRange);
    SUITE_ADD_TEST(suite, testArrRemoveDuplicatesA);
    SUITE_ADD_TEST(suite, testArrRemoveDuplicatesH);
    SUITE_ADD_TEST(suite, testArrRemoveValues);
    SUITE_ADD_TEST(suite, testArrCountValues);
    SUITE_ADD_TEST(suite, testIsSubArr);
    SUITE_ADD_TEST(suite, testArrGetStartIndex);
    SUITE_ADD_TEST(suite, testArrContains);
    SUITE_ADD_TEST(suite, testArrRemoveAtIndex);
    SUITE_ADD_TEST(suite, testArrSort);
    SUITE_ADD_TEST(suite, testArrGetFirst);
    SUITE_ADD_TEST(suite, testArrGetLast);
    SUITE_ADD_TEST(suite, testArrGetAll);
    SUITE_ADD_TEST(suite, testArrBinarySearch);
    SUITE_ADD_TEST(suite, testArrIsPalindrome);
    SUITE_ADD_TEST(suite, testArrIsRotation);
    SUITE_ADD_TEST(suite, testArrUpdateElem);
    SUITE_ADD_TEST(suite, testArrAdd);
    SUITE_ADD_TEST(suite, testArrAddAll);

    return suite;

}


void arraysAlgUnitTest(void) {

    ERROR_TEST = (ErrorTestStruct *) malloc(sizeof(ErrorTestStruct));

    CuString *output = CuStringNew();
    CuStringAppend(output, "**Arrays Algorithms Test**\n");

    CuSuite *suite = createArraysAlgTestsSuite();

    CuSuiteRun(suite);
    CuSuiteSummary(suite, output);
    CuSuiteDetails(suite, output);
    printf("%s\n", output->buffer);

    free(ERROR_TEST);

}
