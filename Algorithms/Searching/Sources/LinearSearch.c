#include "../Headers/LinearSearch.h"
#include "../../../System/Utils.h"
#include "../../../DataStructure/Lists/Headers/Vector.h"
#include "../../../Unit Test/CuTest/CuTest.h"


/** This function will take an integer pointer,
 * then it will free it.
 *
 * Note: This function will be passed to the indices vector.
 *
 * @param n the integer pointer
 */

void intFreeFunLinSearch(void *n) {
    free(n);
}


/** This function takes two integers pointers,
 * then it will compare then and return the result.
 *
 * Note: This function will be passed to the indices vector.
 *
 * @param n1 the first integer pointer
 * @param n2 the second integer pointer
 * @return it will return the result of the comparison, zero if they are equal, minus integer if the second bigger, and positive integer if the first bigger
 */
int intCmpLinSearch(const void *n1, const void *n2) {
    return *(int *) n1 - *(int *) n2;
}


unsigned int *generateIntPointerLinSearch(unsigned int *num) {
    unsigned int *newInt = (unsigned int *) malloc(sizeof(unsigned int));
    memcpy(newInt, num, sizeof(unsigned int));

    return newInt;
}


/** This function will take an array and value,
 * then it will search for the value using the linear search algorithm.
 *
 * Note: if the value doesn't exist the function will return minus one (-1).
 *
 * Time Complexity: O(n).
 *
 * Space Complexity: O(1).
 *
 * @param arr the array pointer
 * @param value the target value pointer
 * @param length the length of the array
 * @param elemSize the array elements size in bytes
 * @param cmp the values comparator function pointer
 * @return it will return the index of the first occurrence of the value, other wise it will return -1
 */

int linearSearch(void *arr, void *value, int length, int elemSize, int (*cmp)(const void *, const void *)) {

    if (arr == NULL) {
#ifdef C_DATASTRUCTURES_ERRORSTESTSTRUCT_H
        ERROR_TEST->errorCode = NULL_POINTER;
        return -1;
#else
        fprintf(stderr, NULL_POINTER_MESSAGE, "passed array", "linear search");
        exit(NULL_POINTER);
#endif
    } else if (value == NULL) {
#ifdef C_DATASTRUCTURES_ERRORSTESTSTRUCT_H
        ERROR_TEST->errorCode = INVALID_ARG;
        return -1;
#else
        fprintf(stderr, INVALID_ARG_MESSAGE, "value pointer", "linear search");
        exit(INVALID_ARG);
#endif
    } else if (cmp == NULL) {
#ifdef C_DATASTRUCTURES_ERRORSTESTSTRUCT_H
        ERROR_TEST->errorCode = INVALID_ARG;
        return -1;
#else
        fprintf(stderr, INVALID_ARG_MESSAGE, "comparator function pointer", "linear search");
        exit(INVALID_ARG);
#endif
    } else if (length < 0) {
#ifdef C_DATASTRUCTURES_ERRORSTESTSTRUCT_H
        ERROR_TEST->errorCode = INVALID_ARG;
        return -1;
#else
        fprintf(stderr, INVALID_ARG_MESSAGE, "array length", "linear search");
        exit(INVALID_ARG);
#endif
    } else if (elemSize <= 0) {
#ifdef C_DATASTRUCTURES_ERRORSTESTSTRUCT_H
        ERROR_TEST->errorCode = INVALID_ARG;
        return -1;
#else
        fprintf(stderr, INVALID_ARG_MESSAGE, "element size", "linear search");
        exit(INVALID_ARG);
#endif
    }

    char *oneBytePointer = (char *) arr;

    for (int i = 0; i < length; i++) {
        if (cmp(value, oneBytePointer + i * elemSize) == 0)
            return i;

    }

    return -1;

}


/** This function will take an array and value,
 * then it will search for the value using the linear search algorithm.
 *
 * Note: if the value doesn't exist the function will return minus one (-1).
 *
 * Time Complexity: O(n).
 *
 * Space Complexity: O(1).
 *
 * @param arr the array pointer
 * @param value the target value pointer
 * @param length the length of the array
 * @param elemSize the array elements size in bytes
 * @param cmp the values comparator function pointer
 * @return it will return the index of the last occurrence of the value, other wise it will return -1
 */

