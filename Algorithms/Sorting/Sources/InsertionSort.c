#include "../Headers/InsertionSort.h"
#include "../../../System/Utils.h"
#include "../../../Unit Test/CuTest/CuTest.h"


/** This function will take an array then it sort it with the insertion sort algorithm.
 *
 * Time Complexity: best: O(n) , worst: O (n ^ 2).
 *
 * Space Complexity: O(1).
 *
 * @param arr the array pointer
 * @param length the length of the array
 * @param elemSize the size of the array elements in bytes
 * @param cmp the comparator function pointer
 */

void insertionSort(void *arr, int length, int elemSize, int (*cmp)(const void *, const void *)) {

    if (arr == NULL) {
#ifdef C_DATASTRUCTURES_ERRORSTESTSTRUCT_H
        ERROR_TEST->errorCode = NULL_POINTER;
        return;
#else
        fprintf(stderr, NULL_POINTER_MESSAGE, "passed array", "insertion sort");
        exit(NULL_POINTER);
#endif
    } else if (cmp == NULL) {
#ifdef C_DATASTRUCTURES_ERRORSTESTSTRUCT_H
        ERROR_TEST->errorCode = INVALID_ARG;
        return;
#else
        fprintf(stderr, INVALID_ARG_MESSAGE, "comparator function pointer", "insertion sort");
        exit(INVALID_ARG);
#endif
    } else if (length < 0) {
#ifdef C_DATASTRUCTURES_ERRORSTESTSTRUCT_H
        ERROR_TEST->errorCode = INVALID_ARG;
        return;
#else
        fprintf(stderr, INVALID_ARG_MESSAGE, "array length", "insertion sort");
        exit(INVALID_ARG);
#endif
    } else if (elemSize <= 0) {
#ifdef C_DATASTRUCTURES_ERRORSTESTSTRUCT_H
        ERROR_TEST->errorCode = INVALID_ARG;
        return;
#else
        fprintf(stderr, INVALID_ARG_MESSAGE, "element size", "insertion sort");
        exit(INVALID_ARG);
#endif
    }

    char *oneBytePointer = (char *) arr;

    for (int i = 0; i < length; i++) {

        char *currentElement = (char *) malloc(elemSize);
        memcpy(currentElement, oneBytePointer + i * elemSize, elemSize);
        int rightIndex = 0;
        for (int j = 0; j <= i; j++) {

            if (cmp(currentElement, oneBytePointer + j * elemSize) <= 0) {
                rightIndex = j;
                break;
            }

        }

        for (int j = i; j > rightIndex; j--)
            memcpy(oneBytePointer + j * elemSize, oneBytePointer + (j - 1) * elemSize, elemSize);

        memcpy(oneBytePointer + rightIndex * elemSize, currentElement, elemSize);

        free(currentElement);

    }


}