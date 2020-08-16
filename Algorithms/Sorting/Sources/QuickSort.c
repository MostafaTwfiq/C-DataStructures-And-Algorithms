#include "../Headers/QuickSort.h"
#include "../Headers/SwapFunction.h"
#include "../../../System/Utils.h"
#include "../../../Unit Test/CuTest/CuTest.h"


void quickSortHelper(char *arr, int length, int elemSize, int (*cmp)(const void *, const void *));


/** This function will take an array then it sort it with the quick sort algorithm.
 *
 * Time Complexity: worst: O( n ^ 2 ) , best: O ( n log(n) ).
 *
 * Space Complexity: O( log(n) ) <<because the recursive calls>>.
 *
 * @param arr the array pointer
 * @param length the length of the array
 * @param elemSize the size of the array elements in bytes
 * @param cmp the comparator function pointer
 */

void quickSort(void *arr, int length, int elemSize, int (*cmp)(const void *, const void *)) {

    if (arr == NULL) {
#ifdef C_DATASTRUCTURES_ERRORSTESTSTRUCT_H
        ERROR_TEST->errorCode = NULL_POINTER;
        return;
#else
        fprintf(stderr, NULL_POINTER_MESSAGE, "passed array", "quick sort");
        exit(NULL_POINTER);
#endif
    } else if (cmp == NULL) {
#ifdef C_DATASTRUCTURES_ERRORSTESTSTRUCT_H
        ERROR_TEST->errorCode = INVALID_ARG;
        return;
#else
        fprintf(stderr, INVALID_ARG_MESSAGE, "comparator function pointer", "quick sort");
        exit(INVALID_ARG);
#endif
    } else if (length < 0) {
#ifdef C_DATASTRUCTURES_ERRORSTESTSTRUCT_H
        ERROR_TEST->errorCode = INVALID_ARG;
        return;
#else
        fprintf(stderr, INVALID_ARG_MESSAGE, "array length", "quick sort");
        exit(INVALID_ARG);
#endif
    } else if (elemSize <= 0) {
#ifdef C_DATASTRUCTURES_ERRORSTESTSTRUCT_H
        ERROR_TEST->errorCode = INVALID_ARG;
        return;
#else
        fprintf(stderr, INVALID_ARG_MESSAGE, "element size", "quick sort");
        exit(INVALID_ARG);
#endif
    }

    quickSortHelper(arr, length, elemSize, cmp);

    //TODO: try to improve the quick sort because the worst case << O(n^2) >>.

}


/** This function will take an array then recursively it will sort the array using quick sort algorithm.
 *
 * Note: this function should only be called from the  quickSort function.
 *
 * Time Complexity: worst: O( n ^ 2 ) , best: O ( n log(n) ).
 *
 * Space Complexity: O( log(n) ) <<because the recursive calls>>.
 *
 * @param arr the array pointer
 * @param length the length of the array
 * @param elemSize the array elements size in bytes
 * @param cmp the comparator function pointer
 */

void quickSortHelper(char *arr, int length, int elemSize, int (*cmp)(const void *, const void *)) {
    if (length <= 0)
        return;

    char *boundaryPointer = arr - elemSize;


    for (int i = 0; i < length; i++) {
        if (cmp(arr + (length - 1) * elemSize, arr + i * elemSize) >= 0) {
            boundaryPointer += elemSize;
            swap(boundaryPointer, arr + i * elemSize, elemSize);
        }

    }

    int firstHalfLength = ((boundaryPointer - arr) / elemSize);
    int secondHalfLength = length - firstHalfLength - 1;


    quickSortHelper(arr, firstHalfLength, elemSize, cmp);
    quickSortHelper(boundaryPointer + elemSize, secondHalfLength, elemSize, cmp);

}