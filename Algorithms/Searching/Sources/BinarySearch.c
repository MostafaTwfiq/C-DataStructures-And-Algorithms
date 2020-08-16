#include "../Headers/BinarySearch.h"
#include "../../../System/Utils.h"
#include "../../../Unit Test/CuTest/CuTest.h"


int binarySearchHelper(char *arr, void *value, int fIndex, int lIndex, int elemSize,
                       int (*cmp)(const void *, const void *));


/** This function will take an array and value,
 * then it will search for the value using the binary search algorithm.
 *
 * Note: if the value doesn't exist the function will return minus one (-1).
 *
 * Note: the array must be sorted so the algorithm actually works.
 *
 * Note: this function will search for the value iterative.
 *
 * Time Complexity: O( log(n) ).
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

int binarySearchI(void *arr, void *value, int length, int elemSize, int (*cmp)(const void *, const void *)) {


    if (arr == NULL) {
#ifdef C_DATASTRUCTURES_ERRORSTESTSTRUCT_H
        ERROR_TEST->errorCode = NULL_POINTER;
        return - 1;
#else
        fprintf(stderr, NULL_POINTER_MESSAGE, "passed array", "binary search");
        exit(NULL_POINTER);
#endif
    } else if (value == NULL) {
#ifdef C_DATASTRUCTURES_ERRORSTESTSTRUCT_H
        ERROR_TEST->errorCode = INVALID_ARG;
        return -1;
#else
        fprintf(stderr, INVALID_ARG_MESSAGE, "value pointer", "binary search");
        exit(INVALID_ARG);
#endif
    } else if (cmp == NULL) {
#ifdef C_DATASTRUCTURES_ERRORSTESTSTRUCT_H
        ERROR_TEST->errorCode = INVALID_ARG;
        return -1;
#else
        fprintf(stderr, INVALID_ARG_MESSAGE, "comparator function pointer", "binary search");
        exit(INVALID_ARG);
#endif
    } else if (length < 0) {
#ifdef C_DATASTRUCTURES_ERRORSTESTSTRUCT_H
        ERROR_TEST->errorCode = INVALID_ARG;
        return -1;
#else
        fprintf(stderr, INVALID_ARG_MESSAGE, "array length", "binary search");
        exit(INVALID_ARG);
#endif
    } else if (elemSize <= 0) {
#ifdef C_DATASTRUCTURES_ERRORSTESTSTRUCT_H
        ERROR_TEST->errorCode = INVALID_ARG;
        return -1;
#else
        fprintf(stderr, INVALID_ARG_MESSAGE, "element size", "binary search");
        exit(INVALID_ARG);
#endif
    }


    char *oneBytePointer = (char *) arr;

    int fIndex = 0, lIndex = length - 1, middleIndex;
    while (fIndex <= lIndex) {

        middleIndex = (fIndex + lIndex) / 2;

        if (cmp(value, oneBytePointer + middleIndex * elemSize) == 0)
            return middleIndex;
        else if (cmp(value, oneBytePointer + middleIndex * elemSize) < 0)
            lIndex = middleIndex - 1;
        else
            fIndex = middleIndex + 1;

    }

    return -1;

}


/** This function will take an array and value,
 * then it will search for the value using the binary search algorithm.
 *
 * Note: if the value doesn't exist the function will return minus one (-1).
 *
 * Note: the array must be sorted so the algorithm actually works.
 *
 * Note: this function will search for the value recursively.
 *
 * Time Complexity: O( log(n) ).
 *
 * Space Complexity: O( log(n) ) << because of the recursive calls >>.
 *
 * @param arr the array pointer
 * @param value the target value pointer
 * @param length the length of the array
 * @param elemSize the array elements size in bytes
 * @param cmp the values comparator function
 * @return it will return the index of the value if found, other wise it will return -1
 */

int binarySearchR(void *arr, void *value, int length, int elemSize, int (*cmp)(const void *, const void *)) {

    if (arr == NULL) {
#ifdef C_DATASTRUCTURES_ERRORSTESTSTRUCT_H
        ERROR_TEST->errorCode = NULL_POINTER;
        return -1;
#else
        fprintf(stderr, NULL_POINTER_MESSAGE, "passed array", "binary search");
        exit(NULL_POINTER);
#endif
    } else if (value == NULL) {
#ifdef C_DATASTRUCTURES_ERRORSTESTSTRUCT_H
        ERROR_TEST->errorCode = INVALID_ARG;
        return -1;
#else
        fprintf(stderr, INVALID_ARG_MESSAGE, "value pointer", "binary search");
        exit(INVALID_ARG);
#endif
    } else if (cmp == NULL) {
#ifdef C_DATASTRUCTURES_ERRORSTESTSTRUCT_H
        ERROR_TEST->errorCode = INVALID_ARG;
        return -1;
#else
        fprintf(stderr, INVALID_ARG_MESSAGE, "comparator function pointer", "binary search");
        exit(INVALID_ARG);
#endif
    } else if (length < 0) {
#ifdef C_DATASTRUCTURES_ERRORSTESTSTRUCT_H
        ERROR_TEST->errorCode = INVALID_ARG;
        return -1;
#else
        fprintf(stderr, INVALID_ARG_MESSAGE, "array length", "binary search");
        exit(INVALID_ARG);
#endif
    } else if (elemSize <= 0) {
#ifdef C_DATASTRUCTURES_ERRORSTESTSTRUCT_H
        ERROR_TEST->errorCode = INVALID_ARG;
        return -1;
#else
        fprintf(stderr, INVALID_ARG_MESSAGE, "element size", "binary search");
        exit(INVALID_ARG);
#endif
    }

    return binarySearchHelper((char *) arr, value, 0, length - 1, elemSize, cmp);

}


/** This function will take an array and value,
 * then it will recursively search for the value using the binary search algorithm.
 *
 * Note: if the value doesn't exist the function will return minus one (-1).
 *
 * Note: the array must be sorted so the algorithm actually works.
 *
 * Note: this function should only be called by the binarySearchR function.
 *
 * Time Complexity: O( log(n) ).
 *
 * Space Complexity: O( log(n) ) << because of the recursive calls >>.
 *
 * @param arr the array pointer
 * @param value the target value pointer
 * @param length the length of the array
 * @param elemSize the array elements size in bytes
 * @param cmp the values comparator function
 * @return it will return the index of the value if found, other wise it will return -1
 */

int binarySearchHelper(char *arr, void *value, int fIndex, int lIndex, int elemSize,
                       int (*cmp)(const void *, const void *)) {
    if (fIndex > lIndex)
        return -1;

    int middleIndex = (fIndex + lIndex) / 2;

    if (cmp(value, arr + middleIndex * elemSize) == 0)
        return middleIndex;
    else if (cmp(value, arr + middleIndex * elemSize) < 0)
        return binarySearchHelper(arr, value, fIndex, middleIndex - 1, elemSize, cmp);
    else
        return binarySearchHelper(arr, value, middleIndex + 1, lIndex, elemSize, cmp);


}
