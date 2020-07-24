#include "../Headers/BubbleSort.h"
#include "../Headers/SwapFunction.h"
#include "../../../System/Utils.h"




/** This function will take an array then it sort it with the bubble sort algorithm.
 *
 * Time Complexity: worst: O(n) , best: O (n ^ 2).
 * Space Complexity: O(1).
 *
 * @param arr the array pointer
 * @param length the length of the array
 * @param elemSize the size of the array elements in bytes
 * @param cmp the comparator function pointer
 */

void bubbleSort(void *arr, int length, int elemSize, int (*cmp)(const void *, const void *)) {
    if (arr == NULL) {
        fprintf(stderr, NULL_POINTER_MESSAGE, "passed array", "bubble sort");
        exit(NULL_POINTER);
    } else if (cmp == NULL) {
        fprintf(stderr, INVALID_ARG_MESSAGE, "comparator function pointer", "bubble sort");
        exit(INVALID_ARG);
    } else if (length < 0) {
        fprintf(stderr, INVALID_ARG_MESSAGE, "array length", "bubble sort");
        exit(INVALID_ARG);
    } else if (elemSize <= 0) {
        fprintf(stderr, INVALID_ARG_MESSAGE, "element size", "bubble sort");
        exit(INVALID_ARG);
    }

    short swapFlag = 0;

    for (int i = length - 1; i > 0; i--) {

        swapFlag = 0;

        for (int j = 0; j < i; j++) {

            if (cmp( arr + j * elemSize, arr + (j + 1) * elemSize ) > 0) {
                swap(arr + j * elemSize, arr + (j + 1) * elemSize, elemSize);
                swapFlag = 1;
            }

        }

        if (!swapFlag)
            break;

    }

}