#include "../Headers/ArraysAlg.h"
#include "../../Sorting/Headers/SwapFunction.h"
#include "../../../System/Utils.h"
#include "../../../DataStructure/Tables/Headers/HashMap.h"




/** This function is an empty function,
 * will be useful to use the hash map without freeing the keys
 * @param item
 */

void nullFreeFunArrAlg(void *item) {}




/** This function takes an integer pointer,
 * and then freeing it.
 * Note: this function will be useful to use the hash map.
 * @param n the integer pointer
 */

void intFreeFunArrAlg(void *n) {
    free(n);
}



/** This function will take two integers pointers,
 * then it will compare them.
 * Note: this function will be useful to use the hash map.
 * @param n1 the first integer pointer
 * @param n2 the second integer pointer
 * @return it will return the result of the comparison, zero if they are equal, minus integer if the second bigger, and positive integer if the first bigger
 */

int intCmpArrAlg(const void *n1, const void * n2) {
    return *(int *)n1 - *(int *)n2;
}





/** This function takes an integer number pointer,
 * then it will allocate a new integer space and copy the passed integer in the new space,
 * and finally return the new integer pointer.
 * Note: this function will be useful to use the hash map.
 * @param num the number pointer
 * @return it will return the new allocated pointer
 */

unsigned int *generateIntPointerArrAlg(unsigned int *num) {
    unsigned int *newInt = (unsigned int *) malloc(sizeof(unsigned int));
    memcpy(newInt, num, sizeof(unsigned int));

    return newInt;
}





/** This function will take an array then it will reverse the array.
 *
 * Time Complexity: O (n)
 * Space Complexity: O (1)
 *
 * @param arr the array pointer
 * @param length the length of the array
 * @param elemSize the array elements size in bytes
 */

void reverseArray(void *arr, int length, int elemSize) {

    if (arr == NULL) {
        fprintf(stderr, NULL_POINTER_MESSAGE, "passed array", "reversing array");
        exit(NULL_POINTER);
    } else if (length < 0) {
        fprintf(stderr, INVALID_ARG_MESSAGE, "array length", "reversing array");
        exit(INVALID_ARG);
    } else if (elemSize <= 0) {
        fprintf(stderr, INVALID_ARG_MESSAGE, "element size", "reversing array");
        exit(INVALID_ARG);
    }


    for (int i = 0; i < length / 2; i++)
        swap(arr + i * elemSize, arr + (length - 1 - i) * elemSize, elemSize);


}









/** This function will take an array then,
 * it will return a pointer to the most frequent value in the array.
 * Note: the function will return null if the array are empty.
 * Note: if there is more than one value that has the same frequent, then the function only will return one of them,
 * without knowing which one << it depends on the hashing function in the hash map >>.
 *
 * Time Complexity: O (n)
 * Space Complexity: O (k) and k is the different values in the array
 *
 * @param arr the array pointer
 * @param length the length of the array
 * @param elemSize the array elements size in bytes
 * @param cmp the elements comparator function pointer
 * @return it will return the most frequent value in the array, or it will return NULL if the array are empty
 */

void *mostFrequentArrValue(void *arr, int length, int elemSize, int (*cmp)(const void *, const void *)) {
    if (arr == NULL) {
        fprintf(stderr, NULL_POINTER_MESSAGE, "passed array", "most frequent value algorithm");
        exit(NULL_POINTER);
    } else if (cmp == NULL) {
        fprintf(stderr, INVALID_ARG_MESSAGE, "comparator function pointer", "most frequent value algorithm");
        exit(INVALID_ARG);
    } else if (length < 0) {
        fprintf(stderr, INVALID_ARG_MESSAGE, "array length", "most frequent value algorithm");
        exit(INVALID_ARG);
    } else if (elemSize <= 0) {
        fprintf(stderr, INVALID_ARG_MESSAGE, "element size", "most frequent value algorithm");
        exit(INVALID_ARG);
    }

    HashMap *countingMap = hashMapInitialization(nullFreeFunArrAlg, intFreeFunArrAlg, cmp);
    unsigned int oneValue = 1;

    for (int i = 0; i < length; i++) {

        void *currentItem = arr + i * elemSize;
        int *currentFreq = (int *) hashMapGet(countingMap, currentItem, elemSize);

        if (currentFreq == NULL)
            hashMapInsert(countingMap, currentItem, elemSize, generateIntPointerArrAlg(&oneValue));
        else
            *currentFreq += 1;

    }

    Entry **mapEntries = hashMapToEntryArray(countingMap);
    void *mostFreqValue = NULL;
    int mostFreq = -1;
    int entriesLength = hashMapGetLength(countingMap);

    for (int i = 0; i < entriesLength; i++) {

        if (mostFreq < *(int *)mapEntries[i]->item) {
            mostFreqValue = mapEntries[i]->key;
            mostFreq = *(int *)mapEntries[i]->item;
        }

        hashMapDelete(countingMap, mapEntries[i]->key, elemSize);

    }

    free(mapEntries);
    destroyHashMap(countingMap);

    return mostFreqValue;

}






/** This function will take an array then it will print it.
 * The printing will be like this:
 * [element1, element2, ...]
 * The passed printing function should only print the value without any increases.
 * The function will use the stdout file to print the array.
 * @param arr the array pointer
 * @param length the length of the array
 * @param elemSize the array elements size in bytes
 * @param printFun the values printing funciton pointer
 */

void printArr(void *arr, int length, int elemSize, void (*printFun)(void *)) {

    if (arr == NULL) {
        fprintf(stderr, NULL_POINTER_MESSAGE, "passed array", "printing array");
        exit(NULL_POINTER);
    } else if (printFun == NULL) {
        fprintf(stderr, INVALID_ARG_MESSAGE, "printing function pointer", "printing array");
        exit(INVALID_ARG);
    } else if (length < 0) {
        fprintf(stderr, INVALID_ARG_MESSAGE, "array length", "printing array");
        exit(INVALID_ARG);
    } else if (elemSize <= 0) {
        fprintf(stderr, INVALID_ARG_MESSAGE, "element size", "printing array");
        exit(INVALID_ARG);
    }

    fprintf(stdout, "[");
    for (int i = 0; i < length; i++) {
        printFun(arr + i * elemSize);
        if (i != length - 1)
            fprintf(stdout, ", ");

    }
    fprintf(stdout, "]");

}