int linearSearchGetLast(void *arr, void *value, int length, int elemSize, int (*cmp)(const void *, const void *)) {

    if (arr == NULL) {
#ifdef C_DATASTRUCTURES_ERRORSTESTSTRUCT_H
        ERROR_TEST->errorCode = NULL_POINTER;
        return -1;
#else
        fprintf(stderr, NULL_POINTER_MESSAGE, "passed array", "linear search");
        exit(NULL_POINTER);
#endif

    } else if (value == NULL) {
#ifdef C_DATASTRUCTURES_ERRORSTESTSTRUCT_H
        ERROR_TEST->errorCode = INVALID_ARG;
        return -1;
#else
        fprintf(stderr, INVALID_ARG_MESSAGE, "value pointer", "linear search");
        exit(INVALID_ARG);
#endif
    } else if (cmp == NULL) {
#ifdef C_DATASTRUCTURES_ERRORSTESTSTRUCT_H
        ERROR_TEST->errorCode = INVALID_ARG;
        return -1;
#else
        fprintf(stderr, INVALID_ARG_MESSAGE, "comparator function pointer", "linear search");
        exit(INVALID_ARG);
#endif
    } else if (length < 0) {
#ifdef C_DATASTRUCTURES_ERRORSTESTSTRUCT_H
        ERROR_TEST->errorCode = INVALID_ARG;
        return -1;
#else
        fprintf(stderr, INVALID_ARG_MESSAGE, "array length", "linear search");
        exit(INVALID_ARG);
#endif
    } else if (elemSize <= 0) {
#ifdef C_DATASTRUCTURES_ERRORSTESTSTRUCT_H
        ERROR_TEST->errorCode = INVALID_ARG;
        return -1;
#else
        fprintf(stderr, INVALID_ARG_MESSAGE, "element size", "linear search");
        exit(INVALID_ARG);
#endif
    }

    char *oneBytePointer = (char *) arr;

    for (int i = length - 1; i >= 0; i--) {
        if (cmp(value, oneBytePointer + i * elemSize) == 0)
            return i;

    }

    return -1;

}


/** This function will take an array and value,
 * then it will search for the value using the linear search algorithm.
 *
 * Note: if the value doesn't exist the function will return minus one (-1).
 *
 * Time Complexity: O(n).
 *
 * Space Complexity: O(k) and k is the number of occurrence.
 *
 * @param arr the array pointer
 * @param value the target value pointer
 * @param length the length of the array
 * @param elemSize the array elements size in bytes
 * @param cmp the values comparator function pointer
 * @return it will return a vector pointer that contains all the occurrences indices
 */

Vector *linearSearchGetAll(void *arr, void *value, int length, int elemSize, int (*cmp)(const void *, const void *)) {

    if (arr == NULL) {
#ifdef C_DATASTRUCTURES_ERRORSTESTSTRUCT_H
        ERROR_TEST->errorCode = NULL_POINTER;
        return NULL;
#else
        fprintf(stderr, NULL_POINTER_MESSAGE, "passed array", "linear search");
        exit(NULL_POINTER);
#endif
    } else if (value == NULL) {
#ifdef C_DATASTRUCTURES_ERRORSTESTSTRUCT_H
        ERROR_TEST->errorCode = INVALID_ARG;
        return NULL;
#else
        fprintf(stderr, INVALID_ARG_MESSAGE, "value pointer", "linear search");
        exit(INVALID_ARG);
#endif
    } else if (cmp == NULL) {
#ifdef C_DATASTRUCTURES_ERRORSTESTSTRUCT_H
        ERROR_TEST->errorCode = INVALID_ARG;
        return NULL;
#else
        fprintf(stderr, INVALID_ARG_MESSAGE, "comparator function pointer", "linear search");
        exit(INVALID_ARG);
#endif
    } else if (length < 0) {
#ifdef C_DATASTRUCTURES_ERRORSTESTSTRUCT_H
        ERROR_TEST->errorCode = INVALID_ARG;
        return NULL;
#else
        fprintf(stderr, INVALID_ARG_MESSAGE, "array length", "linear search");
        exit(INVALID_ARG);
#endif
    } else if (elemSize <= 0) {
#ifdef C_DATASTRUCTURES_ERRORSTESTSTRUCT_H
        ERROR_TEST->errorCode = INVALID_ARG;
        return NULL;
#else
        fprintf(stderr, INVALID_ARG_MESSAGE, "element size", "linear search");
        exit(INVALID_ARG);
#endif
    }


    char *oneBytePointer = (char *) arr;

    Vector *indicesVector = vectorInitialization(2, intFreeFunLinSearch, intCmpLinSearch);

    for (unsigned int i = 0; i < length; i++) {
        if (cmp(value, oneBytePointer + i * elemSize) == 0)
            vectorAdd(indicesVector, generateIntPointerLinSearch(&i));

    }

    return indicesVector;

}




