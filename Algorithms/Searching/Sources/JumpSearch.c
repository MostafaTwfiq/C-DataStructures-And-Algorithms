#include "../Headers/JumpSearch.h"
#include "../../../System/Utils.h"
#include "../../../Unit Test/CuTest/CuTest.h"
#include <math.h>








/** This function will take an array and value,
 * then it will search for the value using the jump search algorithm.
 *
 * Note: if the value doesn't exist the function will return minus one (-1).
 *
 * Note: the array must be sorted so the algorithm actually works.
 *
 * Time Complexity: O( sqrt(n) ).
 *
 * Space Complexity: O(1).
 *
 * @param arr the array pointer
 * @param value the target value pointer
 * @param length the length of the array
 * @param elemSize the array elements size in bytes
 * @param cmp the values comparator function
 * @return it will return the index of the value if found, other wise it will return -1
 */

int jumpSearch(void *arr, void *value, int length, int elemSize, int (*cmp)(const void *, const void *)) {

    if (arr == NULL) {
        #ifdef CU_TEST_H
            DUMMY_TEST_DATASTRUCTURE->errorCode = NULL_POINTER;
            return -1;
        #else
            fprintf(stderr, NULL_POINTER_MESSAGE, "passed array", "jump search");
            exit(NULL_POINTER);
        #endif
    } else if (value == NULL) {
        #ifdef CU_TEST_H
            DUMMY_TEST_DATASTRUCTURE->errorCode = INVALID_ARG;
            return -1;
        #else
            fprintf(stderr, INVALID_ARG_MESSAGE, "value pointer", "jump search");
            exit(INVALID_ARG);
        #endif
    } else if (cmp == NULL) {
        #ifdef CU_TEST_H
            DUMMY_TEST_DATASTRUCTURE->errorCode = INVALID_ARG;
            return -1;
        #else
            fprintf(stderr, INVALID_ARG_MESSAGE, "comparator function pointer", "jump search");
            exit(INVALID_ARG);
        #endif
    } else if (length < 0) {
        #ifdef CU_TEST_H
            DUMMY_TEST_DATASTRUCTURE->errorCode = INVALID_ARG;
            return -1;
        #else
            fprintf(stderr, INVALID_ARG_MESSAGE, "array length", "jump search");
            exit(INVALID_ARG);
        #endif
    } else if (elemSize <= 0) {
        #ifdef CU_TEST_H
            DUMMY_TEST_DATASTRUCTURE->errorCode = INVALID_ARG;
            return -1;
        #else
            fprintf(stderr, INVALID_ARG_MESSAGE, "element size", "jump search");
            exit(INVALID_ARG);
        #endif
    }


    int partitionSize = (int) sqrt(length);
    void *partStart = arr;
    void *nextPartStart = arr + elemSize * partitionSize;

    while (partStart < arr + length * elemSize) {
        if (nextPartStart > arr + length * elemSize)
            nextPartStart = arr + length * elemSize;

        if (cmp(value, nextPartStart - elemSize) <= 0 ) {

            for             (   void *currentPointer = partStart;
                                currentPointer < nextPartStart;
                                currentPointer += elemSize
                    )
            {

                if ( cmp(value, currentPointer) == 0 )
                    return (currentPointer - arr) / elemSize;

            }

            return -1;

        }

        partStart = nextPartStart;
        nextPartStart += partitionSize * elemSize;

    }

    return -1;

}