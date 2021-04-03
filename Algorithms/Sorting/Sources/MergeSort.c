#include "../Headers/MergeSort.h"
#include "../Headers/SwapFunction.h"
#include "../../../System/Utils.h"
#include "../../../Unit Test/CuTest/CuTest.h"


void mergeSortWSHelper(char *arr, int length, int elemSize, int (*cmp)(const void *, const void *));

void mergeSortHelper(char *arr, int length, int elemSize, int (*cmp)(const void *, const void *));


/** This function will take an array then it sort it with the merge sort algorithm.
 *
 * Time Complexity: worst: O( n^2 ) , best: O ( n log(n) ).
 *
 * Space Complexity: O ( 1 )
 *
 * @param arr the array pointer
 * @param length the length of the array
 * @param elemSize the size of the array elements in bytes
 * @param cmp the comparator function pointer
 */

void mergeSortWS(void *arr, int length, int elemSize, int (*cmp)(const void *, const void *)) {

    if (arr == NULL) {
#ifdef C_DATASTRUCTURES_ERRORSTESTSTRUCT_H
        ERROR_TEST->errorCode = NULL_POINTER;
        return;
#else
        fprintf(stderr, NULL_POINTER_MESSAGE, "passed array", "merge sort");
        exit(NULL_POINTER);
#endif
    } else if (cmp == NULL) {
#ifdef C_DATASTRUCTURES_ERRORSTESTSTRUCT_H
        ERROR_TEST->errorCode = INVALID_ARG;
        return;
#else
        fprintf(stderr, INVALID_ARG_MESSAGE, "comparator function pointer", "merge sort");
        exit(INVALID_ARG);
#endif
    } else if (length < 0) {
#ifdef C_DATASTRUCTURES_ERRORSTESTSTRUCT_H
        ERROR_TEST->errorCode = INVALID_ARG;
        return;
#else
        fprintf(stderr, INVALID_ARG_MESSAGE, "array length", "merge sort");
        exit(INVALID_ARG);
#endif
    } else if (elemSize <= 0) {
#ifdef C_DATASTRUCTURES_ERRORSTESTSTRUCT_H
        ERROR_TEST->errorCode = INVALID_ARG;
        return;
#else
        fprintf(stderr, INVALID_ARG_MESSAGE, "element size", "merge sort");
        exit(INVALID_ARG);
#endif
    }

    mergeSortWSHelper((char *) arr, length, elemSize, cmp);

}


/** This function will take an array then it sort it with the merge sort algorithm.
 *
 * Time Complexity: worst: O( n log(n) ) , best: O ( n log(n) ).
 *
 * Space Complexity: O ( n )
 *
 * @param arr the array pointer
 * @param length the length of the array
 * @param elemSize the size of the array elements in bytes
 * @param cmp the comparator function pointer
 */

void mergeSort(void *arr, int length, int elemSize, int (*cmp)(const void *, const void *)) {

    if (arr == NULL) {
#ifdef C_DATASTRUCTURES_ERRORSTESTSTRUCT_H
        ERROR_TEST->errorCode = NULL_POINTER;
        return;
#else
        fprintf(stderr, NULL_POINTER_MESSAGE, "passed array", "merge sort");
        exit(NULL_POINTER);
#endif
    } else if (cmp == NULL) {
#ifdef C_DATASTRUCTURES_ERRORSTESTSTRUCT_H
        ERROR_TEST->errorCode = INVALID_ARG;
        return;
#else
        fprintf(stderr, INVALID_ARG_MESSAGE, "comparator function pointer", "merge sort");
        exit(INVALID_ARG);
#endif
    } else if (length < 0) {
#ifdef C_DATASTRUCTURES_ERRORSTESTSTRUCT_H
        ERROR_TEST->errorCode = INVALID_ARG;
        return;
#else
        fprintf(stderr, INVALID_ARG_MESSAGE, "array length", "merge sort");
        exit(INVALID_ARG);
#endif
    } else if (elemSize <= 0) {
#ifdef C_DATASTRUCTURES_ERRORSTESTSTRUCT_H
        ERROR_TEST->errorCode = INVALID_ARG;
        return;
#else
        fprintf(stderr, INVALID_ARG_MESSAGE, "element size", "merge sort");
        exit(INVALID_ARG);
#endif
    }

    mergeSortHelper((char *) arr, length, elemSize, cmp);

}


/** This function will take an array then it sort it recursively with the merge sort algorithm.
 *
 * Note: this function should only be called from the mergeSort function.
 *
 * Time Complexity: worst: O( n^2 ) , best: O ( n log(n) ).
 *
 * Space Complexity: O ( 1 )
 *
 * @param arr the array pointer
 * @param length the length of the array
 * @param elemSize the size of the array elements in bytes
 * @param cmp the comparator function pointer
 */

void mergeSortWSHelper(char *arr, int length, int elemSize, int (*cmp)(const void *, const void *)) {
    if (length <= 0)
        return;


    int firstHalfLength = (int) (length / 2);
    int secondHalfLength = length - firstHalfLength == length ? 0 : length - firstHalfLength;

    mergeSortWSHelper(arr, firstHalfLength, elemSize, cmp);
    mergeSortWSHelper(arr + firstHalfLength * elemSize, secondHalfLength, elemSize, cmp);

    for (int i = firstHalfLength - 1; i >= 0; i--) {

        for (int j = i; j < length - 1; j++) {
            if (cmp(arr + j * elemSize, arr + (j + 1) * elemSize) > 0)
                swap(arr + j * elemSize, arr + (j + 1) * elemSize, elemSize);
            else
                break;


        }

    }

}


/** This function will take an array then it sort it recursively with the merge sort algorithm.
 *
 * Note: this function should only be called from the mergeSort function.
 *
 * Time Complexity: worst: O( n log(n) ) , best: O ( n log(n) ).
 *
 * Space Complexity: O ( n )
 *
 * @param arr the array pointer
 * @param length the length of the array
 * @param elemSize the size of the array elements in bytes
 * @param cmp the comparator function pointer
 */

void mergeSortHelper(char *arr, int length, int elemSize, int (*cmp)(const void *, const void *)) {
    if (length <= 0)
        return;


    int firstHalfLength = (int) (length / 2);
    int secondHalfLength = length - firstHalfLength == length ? 0 : length - firstHalfLength;

    mergeSortHelper(arr, firstHalfLength, elemSize, cmp);
    mergeSortHelper(arr + firstHalfLength * elemSize, secondHalfLength, elemSize, cmp);

    char *tempArr = (char *) malloc(length * elemSize), *firstHalfPointer = arr;
    int counter = 0;

    for (int i = firstHalfLength; i < length; i++) {

        while (firstHalfPointer != arr + firstHalfLength * elemSize &&
               cmp(arr + i * elemSize, firstHalfPointer) > 0) {
            memcpy(tempArr + counter++ * elemSize, firstHalfPointer, elemSize);
            firstHalfPointer += elemSize;
        }

        memcpy(tempArr + counter++ * elemSize, arr + i * elemSize, elemSize);

    }

    while (firstHalfPointer != arr + firstHalfLength * elemSize) {
        memcpy(tempArr + counter++ * elemSize, firstHalfPointer, elemSize);
        firstHalfPointer += elemSize;
    }

    for (int i = 0; i < length; i++) {
        memcpy(arr + i * elemSize, tempArr + i * elemSize, elemSize);
    }

    free(tempArr);

}