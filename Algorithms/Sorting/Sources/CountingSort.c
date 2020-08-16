#include "../Headers/CountingSort.h"
#include "../../../System/Utils.h"
#include "../../../DataStructure/Tables/Headers/HashMap.h"
#include "../../../Unit Test/CuTest/CuTest.h"


/** This function takes an integer pointer,
 * and then freeing it.
 *
 * Note: this function will be useful in the countingSortH function, because of the hash map.
 *
 * @param n the integer pointer
 */

void intFreeFunCountSort(void *n) {
    free(n);
}


/** This function will take two integers pointers,
 * then it will compare them.
 *
 * Note: this function will be useful in the countingSortH function, because of the hash map.
 *
 * @param n1 the first integer pointer
 * @param n2 the second integer pointer
 * @return it will return the result of the comparison, zero if they are equal, minus integer if the second bigger, and positive integer if the first bigger
 */

int intCmpCountSort(const void *n1, const void *n2) {
    return *(int *) n1 - *(int *) n2;
}


/** This function takes an integer number pointer,
 * then it will allocate a new integer space and copy the passed integer in the new space,
 * and finally return the new integer pointer.
 *
 * @param num the number pointer
 * @return it will return the new allocated pointer
 */

unsigned int *generateIntPointerCountSort(unsigned int *num) {
    unsigned int *newInt = (unsigned int *) malloc(sizeof(unsigned int));
    memcpy(newInt, num, sizeof(unsigned int));

    return newInt;
}


/** This function will take an integer pointer as a parameter,
 * then it will return the value of the integer.
 *
 * Note: this function will be useful to use in the hash map data structure.
 *
 * @param item the integer pointer
 * @return it will return the value of the integer as the unique hash key
 */

int intHashFunCountSort(const void *item) {
    return *(int *) item;
}


/** This function will sort an unsigned int array, using the counting sort algorithm.
 * This function takes the range of the number that are existing in the array.
 *
 * Note: this function will use a fixed length array to count the numbers.
 *
 * Time Complexity: worst: O(n) , best: O (n).
 *
 * Space Complexity: O(k) and k is the range of the numbers.
 *
 * @param arr the array pointer
 * @param length the length of the array
 * @param rangeStart the start range number << ex: [2,50] then the start is 2 >>
 * @param rangeEnd the end range number << ex: [2,50] then the end is 50 >>
 */

void countingSortA(unsigned int *arr, int length, unsigned int rangeStart, unsigned int rangeEnd) {

    if (arr == NULL) {
#ifdef C_DATASTRUCTURES_ERRORSTESTSTRUCT_H
        ERROR_TEST->errorCode = NULL_POINTER;
        return;
#else
        fprintf(stderr, NULL_POINTER_MESSAGE, "passed array", "counting sort");
        exit(NULL_POINTER);
#endif
    } else if (length < 0) {
#ifdef C_DATASTRUCTURES_ERRORSTESTSTRUCT_H
        ERROR_TEST->errorCode = INVALID_ARG;
        return;
#else
        fprintf(stderr, INVALID_ARG_MESSAGE, "array length", "counting sort");
        exit(INVALID_ARG);
#endif
    } else if (rangeEnd < rangeStart) {
#ifdef C_DATASTRUCTURES_ERRORSTESTSTRUCT_H
        ERROR_TEST->errorCode = INVALID_ARG;
        return;
#else
        fprintf(stderr, INVALID_ARG_MESSAGE, "start and end range", "counting sort");
        exit(INVALID_ARG);
#endif
    }

    unsigned int countingArrLength = rangeEnd - rangeStart + 1;
    unsigned int *countingArr = (unsigned int *) calloc(sizeof(unsigned int), countingArrLength);
    for (int i = 0; i < length; i++)
        countingArr[arr[i] - rangeStart]++;

    int index = 0;
    for (int i = 0; i < countingArrLength; i++) {

        while (countingArr[i] != 0) {
            arr[index++] = i + rangeStart;
            countingArr[i]--;
        }

    }


}


/** This function will sort an unsigned int array, using the counting sort algorithm.
 * This function takes the range of the number that are existing in the array.
 *
 * Note: this function will use a hash map to count the numbers.
 *
 * Time Complexity: worst: O(n) , best: O (n).
 *
 * Space Complexity: O(n) << because of the hash map>>.
 *
 * @param arr the array pointer
 * @param length the length of the array
 * @param rangeStart the start range number << ex: [2,50] then the start is 2 >>
 * @param rangeEnd the end range number << ex: [2,50] then the end is 50 >>
 */

void countingSortH(unsigned int *arr, int length, unsigned int rangeStart, unsigned int rangeEnd) {

    if (arr == NULL) {
#ifdef C_DATASTRUCTURES_ERRORSTESTSTRUCT_H
        ERROR_TEST->errorCode = NULL_POINTER;
        return;
#else
        fprintf(stderr, NULL_POINTER_MESSAGE, "passed array", "counting sort");
        exit(NULL_POINTER);
#endif
    } else if (length < 0) {
#ifdef C_DATASTRUCTURES_ERRORSTESTSTRUCT_H
        ERROR_TEST->errorCode = INVALID_ARG;
        return;
#else
        fprintf(stderr, INVALID_ARG_MESSAGE, "array length", "counting sort");
        exit(INVALID_ARG);
#endif
    } else if (rangeEnd < rangeStart) {
#ifdef C_DATASTRUCTURES_ERRORSTESTSTRUCT_H
        ERROR_TEST->errorCode = INVALID_ARG;
        return;
#else
        fprintf(stderr, INVALID_ARG_MESSAGE, "start and end range", "counting sort");
        exit(INVALID_ARG);
#endif
    }

    HashMap *countingMap = hashMapInitialization(intFreeFunCountSort, intFreeFunCountSort, intCmpCountSort,
                                                 intHashFunCountSort);

    for (int i = 0; i < length; i++) {
        unsigned int *newNumPointer = generateIntPointerCountSort(arr + i);

        if (!hashMapContains(countingMap, newNumPointer)) {
            unsigned int initialCount = 1;
            unsigned int *countPointer = generateIntPointerCountSort(&initialCount);
            hashMapInsert(countingMap, newNumPointer, countPointer);
        } else {
            unsigned int *currentCount = hashMapGet(countingMap, newNumPointer);
            *currentCount += 1;
            unsigned int *newCount = generateIntPointerCountSort(currentCount);
            hashMapInsert(countingMap, newNumPointer, newCount);
        }

    }

    for (unsigned int i = rangeStart, index = 0; i <= rangeEnd; i++) {

        unsigned int *currentCount = (unsigned int *) hashMapGet(countingMap, &i);

        while (currentCount != NULL && *currentCount > 0) {
            arr[index++] = i;
            *currentCount -= 1;
        }

    }

    destroyHashMap(countingMap);


}