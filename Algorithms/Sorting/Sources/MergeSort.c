#include "../Headers/MergeSort.h"
#include "../Headers/SwapFunction.h"
#include "../../../System/Utils.h"
#include "../../../Unit Test/CuTest/CuTest.h"




void mergeSortHelper(void *arr, int length, int elemSize, int (*cmp)(const void *, const void *));







/** This function will take an array then it sort it with the merge sort algorithm.
 *
 * Time Complexity: worst: O( n log(n) ) , best: O ( n log(n) ).
 *
 * Space Complexity: O ( log(n) ) <<because the recursive calls>>
 *
 * @param arr the array pointer
 * @param length the length of the array
 * @param elemSize the size of the array elements in bytes
 * @param cmp the comparator function pointer
 */

void mergeSort(void *arr, int length, int elemSize, int (*cmp)(const void *, const void *)) {

    if (arr == NULL) {
        #ifdef CU_TEST_H
            DUMMY_TEST_DATASTRUCTURE->errorCode = NULL_POINTER;
            return;
        #else
            fprintf(stderr, NULL_POINTER_MESSAGE, "passed array", "merge sort");
            exit(NULL_POINTER);
        #endif
    } else if (cmp == NULL) {
        #ifdef CU_TEST_H
            DUMMY_TEST_DATASTRUCTURE->errorCode = INVALID_ARG;
            return;
        #else
            fprintf(stderr, INVALID_ARG_MESSAGE, "comparator function pointer", "merge sort");
            exit(INVALID_ARG);
        #endif
    } else if (length < 0) {
        #ifdef CU_TEST_H
            DUMMY_TEST_DATASTRUCTURE->errorCode = INVALID_ARG;
            return;
        #else
            fprintf(stderr, INVALID_ARG_MESSAGE, "array length", "merge sort");
            exit(INVALID_ARG);
        #endif
    } else if (elemSize <= 0) {
        #ifdef CU_TEST_H
            DUMMY_TEST_DATASTRUCTURE->errorCode = INVALID_ARG;
            return;
        #else
            fprintf(stderr, INVALID_ARG_MESSAGE, "element size", "merge sort");
            exit(INVALID_ARG);
        #endif
    }

    mergeSortHelper(arr, length, elemSize, cmp);

}




/** This function will take an array then it sort it recursively with the merge sort algorithm.
 *
 * Note: this function should only be called from the mergeSort function.
 *
 * Time Complexity: worst: O( n log(n) ) , best: O ( n log(n) ).
 *
 * Space Complexity: O ( log(n) ) <<because the recursive calls>>
 *
 * @param arr the array pointer
 * @param length the length of the array
 * @param elemSize the size of the array elements in bytes
 * @param cmp the comparator function pointer
 */

void mergeSortHelper(void *arr, int length, int elemSize, int (*cmp)(const void *, const void *)) {
    if (length <= 0)
        return;


    int middleLength = (int) (length / 2);
    int secondHalfLength = length - middleLength == length ? 0 : length - middleLength;

    mergeSortHelper(arr, middleLength, elemSize, cmp);
    mergeSortHelper(arr + middleLength * elemSize, secondHalfLength, elemSize, cmp);

    for (int i = middleLength - 1; i >= 0; i--) {

        for (int j = i; j < length - 1; j++) {
            if ( cmp(arr + j * elemSize, arr + (j + 1) * elemSize ) > 0 )
                swap(arr + j * elemSize, arr + (j + 1) * elemSize, elemSize);
            else
                break;


        }

    }

}