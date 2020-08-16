#include "../Headers/SelectionSort.h"
#include "../Headers/SwapFunction.h"
#include "../../../System/Utils.h"
#include "../../../Unit Test/CuTest/CuTest.h"


/** This function will take an array then it sort it with the selection sort algorithm.
 *
 * Time Complexity: worst: O(n ^ 2) , best: O (n ^ 2).
 *
 * Space Complexity: O(1).
 *
 * @param arr the array pointer
 * @param length the length of the array
 * @param elemSize the size of the array elements in bytes
 * @param cmp the comparator function pointer
 */

void selectionSort(void *arr, int length, int elemSize, int (*cmp)(const void *, const void *)) {

    if (arr == NULL) {
#ifdef C_DATASTRUCTURES_ERRORSTESTSTRUCT_H
        ERROR_TEST->errorCode = NULL_POINTER;
        return;
#else
        fprintf(stderr, NULL_POINTER_MESSAGE, "passed array", "selection sort");
        exit(NULL_POINTER);
#endif
    } else if (cmp == NULL) {
#ifdef C_DATASTRUCTURES_ERRORSTESTSTRUCT_H
        ERROR_TEST->errorCode = INVALID_ARG;
        return;
#else
        fprintf(stderr, INVALID_ARG_MESSAGE, "comparator function pointer", "selection sort");
        exit(INVALID_ARG);
#endif
    } else if (length < 0) {
#ifdef C_DATASTRUCTURES_ERRORSTESTSTRUCT_H
        ERROR_TEST->errorCode = INVALID_ARG;
        return;
#else
        fprintf(stderr, INVALID_ARG_MESSAGE, "array length", "selection sort");
        exit(INVALID_ARG);
#endif
    } else if (elemSize <= 0) {
#ifdef C_DATASTRUCTURES_ERRORSTESTSTRUCT_H
        ERROR_TEST->errorCode = INVALID_ARG;
        return;
#else
        fprintf(stderr, INVALID_ARG_MESSAGE, "element size", "selection sort");
        exit(INVALID_ARG);
#endif
    }


    char *oneBytePointer = (char *) arr;
    char *currentElement = NULL;

    for (int i = 0; i < length; i++) {
        currentElement = oneBytePointer +
                         i * elemSize; // the min or max element depends on if the sorting descending order or not
        for (int j = i; j < length; j++) {

            if (cmp(currentElement, oneBytePointer + j * elemSize) > 0)
                currentElement = oneBytePointer + j * elemSize;

        }

        if (currentElement != oneBytePointer + i * elemSize)
            swap(oneBytePointer + i * elemSize, currentElement, elemSize);

    }


}