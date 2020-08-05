#include "../Headers/ExponentialSearch.h"
#include "../../../System/Utils.h"
#include "../Headers/BinarySearch.h"
#include "../../../Unit Test/CuTest/CuTest.h"






/** This function will take an array and value,
 * then it will search for the value using the exponential search algorithm.
 *
 * Note: if the value doesn't exist the function will return minus one (-1).
 *
 * Note: the array must be sorted so the algorithm actually works.
 *
 * Time Complexity: O( log(i) ) and i represents the length of searching area.
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

int exponentialSearch(void *arr, void *value, int length, int elemSize, int (*cmp)(const void *, const void *)) {

    if (arr == NULL) {
        #ifdef CU_TEST_H
            DUMMY_TEST_DATASTRUCTURE->errorCode = NULL_POINTER;
            return -1;
        #else
            printf(stderr, NULL_POINTER_MESSAGE, "passed array", "exponential search");
            exit(NULL_POINTER);
        #endif
    } else if (value == NULL) {
        #ifdef CU_TEST_H
            DUMMY_TEST_DATASTRUCTURE->errorCode = INVALID_ARG;
            return -1;
        #else
            fprintf(stderr, INVALID_ARG_MESSAGE, "value pointer", "exponential search");
            exit(INVALID_ARG);
        #endif
    } else if (cmp == NULL) {
        #ifdef CU_TEST_H
            DUMMY_TEST_DATASTRUCTURE->errorCode = INVALID_ARG;
            return -1;
        #else
            fprintf(stderr, INVALID_ARG_MESSAGE, "comparator function pointer", "exponential search");
            exit(INVALID_ARG);
        #endif
    } else if (length < 0) {
        #ifdef CU_TEST_H
            DUMMY_TEST_DATASTRUCTURE->errorCode = INVALID_ARG;
            return -1;
        #else
            fprintf(stderr, INVALID_ARG_MESSAGE, "array length", "exponential search");
            exit(INVALID_ARG);
        #endif
    } else if (elemSize <= 0) {
        #ifdef CU_TEST_H
            DUMMY_TEST_DATASTRUCTURE->errorCode = INVALID_ARG;
            return -1;
        #else
            fprintf(stderr, INVALID_ARG_MESSAGE, "element size", "exponential search");
            exit(INVALID_ARG);
        #endif
    }

    void *fPointer = arr, *lPointer = arr;
    while ( cmp(value, lPointer) > 0 ) {
        int partitionLength = lPointer - fPointer + 1;
        fPointer = lPointer;
        lPointer += partitionLength * 2 * elemSize;
        if (lPointer >= arr + length * elemSize) {
            lPointer = arr + (length - 1) * elemSize;
            break;
        }

    }

    int index = binarySearchI(fPointer, value, lPointer - fPointer + 1, elemSize, cmp);
    return index == -1 ? -1 : index + (fPointer - arr) / elemSize;

}