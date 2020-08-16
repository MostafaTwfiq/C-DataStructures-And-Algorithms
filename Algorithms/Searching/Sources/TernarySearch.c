#include "../Headers/TernarySearch.h"
#include "../../../System/Utils.h"
#include "../../../Unit Test/CuTest/CuTest.h"


int ternarySearchHelper(char *arr, void *value, int fIndex, int lIndex, int elemSize,
                        int (*cmp)(const void *, const void *));


/** This function will take an array and value,
 * then it will search for the value using the ternary search algorithm.
 *
 * Note: if the value doesn't exist the function will return minus one (-1).
 *
 * Note: the array must be sorted so the algorithm actually works.
 *
 * Note: this function will search for the value iterative.
 *
 * Time Complexity: O( log(n) to the base 3 ).
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

int ternarySearchI(void *arr, void *value, int length, int elemSize, int (*cmp)(const void *, const void *)) {

    if (arr == NULL) {
#ifdef C_DATASTRUCTURES_ERRORSTESTSTRUCT_H
        ERROR_TEST->errorCode = NULL_POINTER;
        return -1;
#else
        fprintf(stderr, NULL_POINTER_MESSAGE, "passed array", "ternary search");
        exit(NULL_POINTER);
#endif
    } else if (value == NULL) {
#ifdef C_DATASTRUCTURES_ERRORSTESTSTRUCT_H
        ERROR_TEST->errorCode = INVALID_ARG;
        return -1;
#else
        fprintf(stderr, INVALID_ARG_MESSAGE, "value pointer", "ternary search");
        exit(INVALID_ARG);
#endif
    } else if (cmp == NULL) {
#ifdef C_DATASTRUCTURES_ERRORSTESTSTRUCT_H
        ERROR_TEST->errorCode = INVALID_ARG;
        return -1;
#else
        fprintf(stderr, INVALID_ARG_MESSAGE, "comparator function pointer", "ternary search");
        exit(INVALID_ARG);
#endif
    } else if (length < 0) {
#ifdef C_DATASTRUCTURES_ERRORSTESTSTRUCT_H
        ERROR_TEST->errorCode = INVALID_ARG;
        return -1;
#else
        fprintf(stderr, INVALID_ARG_MESSAGE, "array length", "ternary search");
        exit(INVALID_ARG);
#endif
    } else if (elemSize <= 0) {
#ifdef C_DATASTRUCTURES_ERRORSTESTSTRUCT_H
        ERROR_TEST->errorCode = INVALID_ARG;
        return -1;
#else
        fprintf(stderr, INVALID_ARG_MESSAGE, "element size", "ternary search");
        exit(INVALID_ARG);
#endif
    }


    char *oneBytePointer = (char *) arr;

    int fIndex = 0, lIndex = length - 1, partitionSize, fMiddle, sMiddle;
    while (fIndex <= lIndex) {

        partitionSize = (lIndex - fIndex) / 3;
        fMiddle = fIndex + partitionSize;
        sMiddle = lIndex - partitionSize;

        if (cmp(value, oneBytePointer + fMiddle * elemSize) == 0)
            return fMiddle;
        else if (cmp(value, oneBytePointer + sMiddle * elemSize) == 0)
            return sMiddle;
        else if (cmp(value, oneBytePointer + fMiddle * elemSize) < 0)
            lIndex = fMiddle - 1;
        else if (cmp(value, oneBytePointer + sMiddle * elemSize) > 0)
            fIndex = sMiddle + 1;
        else {
            fIndex = fMiddle + 1;
            lIndex = sMiddle - 1;
        }

    }

    return -1;

}


/** This function will take an array and value,
 * then it will search for the value using the ternary search algorithm.
 *
 * Note: if the value doesn't exist the function will return minus one (-1).
 *
 * Note: the array must be sorted so the algorithm actually works.
 *
 * Note: this function will search for the value recursively.
 *
 * Time Complexity: O( log(n) to the base 3 ).
 *
 * Space Complexity: O( log(n) to the base 3 ).
 *
 * @param arr the array pointer
 * @param value the target value pointer
 * @param length the length of the array
 * @param elemSize the array elements size in bytes
 * @param cmp the values comparator function
 * @return it will return the index of the value if found, other wise it will return -1
 */

