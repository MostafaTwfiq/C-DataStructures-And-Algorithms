#include "../Header/InsertionSort.h"
#include "../../../System/Utils.h"






/** This function will take an array then it sort it with the insertion sort algorithm.
 *
 * Time Complexity: worst: O(n) , best: O (n ^ 2).
 * Space Complexity: O(1).
 *
 * @param arr the array pointer
 * @param length the length of the array
 * @param elemSize the size of the array elements in bytes
 * @param cmp the comparator function pointer
 */

void insertionSort(void *arr, int length, int elemSize, int (*cmp)(const void *, const void *)) {

    if (arr == NULL) {
        fprintf(stderr, NULL_POINTER_MESSAGE, "passed array", "insertion sort");
        exit(NULL_POINTER);
    } else if (cmp == NULL) {
        fprintf(stderr, INVALID_ARG_MESSAGE, "comparator function pointer", "insertion sort");
        exit(INVALID_ARG);
    } else if (length < 0) {
        fprintf(stderr, INVALID_ARG_MESSAGE, "array length", "insertion sort");
        exit(INVALID_ARG);
    } else if (elemSize <= 0) {
        fprintf(stderr, INVALID_ARG_MESSAGE, "element size", "insertion sort");
        exit(INVALID_ARG);
    }

    for (int i = 0; i < length; i++) {
        void *currentElement = (void *) malloc(elemSize);
        memcpy(currentElement, arr + i * elemSize, elemSize);
        int rightIndex = 0;
        for (int j = 0; j < i; j++) {

            if ( cmp(currentElement, arr + j * elemSize) <= 0) {
                rightIndex = j;
                break;
            }

        }

        for (int j = i; j > rightIndex; j--)
            memcpy(arr + j * elemSize, arr + (j - 1) * elemSize, elemSize);

        memcpy(arr + rightIndex * elemSize, currentElement, elemSize);

    }



}