int ternarySearchR(void *arr, void *value, int length, int elemSize, int (*cmp)(const void *, const void *)) {

    if (arr == NULL) {
#ifdef C_DATASTRUCTURES_ERRORSTESTSTRUCT_H
        ERROR_TEST->errorCode = NULL_POINTER;
        return -1;
#else
        fprintf(stderr, NULL_POINTER_MESSAGE, "passed array", "ternary search");
        exit(NULL_POINTER);
#endif
    } else if (value == NULL) {
#ifdef C_DATASTRUCTURES_ERRORSTESTSTRUCT_H
        ERROR_TEST->errorCode = INVALID_ARG;
        return -1;
#else
        fprintf(stderr, INVALID_ARG_MESSAGE, "value pointer", "ternary search");
        exit(INVALID_ARG);
#endif
    } else if (cmp == NULL) {
#ifdef C_DATASTRUCTURES_ERRORSTESTSTRUCT_H
        ERROR_TEST->errorCode = INVALID_ARG;
        return -1;
#else
        fprintf(stderr, INVALID_ARG_MESSAGE, "comparator function pointer", "ternary search");
        exit(INVALID_ARG);
#endif
    } else if (length < 0) {
#ifdef C_DATASTRUCTURES_ERRORSTESTSTRUCT_H
        ERROR_TEST->errorCode = INVALID_ARG;
        return -1;
#else
        fprintf(stderr, INVALID_ARG_MESSAGE, "array length", "ternary search");
        exit(INVALID_ARG);
#endif
    } else if (elemSize <= 0) {
#ifdef C_DATASTRUCTURES_ERRORSTESTSTRUCT_H
        ERROR_TEST->errorCode = INVALID_ARG;
        return -1;
#else
        fprintf(stderr, INVALID_ARG_MESSAGE, "element size", "ternary search");
        exit(INVALID_ARG);
#endif
    }

    return ternarySearchHelper((char *) arr, value, 0, length - 1, elemSize, cmp);

}


/** This function will take an array and value,
 * then it will recursively search for the value using the ternary search algorithm.
 *
 * Note: if the value doesn't exist the function will return minus one (-1).
 *
 * Note: the array must be sorted so the algorithm actually works.
 *
 * Note: this function should only be called by the ternarySearchR function.
 *
 * Time Complexity: O( log(n) to the base 3 ).
 *
 * Space Complexity: O( log(n) to the base 3 ).
 *
 * @param arr the array pointer
 * @param value the target value pointer
 * @param length the length of the array
 * @param elemSize the array elements size in bytes
 * @param cmp the values comparator function
 * @return it will return the index of the value if found, other wise it will return -1
 */

int ternarySearchHelper(char *arr, void *value, int fIndex, int lIndex, int elemSize,
                        int (*cmp)(const void *, const void *)) {
    if (fIndex > lIndex)
        return -1;


    int partitionSize = (lIndex - fIndex) / 3;
    int fMiddle = fIndex + partitionSize;
    int sMiddle = lIndex - partitionSize;

    if (cmp(value, arr + fMiddle * elemSize) == 0)
        return fMiddle;
    else if (cmp(value, arr + sMiddle * elemSize) == 0)
        return sMiddle;
    else if (cmp(value, arr + fMiddle * elemSize) < 0)
        return ternarySearchHelper(arr, value, fIndex, fMiddle - 1, elemSize, cmp);
    else if (cmp(value, arr + sMiddle * elemSize) > 0)
        return ternarySearchHelper(arr, value, sMiddle + 1, lIndex, elemSize, cmp);
    else
        return ternarySearchHelper(arr, value, fMiddle + 1, sMiddle - 1, elemSize, cmp);


}