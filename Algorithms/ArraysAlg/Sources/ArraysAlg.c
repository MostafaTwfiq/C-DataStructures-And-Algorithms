#include "../Headers/ArraysAlg.h"
#include "../../Sorting/Headers/SwapFunction.h"
#include "../../../System/Utils.h"
#include "../../../DataStructure/Tables/Headers/HashMap.h"
#include "../../../DataStructure/Tables/Headers/HashSet.h"
#include "../../../DataStructure/Lists/Headers/Vector.h"
#include "../../Sorting/Headers/Sorting.h"
#include "../../Searching/Headers/Searching.h"
#include "../../../Unit Test/CuTest/CuTest.h"


/** This function is an empty function,
 * will be useful to use the hash map without freeing the keys.
 *
 * @param item
 */

void nullFreeFunArrAlg(void *item) {}


/** This function takes an integer pointer,
 * and then freeing it.
 *
 * Note: this function will be useful to use the hash map.
 *
 * @param n the integer pointer
 */

void intFreeFunArrAlg(void *n) {
    free(n);
}


/** This function will take two integers pointers,
 * then it will compare them.
 *
 * Note: this function will be useful to use the hash map.
 *
 * @param n1 the first integer pointer
 * @param n2 the second integer pointer
 * @return it will return the result of the comparison, zero if they are equal, minus integer if the second bigger, and positive integer if the first bigger
 */

int intCmpArrAlg(const void *n1, const void *n2) {
    return *(int *) n1 - *(int *) n2;
}


/** This function takes an integer number pointer,
 * then it will allocate a new integer space and copy the passed integer in the new space,
 * and finally return the new integer pointer.
 *
 * Note: this function will be useful to use the hash map.
 *
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
 * Time Complexity: O (n).
 *
 * Space Complexity: O (1).
 *
 * @param arr the array pointer
 * @param length the length of the array
 * @param elemSize the array elements size in bytes
 */

void reverseArray(void *arr, int length, int elemSize) {

    if (arr == NULL) {
#ifdef C_DATASTRUCTURES_ERRORSTESTSTRUCT_H
        ERROR_TEST->errorCode = NULL_POINTER;
        return;
#else
        fprintf(stderr, NULL_POINTER_MESSAGE, "passed array", "reversing array");
        exit(NULL_POINTER);
#endif
    } else if (length < 0) {
#ifdef C_DATASTRUCTURES_ERRORSTESTSTRUCT_H
        ERROR_TEST->errorCode = INVALID_ARG;
        return;
#else
        fprintf(stderr, INVALID_ARG_MESSAGE, "array length", "reversing array");
        exit(INVALID_ARG);
#endif
    } else if (elemSize <= 0) {
#ifdef C_DATASTRUCTURES_ERRORSTESTSTRUCT_H
        ERROR_TEST->errorCode = INVALID_ARG;
        return;
#else
        fprintf(stderr, INVALID_ARG_MESSAGE, "element size", "reversing array");
        exit(INVALID_ARG);
#endif
    }


    char *oneBytePointer = (char *) arr;

    for (int i = 0; i < length / 2; i++)
        swap(oneBytePointer + i * elemSize, oneBytePointer + (length - 1 - i) * elemSize, elemSize);


}


/** This function will take an array then,
 * it will return a pointer to the most frequent value in the array.
 *
 * Note: because the function uses hash map, you need to pass the hashing function.
 *
 * Note: the function will return null if the array are empty.
 *
 * Note: if there is more than one value that has the same frequent, then the function only will return one of them,
 * without knowing which one it depends on the hashing function in the hash map >>.
 *
 * Note: this function will use hash map to detect the duplicates.
 *
 * Time Complexity: O (n).
 *
 * Space Complexity: O (k) and k is the different values in the array.
 *
 * @param arr the array pointer
 * @param length the length of the array
 * @param elemSize the array elements size in bytes
 * @param cmp the elements comparator function pointer
 * @param hashFun the hashing function that will return a unique integer representing the hash map key
 * @return it will return the most frequent value in the array, or it will return NULL if the array are empty
 */

void *mostFrequentArrValueH(void *arr, int length, int elemSize, int (*cmp)(const void *, const void *),
                            int (*hashFun)(const void *)) {

    if (arr == NULL) {
#ifdef C_DATASTRUCTURES_ERRORSTESTSTRUCT_H
        ERROR_TEST->errorCode = NULL_POINTER;
        return NULL;
#else
        fprintf(stderr, NULL_POINTER_MESSAGE, "passed array", "most frequent value algorithm");
        exit(NULL_POINTER);
#endif
    } else if (cmp == NULL) {
#ifdef C_DATASTRUCTURES_ERRORSTESTSTRUCT_H
        ERROR_TEST->errorCode = INVALID_ARG;
        return NULL;
#else
        fprintf(stderr, INVALID_ARG_MESSAGE, "comparator function pointer", "most frequent value algorithm");
        exit(INVALID_ARG);
#endif
    } else if (length < 0) {
#ifdef C_DATASTRUCTURES_ERRORSTESTSTRUCT_H
        ERROR_TEST->errorCode = INVALID_ARG;
        return NULL;
#else
        fprintf(stderr, INVALID_ARG_MESSAGE, "array length", "most frequent value algorithm");
        exit(INVALID_ARG);
#endif
    } else if (elemSize <= 0) {
#ifdef C_DATASTRUCTURES_ERRORSTESTSTRUCT_H
        ERROR_TEST->errorCode = INVALID_ARG;
        return NULL;
#else
        fprintf(stderr, INVALID_ARG_MESSAGE, "element size", "most frequent value algorithm");
        exit(INVALID_ARG);
#endif
    } else if (hashFun == NULL) {
#ifdef C_DATASTRUCTURES_ERRORSTESTSTRUCT_H
        ERROR_TEST->errorCode = INVALID_ARG;
        return NULL;
#else
        fprintf(stderr, INVALID_ARG_MESSAGE, "hash function pointer", "most frequent value algorithm");
        exit(INVALID_ARG);
#endif
    }

    char *oneBytePointer = (char *) arr;

    HashMap *countingMap = hashMapInitialization(nullFreeFunArrAlg, intFreeFunArrAlg, cmp, hashFun);
    unsigned int oneValue = 1;

    for (int i = 0; i < length; i++) {

        char *currentItem = oneBytePointer + i * elemSize;
        int *currentFreq = (int *) hashMapGet(countingMap, currentItem);

        if (currentFreq == NULL)
            hashMapInsert(countingMap, currentItem, generateIntPointerArrAlg(&oneValue));
        else
            *currentFreq += 1;

    }

    Entry **mapEntries = hashMapToEntryArray(countingMap);
    void *mostFreqValue = NULL;
    int mostFreq = -1;
    int entriesLength = hashMapGetLength(countingMap);

    for (int i = 0; i < entriesLength; i++) {

        if (mostFreq < *(int *) mapEntries[i]->item) {
            mostFreqValue = mapEntries[i]->key;
            mostFreq = *(int *) mapEntries[i]->item;
        }

        hashMapDelete(countingMap, mapEntries[i]->key);

    }

    free(mapEntries);
    destroyHashMap(countingMap);

    return mostFreqValue;

}


/** This function will take an array then,
 * it will return a pointer to the most frequent value in the array.
 *
 * Note: the function will return null if the array are empty.
 *
 * Note: if there is more than one value that has the same frequent, then the function only will return the first one.
 *
 * Note: this function will uses arrays to detect the duplicates.
 *
 * Time Complexity: O (n ^ 2).
 *
 * Space Complexity: O (2n).
 *
 * @param arr the array pointer
 * @param length the length of the array
 * @param elemSize the array elements size in bytes
 * @param cmp the elements comparator function pointer
 * @return it will return the most frequent value in the array, or it will return NULL if the array are empty
 */

void *mostFrequentArrValueA(void *arr, int length, int elemSize, int (*cmp)(const void *, const void *)) {

    if (arr == NULL) {
#ifdef C_DATASTRUCTURES_ERRORSTESTSTRUCT_H
        ERROR_TEST->errorCode = NULL_POINTER;
        return NULL;
#else
        fprintf(stderr, NULL_POINTER_MESSAGE, "passed array", "most frequent value algorithm");
        exit(NULL_POINTER);
#endif
    } else if (cmp == NULL) {
#ifdef C_DATASTRUCTURES_ERRORSTESTSTRUCT_H
        ERROR_TEST->errorCode = INVALID_ARG;
        return NULL;
#else
        fprintf(stderr, INVALID_ARG_MESSAGE, "comparator function pointer", "most frequent value algorithm");
        exit(INVALID_ARG);
#endif
    } else if (length < 0) {
#ifdef C_DATASTRUCTURES_ERRORSTESTSTRUCT_H
        ERROR_TEST->errorCode = INVALID_ARG;
        return NULL;
#else
        fprintf(stderr, INVALID_ARG_MESSAGE, "array length", "most frequent value algorithm");
        exit(INVALID_ARG);
#endif
    } else if (elemSize <= 0) {
#ifdef C_DATASTRUCTURES_ERRORSTESTSTRUCT_H
        ERROR_TEST->errorCode = INVALID_ARG;
        return NULL;
#else
        fprintf(stderr, INVALID_ARG_MESSAGE, "element size", "most frequent value algorithm");
        exit(INVALID_ARG);
#endif
    }

    char *oneBytePointer = (char *) arr;

    Vector *valuesVector = vectorInitialization(length / 2 == 0 ? 1 : length / 2, nullFreeFunArrAlg, cmp);
    Vector *counterVector = vectorInitialization(length / 2 == 0 ? 1 : length / 2, intFreeFunArrAlg, intCmpArrAlg);
    unsigned int oneValue = 1;

    for (int i = 0; i < length; i++) {

        char *currentItem = oneBytePointer + i * elemSize;
        int currentItemIndex = vectorGetIndex(valuesVector, currentItem);

        if (currentItemIndex == -1) {
            vectorAdd(valuesVector, currentItem);
            vectorAdd(counterVector, generateIntPointerArrAlg(&oneValue));
        } else {
            int *currentFreq = vectorGet(counterVector, currentItemIndex);
            *currentFreq += 1;
        }

    }

    void *mostFreqValue = NULL;
    int mostFreq = -1;
    int mostFreqValueIndex = -1;

    for (int i = 0; i < vectorGetLength(counterVector); i++) {

        if (mostFreq < *(int *) vectorGet(counterVector, i)) {
            mostFreq = *(int *) vectorGet(counterVector, i);
            mostFreqValueIndex = i;
        }

    }


    if (mostFreqValueIndex != -1)
        mostFreqValue = vectorGet(valuesVector, mostFreqValueIndex);

    destroyVector(valuesVector);
    destroyVector(counterVector);

    return mostFreqValue;

}


/** This function will take an array then it will print it.
 *
 * The printing will be like this:
 *
 * [element1, element2, ...]
 *
 * The passed printing function should only print the value without any increases.
 *
 * The function will use the stdout file to print the array.
 *
 * @param arr the array pointer
 * @param length the length of the array
 * @param elemSize the array elements size in bytes
 * @param printFun the values printing function pointer
 */

void printArr(void *arr, int length, int elemSize, void (*printFun)(void *)) {

    if (arr == NULL) {
#ifdef C_DATASTRUCTURES_ERRORSTESTSTRUCT_H
        ERROR_TEST->errorCode = NULL_POINTER;
        return;
#else
        fprintf(stderr, NULL_POINTER_MESSAGE, "passed array", "printing array");
        exit(NULL_POINTER);
#endif
    } else if (printFun == NULL) {
#ifdef C_DATASTRUCTURES_ERRORSTESTSTRUCT_H
        ERROR_TEST->errorCode = INVALID_ARG;
        return;
#else
        fprintf(stderr, INVALID_ARG_MESSAGE, "printing function pointer", "printing array");
        exit(INVALID_ARG);
#endif
    } else if (length < 0) {
#ifdef C_DATASTRUCTURES_ERRORSTESTSTRUCT_H
        ERROR_TEST->errorCode = INVALID_ARG;
        return;
#else
        fprintf(stderr, INVALID_ARG_MESSAGE, "array length", "printing array");
        exit(INVALID_ARG);
#endif
    } else if (elemSize <= 0) {
#ifdef C_DATASTRUCTURES_ERRORSTESTSTRUCT_H
        ERROR_TEST->errorCode = INVALID_ARG;
        return;
#else
        fprintf(stderr, INVALID_ARG_MESSAGE, "element size", "printing array");
        exit(INVALID_ARG);
#endif
    }


#ifdef C_DATASTRUCTURES_ERRORSTESTSTRUCT_H
#else
    fprintf(stdout, "[");
#endif

    char *oneBytePointer = (char *) arr;

    for (int i = 0; i < length; i++) {

        printFun(oneBytePointer + i * elemSize);

#ifdef C_DATASTRUCTURES_ERRORSTESTSTRUCT_H
#else

        if (i != length - 1)
            fprintf(stdout, ", ");

#endif

    }


#ifdef C_DATASTRUCTURES_ERRORSTESTSTRUCT_H
#else
    fprintf(stdout, "]");
#endif


}


/** This function will take an array and resize it using realloc function,
 * then it will return the new pointer of the realloc.
 *
 * Note: the realloc function could allocate the new space without changing the start address, but not always.
 *
 * @param arr the array pointer
 * @param elemSize the size of the array elements
 * @param newLength the new length of the array
 * @return it will return the new pointer of the array
 */

void *arrResize(void *arr, int elemSize, int newLength) {

    if (arr == NULL) {
#ifdef C_DATASTRUCTURES_ERRORSTESTSTRUCT_H
        ERROR_TEST->errorCode = NULL_POINTER;
        return NULL;
#else
        fprintf(stderr, NULL_POINTER_MESSAGE, "passed array", "arr resize function");
        exit(NULL_POINTER);
#endif
    } else if (elemSize <= 0) {
#ifdef C_DATASTRUCTURES_ERRORSTESTSTRUCT_H
        ERROR_TEST->errorCode = INVALID_ARG;
        return NULL;
#else
        fprintf(stderr, INVALID_ARG_MESSAGE, "element size", "arr resize function");
        exit(INVALID_ARG);
#endif
    } else if (newLength <= 0) {
#ifdef C_DATASTRUCTURES_ERRORSTESTSTRUCT_H
        ERROR_TEST->errorCode = INVALID_ARG;
        return NULL;
#else
        fprintf(stderr, INVALID_ARG_MESSAGE, "new Length", "arr resize function");
        exit(INVALID_ARG);
#endif
    }

    return realloc(arr, newLength * elemSize);

}


/** This function will take an array with a new length,
 * then it will allocate a new array with the provided new length,
 * and it will copy the values in the original array into the new array, and finally return the new array pointer.
 *
 * Note: this function will memory copy the original array.
 *
 * @param arr the array pointer
 * @param length the length of the array
 * @param elemSize the size of the array elements in bytes
 * @param newLength the new length of the new array
 * @return it will return a pointer to the new array
 */

void *arrResizeAndCpy(void *arr, int length, int elemSize, int newLength) {

    if (arr == NULL) {
#ifdef C_DATASTRUCTURES_ERRORSTESTSTRUCT_H
        ERROR_TEST->errorCode = NULL_POINTER;
        return NULL;
#else
        fprintf(stderr, NULL_POINTER_MESSAGE, "passed array", "array resize and copy function");
        exit(NULL_POINTER);
#endif
    } else if (length < 0) {
#ifdef C_DATASTRUCTURES_ERRORSTESTSTRUCT_H
        ERROR_TEST->errorCode = INVALID_ARG;
        return NULL;
#else
        fprintf(stderr, INVALID_ARG_MESSAGE, "array length", "array resize and copy function");
        exit(INVALID_ARG);
#endif
    } else if (elemSize <= 0) {
#ifdef C_DATASTRUCTURES_ERRORSTESTSTRUCT_H
        ERROR_TEST->errorCode = INVALID_ARG;
        return NULL;
#else
        fprintf(stderr, INVALID_ARG_MESSAGE, "element size", "array resize and copy function");
        exit(INVALID_ARG);
#endif
    } else if (newLength < length) {
#ifdef C_DATASTRUCTURES_ERRORSTESTSTRUCT_H
        ERROR_TEST->errorCode = INVALID_ARG;
        return NULL;
#else
        fprintf(stderr, INVALID_ARG_MESSAGE, "new length", "array resize and copy function");
        exit(INVALID_ARG);
#endif
    }

    void *newArr = (void *) malloc(elemSize * newLength);
    memcpy(newArr, arr, elemSize * length);

    return newArr;

}


/** This function will take an array with a new length,
 * then it will allocate a new array with the provided new length,
 * and it will copy the values between the provided two indices in the original array into the new array,
 * and finally return the new array pointer.
 *
 * Note: this function will memory copy the original array.
 *
 * @param arr the array pointer
 * @param length the length of the array
 * @param elemSize the array elements size in bytes
 * @param startIndex the copying start index
 * @param endIndex the copying end index
 * @param newLength the new array length
 * @return it will return the new array pointer
 */

void *arrResizeOfRangeAndCpy(void *arr, int length, int elemSize, int startIndex, int endIndex, int newLength) {

    if (arr == NULL) {
#ifdef C_DATASTRUCTURES_ERRORSTESTSTRUCT_H
        ERROR_TEST->errorCode = NULL_POINTER;
        return NULL;
#else
        fprintf(stderr, NULL_POINTER_MESSAGE, "passed array", "array resize of range and copy function");
        exit(NULL_POINTER);
#endif
    } else if (length < 0) {
#ifdef C_DATASTRUCTURES_ERRORSTESTSTRUCT_H
        ERROR_TEST->errorCode = INVALID_ARG;
        return NULL;
#else
        fprintf(stderr, INVALID_ARG_MESSAGE, "array length", "array resize of range and copy function");
        exit(INVALID_ARG);
#endif
    } else if (elemSize <= 0) {
#ifdef C_DATASTRUCTURES_ERRORSTESTSTRUCT_H
        ERROR_TEST->errorCode = INVALID_ARG;
        return NULL;
#else
        fprintf(stderr, INVALID_ARG_MESSAGE, "element size", "array resize of range and copy function");
        exit(INVALID_ARG);
#endif
    } else if (startIndex < 0 || startIndex > endIndex || endIndex >= length) {
#ifdef C_DATASTRUCTURES_ERRORSTESTSTRUCT_H
        ERROR_TEST->errorCode = INVALID_ARG;
        return NULL;
#else
        fprintf(stderr, INVALID_ARG_MESSAGE, "range of copy", "array resize of range and copy function");
        exit(INVALID_ARG);
#endif
    } else if (newLength < (endIndex - startIndex + 1)) {
#ifdef C_DATASTRUCTURES_ERRORSTESTSTRUCT_H
        ERROR_TEST->errorCode = INVALID_ARG;
        return NULL;
#else
        fprintf(stderr, INVALID_ARG_MESSAGE, "new length", "array resize of range and copy function");
        exit(INVALID_ARG);
#endif
    }

    char *oneBytePointer = (char *) arr;

    void *newArr = (void *) malloc(elemSize * newLength);
    memcpy(newArr, oneBytePointer + startIndex * elemSize, elemSize * (endIndex - startIndex + 1));

    return newArr;

}


/** This function will take an array with a new length,
 * then it will allocate a new array with the provided new length,
 * and it will copy the values in the original array into the new array using the passed copy function,
 * and finally return the new array pointer.
 *
 * Note: the first parameter of the copying function will be the space that the second parameter will be copied into it.
 *
 * @param arr the array pointer
 * @param length the array length
 * @param elemSize the size of the array elements in bytes
 * @param newLength the new array length
 * @param copyFun the copying function pointer, that will be called to copy the values
 * @return it will return the new array pointer
 */

void *
arrResizeAndCpyC(void *arr, int length, int elemSize, int newLength, void (*copyFun)(const void *, const void *)) {

    if (arr == NULL) {
#ifdef C_DATASTRUCTURES_ERRORSTESTSTRUCT_H
        ERROR_TEST->errorCode = NULL_POINTER;
        return NULL;
#else
        fprintf(stderr, NULL_POINTER_MESSAGE, "passed array", "custom array resize and copy function");
        exit(NULL_POINTER);
#endif
    } else if (copyFun == NULL) {
#ifdef C_DATASTRUCTURES_ERRORSTESTSTRUCT_H
        ERROR_TEST->errorCode = INVALID_ARG;
        return NULL;
#else
        fprintf(stderr, INVALID_ARG_MESSAGE, "copying function pointer", "custom array resize and copy function");
        exit(INVALID_ARG);
#endif
    } else if (length < 0) {
#ifdef C_DATASTRUCTURES_ERRORSTESTSTRUCT_H
        ERROR_TEST->errorCode = INVALID_ARG;
        return NULL;
#else
        fprintf(stderr, INVALID_ARG_MESSAGE, "array length", "custom array resize and copy function");
        exit(INVALID_ARG);
#endif
    } else if (elemSize <= 0) {
#ifdef C_DATASTRUCTURES_ERRORSTESTSTRUCT_H
        ERROR_TEST->errorCode = INVALID_ARG;
        return NULL;
#else
        fprintf(stderr, INVALID_ARG_MESSAGE, "element size", "custom array resize and copy function");
        exit(INVALID_ARG);
#endif
    } else if (newLength < length) {
#ifdef C_DATASTRUCTURES_ERRORSTESTSTRUCT_H
        ERROR_TEST->errorCode = INVALID_ARG;
        return NULL;
#else
        fprintf(stderr, INVALID_ARG_MESSAGE, "new length", "custom array resize and copy function");
        exit(INVALID_ARG);
#endif
    }

    char *oneBytePointer = (char *) arr;
    char *newArr = (void *) malloc(elemSize * newLength);

    for (int i = 0; i < length; i++)
        copyFun(newArr + i * elemSize, oneBytePointer + i * elemSize);

    return newArr;

}


/** This function will take an array with a new length,
 * then it will allocate a new array with the provided new length,
 * and it will copy the values between the provided two indices in the original array into the new array using the passed copy function,
 * and finally return the new array pointer.
 *
 * Note: the first parameter of the copying function will be the space that the second parameter will be copied into it.
 *
 * @param arr the array pointer
 * @param length the array length
 * @param elemSize the size of the array elements in bytes
 * @param startIndex the copying start index
 * @param endIndex the copying end index
 * @param newLength the length of the new array
 * @param copyFun the copying function pointer, that will be called to copy the values
 * @return it will return the new array pointer
 */

void *arrResizeOfRangeAndCpyC(void *arr, int length, int elemSize, int startIndex, int endIndex, int newLength,
                              void (*copyFun)(const void *, const void *)) {

    if (arr == NULL) {
#ifdef C_DATASTRUCTURES_ERRORSTESTSTRUCT_H
        ERROR_TEST->errorCode = NULL_POINTER;
        return NULL;
#else
        fprintf(stderr, NULL_POINTER_MESSAGE, "passed array", "custom array resize of range and copy function");
        exit(NULL_POINTER);
#endif
    } else if (copyFun == NULL) {
#ifdef C_DATASTRUCTURES_ERRORSTESTSTRUCT_H
        ERROR_TEST->errorCode = INVALID_ARG;
        return NULL;
#else
        fprintf(stderr, INVALID_ARG_MESSAGE, "copying function pointer",
                "custom array resize of range and copy function");
        exit(INVALID_ARG);
#endif
    } else if (length < 0) {
#ifdef C_DATASTRUCTURES_ERRORSTESTSTRUCT_H
        ERROR_TEST->errorCode = INVALID_ARG;
        return NULL;
#else
        fprintf(stderr, INVALID_ARG_MESSAGE, "array length", "custom array resize of range and copy function");
        exit(INVALID_ARG);
#endif
    } else if (elemSize <= 0) {
#ifdef C_DATASTRUCTURES_ERRORSTESTSTRUCT_H
        ERROR_TEST->errorCode = INVALID_ARG;
        return NULL;
#else
        fprintf(stderr, INVALID_ARG_MESSAGE, "element size", "custom array resize of range and copy function");
        exit(INVALID_ARG);
#endif
    } else if (startIndex < 0 || startIndex > endIndex || endIndex >= length) {
#ifdef C_DATASTRUCTURES_ERRORSTESTSTRUCT_H
        ERROR_TEST->errorCode = INVALID_ARG;
        return NULL;
#else
        fprintf(stderr, INVALID_ARG_MESSAGE, "range of copy", "custom array resize of range and copy function");
        exit(INVALID_ARG);
#endif
    } else if (newLength < (endIndex - startIndex + 1)) {
#ifdef C_DATASTRUCTURES_ERRORSTESTSTRUCT_H
        ERROR_TEST->errorCode = INVALID_ARG;
        return NULL;
#else
        fprintf(stderr, INVALID_ARG_MESSAGE, "new length", "custom array resize of range and copy function");
        exit(INVALID_ARG);
#endif
    }


    char *oneBytePointer = (char *) arr;
    char *newArr = (void *) malloc(elemSize * newLength);

    for (int i = startIndex; i <= endIndex; i++)
        copyFun(newArr + (i - startIndex) * elemSize, oneBytePointer + i * elemSize);

    return (void *) newArr;

}


/** This function will take an array,
 * then it will allocate a new array and copy the original one in the new array.
 *
 * Note: this function will memory copy the original array.
 *
 * @param arr the array pointer
 * @param length the length of the array
 * @param elemSize the size of the array elements in bytes
 * @return it will return the new copied array pointer
 */

void *arrCopy(void *arr, int length, int elemSize) {

    if (arr == NULL) {
#ifdef C_DATASTRUCTURES_ERRORSTESTSTRUCT_H
        ERROR_TEST->errorCode = NULL_POINTER;
        return NULL;
#else
        fprintf(stderr, NULL_POINTER_MESSAGE, "passed array", "array copy function");
        exit(NULL_POINTER);
#endif
    } else if (length < 0) {
#ifdef C_DATASTRUCTURES_ERRORSTESTSTRUCT_H
        ERROR_TEST->errorCode = INVALID_ARG;
        return NULL;
#else
        fprintf(stderr, INVALID_ARG_MESSAGE, "array length", "array copy function");
        exit(INVALID_ARG);
#endif
    } else if (elemSize <= 0) {
#ifdef C_DATASTRUCTURES_ERRORSTESTSTRUCT_H
        ERROR_TEST->errorCode = INVALID_ARG;
        return NULL;
#else
        fprintf(stderr, INVALID_ARG_MESSAGE, "element size", "array copy function");
        exit(INVALID_ARG);
#endif
    }


    void *newArr = (void *) malloc(elemSize * length);

    memcpy(newArr, arr, elemSize * length);

    return newArr;

}


/** This function will take an array,
 * then it will allocate a new array and copy the original array into the new one.
 *
 * Note: the passed copy function will take two parameters, the first one will be a pointer to the,
 * new space that should the second parameter be copied into it.
 *
 * @param arr the array pointer
 * @param length the length of the array
 * @param elemSize the size of the array elements in bytes
 * @param copyFun the copy function pointer, that will be called to copy the original array value into the new one
 * @return it will return the new copied array pointer
 */

void *arrCopyC(void *arr, int length, int elemSize, void (*copyFun)(const void *, const void *)) {

    if (arr == NULL) {
#ifdef C_DATASTRUCTURES_ERRORSTESTSTRUCT_H
        ERROR_TEST->errorCode = NULL_POINTER;
        return NULL;
#else
        fprintf(stderr, NULL_POINTER_MESSAGE, "passed array", "array custom copy function");
        exit(NULL_POINTER);
#endif
    } else if (copyFun == NULL) {
#ifdef C_DATASTRUCTURES_ERRORSTESTSTRUCT_H
        ERROR_TEST->errorCode = INVALID_ARG;
        return NULL;
#else
        fprintf(stderr, INVALID_ARG_MESSAGE, "copying function pointer", "array custom copy function");
        exit(INVALID_ARG);
#endif
    } else if (length < 0) {
#ifdef C_DATASTRUCTURES_ERRORSTESTSTRUCT_H
        ERROR_TEST->errorCode = INVALID_ARG;
        return NULL;
#else
        fprintf(stderr, INVALID_ARG_MESSAGE, "array length", "array custom copy function");
        exit(INVALID_ARG);
#endif
    } else if (elemSize <= 0) {
#ifdef C_DATASTRUCTURES_ERRORSTESTSTRUCT_H
        ERROR_TEST->errorCode = INVALID_ARG;
        return NULL;
#else
        fprintf(stderr, INVALID_ARG_MESSAGE, "element size", "array custom copy function");
        exit(INVALID_ARG);
#endif
    }

    char *oneBytePointer = (char *) arr;
    char *newArr = (void *) malloc(elemSize * length);

    for (int i = 0; i < length; i++)
        copyFun(newArr + i * elemSize, oneBytePointer + i * elemSize);

    return (void *) newArr;

}


/** This function will take an array and a range,
 * then it will copy the passed range from the original array into a new allocated array.
 *
 * @param arr the array length
 * @param length the length of the array
 * @param elemSize the size of the array elements
 * @param startIndex the range start index
 * @param endIndex the range end index
 * @return it will return the new copied array
 */

void *arrCopyOfRange(void *arr, int length, int elemSize, int startIndex, int endIndex) {

    if (arr == NULL) {
#ifdef C_DATASTRUCTURES_ERRORSTESTSTRUCT_H
        ERROR_TEST->errorCode = NULL_POINTER;
        return NULL;
#else
        fprintf(stderr, NULL_POINTER_MESSAGE, "passed array", "array copy of range function");
        exit(NULL_POINTER);
#endif
    } else if (length < 0) {
#ifdef C_DATASTRUCTURES_ERRORSTESTSTRUCT_H
        ERROR_TEST->errorCode = INVALID_ARG;
        return NULL;
#else
        fprintf(stderr, INVALID_ARG_MESSAGE, "array length", "array copy of range function");
        exit(INVALID_ARG);
#endif
    } else if (elemSize <= 0) {
#ifdef C_DATASTRUCTURES_ERRORSTESTSTRUCT_H
        ERROR_TEST->errorCode = INVALID_ARG;
        return NULL;
#else
        fprintf(stderr, INVALID_ARG_MESSAGE, "element size", "array copy of range function");
        exit(INVALID_ARG);
#endif
    } else if (startIndex < 0 || startIndex > endIndex || endIndex >= length) {
#ifdef C_DATASTRUCTURES_ERRORSTESTSTRUCT_H
        ERROR_TEST->errorCode = INVALID_ARG;
        return NULL;
#else
        fprintf(stderr, INVALID_ARG_MESSAGE, "range of copy", "array copy of range function");
        exit(INVALID_ARG);
#endif
    }


    char *oneBytePointer = (char *) arr;
    void *newArr = (void *) malloc(elemSize * (endIndex - startIndex + 1));

    memcpy(newArr, oneBytePointer + startIndex * elemSize, elemSize * (endIndex - startIndex + 1));

    return newArr;

}


/** This function will take an array and a range,
 * then it will copy the passed range from the original array into a new allocated array.
 *
 * Note: the passed copy function will take two parameters, the first one will be a pointer to the,
 * new space that should the second parameter be copied into it.
 *
 * @param arr the array length
 * @param length the length of the array
 * @param elemSize the size of the array elements
 * @param startIndex the range start index
 * @param endIndex the range end index
 * @param copyFun copyFun the copy function pointer, that will be called to copy the original array value into the new one
 * @return it will return the new copied array
 */

void *arrCopyOfRangeC(void *arr, int length, int elemSize, int startIndex, int endIndex,
                      void (*copyFun)(const void *, const void *)) {

    if (arr == NULL) {
#ifdef C_DATASTRUCTURES_ERRORSTESTSTRUCT_H
        ERROR_TEST->errorCode = NULL_POINTER;
        return NULL;
#else
        fprintf(stderr, NULL_POINTER_MESSAGE, "passed array", "array custom copy of range function");
        exit(NULL_POINTER);
#endif
    } else if (copyFun == NULL) {
#ifdef C_DATASTRUCTURES_ERRORSTESTSTRUCT_H
        ERROR_TEST->errorCode = INVALID_ARG;
        return NULL;
#else
        fprintf(stderr, INVALID_ARG_MESSAGE, "copying function pointer", "array custom copy of range function");
        exit(INVALID_ARG);
#endif
    } else if (length < 0) {
#ifdef C_DATASTRUCTURES_ERRORSTESTSTRUCT_H
        ERROR_TEST->errorCode = INVALID_ARG;
        return NULL;
#else
        fprintf(stderr, INVALID_ARG_MESSAGE, "array length", "array custom copy of range function");
        exit(INVALID_ARG);
#endif
    } else if (elemSize <= 0) {
#ifdef C_DATASTRUCTURES_ERRORSTESTSTRUCT_H
        ERROR_TEST->errorCode = INVALID_ARG;
        return NULL;
#else
        fprintf(stderr, INVALID_ARG_MESSAGE, "element size", "array custom copy of range function");
        exit(INVALID_ARG);
#endif
    } else if (startIndex < 0 || startIndex > endIndex || endIndex >= length) {
#ifdef C_DATASTRUCTURES_ERRORSTESTSTRUCT_H
        ERROR_TEST->errorCode = INVALID_ARG;
        return NULL;
#else
        fprintf(stderr, INVALID_ARG_MESSAGE, "range of copy", "array custom copy of range function");
        exit(INVALID_ARG);
#endif
    }


    char *oneBytePointer = (char *) arr;
    char *newArr = (void *) malloc(elemSize * (endIndex - startIndex + 1));

    for (int i = startIndex; i <= endIndex; i++)
        copyFun(newArr + (i - startIndex) * elemSize, oneBytePointer + i * elemSize);

    return (void *) newArr;

}


/** This function will take an array and a value,
 * then it will fill all the array with that value.
 *
 * Note: the function will memory copy the value into the array.
 *
 * @param arr the array pointer
 * @param fillValue the target value pointer
 * @param length the length of the array
 * @param elemSize the size of the array elements
 */

void fillArr(void *arr, void *fillValue, int length, int elemSize) {

    if (arr == NULL) {
#ifdef C_DATASTRUCTURES_ERRORSTESTSTRUCT_H
        ERROR_TEST->errorCode = NULL_POINTER;
        return;
#else
        fprintf(stderr, NULL_POINTER_MESSAGE, "passed array", "fill array function");
        exit(NULL_POINTER);
#endif
    } else if (fillValue == NULL) {
#ifdef C_DATASTRUCTURES_ERRORSTESTSTRUCT_H
        ERROR_TEST->errorCode = INVALID_ARG;
        return;
#else
        fprintf(stderr, INVALID_ARG_MESSAGE, "fill value pointer", "fill array function");
        exit(INVALID_ARG);
#endif
    } else if (length < 0) {
#ifdef C_DATASTRUCTURES_ERRORSTESTSTRUCT_H
        ERROR_TEST->errorCode = INVALID_ARG;
        return;
#else
        fprintf(stderr, INVALID_ARG_MESSAGE, "array length", "fill array function");
        exit(INVALID_ARG);
#endif
    } else if (elemSize <= 0) {
#ifdef C_DATASTRUCTURES_ERRORSTESTSTRUCT_H
        ERROR_TEST->errorCode = INVALID_ARG;
        return;
#else
        fprintf(stderr, INVALID_ARG_MESSAGE, "element size", "fill array function");
        exit(INVALID_ARG);
#endif
    }

    char *oneBytePointer = (char *) arr;
    for (int i = 0; i < length; i++)
        memcpy(oneBytePointer + i * elemSize, fillValue, elemSize);

}


/** This function will take an array and a value,
 * then it will fill all the array with that value.
 *
 * Note: the passed copy function will take two parameters, the first one will be a pointer to the,
 * new space that should the second parameter (the value) be copied into it.
 *
 * @param arr the array pointer
 * @param fillValue the target value pointer
 * @param length the length of the array
 * @param elemSize the size of the array elements in bytes
 * @param copyFun the copy function pointer, that will be called to copy the values in the array
 */

void fillArrC(void *arr, void *fillValue, int length, int elemSize, void (*copyFun)(const void *, const void *)) {

    if (arr == NULL) {
#ifdef C_DATASTRUCTURES_ERRORSTESTSTRUCT_H
        ERROR_TEST->errorCode = NULL_POINTER;
        return;
#else
        fprintf(stderr, NULL_POINTER_MESSAGE, "passed array", "fill array custom function");
        exit(NULL_POINTER);
#endif
    } else if (fillValue == NULL) {
#ifdef C_DATASTRUCTURES_ERRORSTESTSTRUCT_H
        ERROR_TEST->errorCode = INVALID_ARG;
        return;
#else
        fprintf(stderr, INVALID_ARG_MESSAGE, "fill value pointer", "fill array custom function");
        exit(INVALID_ARG);
#endif
    } else if (copyFun == NULL) {
#ifdef C_DATASTRUCTURES_ERRORSTESTSTRUCT_H
        ERROR_TEST->errorCode = INVALID_ARG;
        return;
#else
        fprintf(stderr, INVALID_ARG_MESSAGE, "copy function pointer", "fill array custom function");
        exit(INVALID_ARG);
#endif
    } else if (length < 0) {
#ifdef C_DATASTRUCTURES_ERRORSTESTSTRUCT_H
        ERROR_TEST->errorCode = INVALID_ARG;
        return;
#else
        fprintf(stderr, INVALID_ARG_MESSAGE, "array length", "fill array custom function");
        exit(INVALID_ARG);
#endif
    } else if (elemSize <= 0) {
#ifdef C_DATASTRUCTURES_ERRORSTESTSTRUCT_H
        ERROR_TEST->errorCode = INVALID_ARG;
        return;
#else
        fprintf(stderr, INVALID_ARG_MESSAGE, "element size", "fill array custom function");
        exit(INVALID_ARG);
#endif
    }

    char *oneBytePointer = (char *) arr;

    for (int i = 0; i < length; i++)
        copyFun(oneBytePointer + i * elemSize, fillValue);

}


/** This function will fill the passed array with the passed value,
 * in the provided range.
 *
 * @param arr the array pointer
 * @param fillValue the target value pointer
 * @param length the length of the array
 * @param elemSize the array elements size in bytes
 * @param startIndex the range start index
 * @param endIndex the range end index
 */

void fillArrOfRange(void *arr, void *fillValue, int length, int elemSize, int startIndex, int endIndex) {

    if (arr == NULL) {
#ifdef C_DATASTRUCTURES_ERRORSTESTSTRUCT_H
        ERROR_TEST->errorCode = NULL_POINTER;
        return;
#else
        fprintf(stderr, NULL_POINTER_MESSAGE, "passed array", "fill array of range function");
        exit(NULL_POINTER);
#endif
    } else if (fillValue == 0) {
#ifdef C_DATASTRUCTURES_ERRORSTESTSTRUCT_H
        ERROR_TEST->errorCode = INVALID_ARG;
        return;
#else
        fprintf(stderr, INVALID_ARG_MESSAGE, "fill value pointer", "fill array of range function");
        exit(INVALID_ARG);
#endif
    } else if (length < 0) {
#ifdef C_DATASTRUCTURES_ERRORSTESTSTRUCT_H
        ERROR_TEST->errorCode = INVALID_ARG;
        return;
#else
        fprintf(stderr, INVALID_ARG_MESSAGE, "array length", "fill array of range function");
        exit(INVALID_ARG);
#endif
    } else if (elemSize <= 0) {
#ifdef C_DATASTRUCTURES_ERRORSTESTSTRUCT_H
        ERROR_TEST->errorCode = INVALID_ARG;
        return;
#else
        fprintf(stderr, INVALID_ARG_MESSAGE, "element size", "fill array of range function");
        exit(INVALID_ARG);
#endif
    } else if (startIndex < 0 || startIndex > endIndex || endIndex >= length) {
#ifdef C_DATASTRUCTURES_ERRORSTESTSTRUCT_H
        ERROR_TEST->errorCode = INVALID_ARG;
        return;
#else
        fprintf(stderr, INVALID_ARG_MESSAGE, "range of copy", "fill array of range function");
        exit(INVALID_ARG);
#endif
    }

    char *oneBytePointer = (char *) arr;

    for (int i = startIndex; i <= endIndex; i++)
        memcpy(oneBytePointer + i * elemSize, fillValue, elemSize);

}


/** This function will fill the passed array with the passed value,
 * in the provided range.
 *
 * Note: the passed copy function will take two parameters, the first one will be a pointer to the,
 * new space that should the second parameter (the value) be copied into it.
 *
 * @param arr the array pointer
 * @param fillValue the target value pointer
 * @param length the length of the array
 * @param elemSize the size of the array elements in bytes
 * @param startIndex the range start index
 * @param endIndex the range end index
 * @param copyFun the copy function pointer, that will be called to copy the values in the array
 */

void fillArrOfRangeC(void *arr, void *fillValue, int length, int elemSize, int startIndex, int endIndex,
                     void (*copyFun)(const void *, const void *)) {

    if (arr == NULL) {
#ifdef C_DATASTRUCTURES_ERRORSTESTSTRUCT_H
        ERROR_TEST->errorCode = NULL_POINTER;
        return;
#else
        fprintf(stderr, NULL_POINTER_MESSAGE, "passed array", "fill array of range custom function");
        exit(NULL_POINTER);
#endif
    } else if (fillValue == NULL) {
#ifdef C_DATASTRUCTURES_ERRORSTESTSTRUCT_H
        ERROR_TEST->errorCode = INVALID_ARG;
        return;
#else
        fprintf(stderr, INVALID_ARG_MESSAGE, "fill value pointer", "fill array of range custom function");
        exit(INVALID_ARG);
#endif
    } else if (copyFun == NULL) {
#ifdef C_DATASTRUCTURES_ERRORSTESTSTRUCT_H
        ERROR_TEST->errorCode = INVALID_ARG;
        return;
#else
        fprintf(stderr, INVALID_ARG_MESSAGE, "copy function pointer", "fill array of range custom function");
        exit(INVALID_ARG);
#endif
    } else if (length < 0) {
#ifdef C_DATASTRUCTURES_ERRORSTESTSTRUCT_H
        ERROR_TEST->errorCode = INVALID_ARG;
        return;
#else
        fprintf(stderr, INVALID_ARG_MESSAGE, "array length", "fill array of range custom function");
        exit(INVALID_ARG);
#endif
    } else if (elemSize <= 0) {
#ifdef C_DATASTRUCTURES_ERRORSTESTSTRUCT_H
        ERROR_TEST->errorCode = INVALID_ARG;
        return;
#else
        fprintf(stderr, INVALID_ARG_MESSAGE, "element size", "fill array of range custom function");
        exit(INVALID_ARG);
#endif
    } else if (startIndex < 0 || startIndex > endIndex || endIndex >= length) {
#ifdef C_DATASTRUCTURES_ERRORSTESTSTRUCT_H
        ERROR_TEST->errorCode = INVALID_ARG;
        return;
#else
        fprintf(stderr, INVALID_ARG_MESSAGE, "range of copy", "fill array of range custom function");
        exit(INVALID_ARG);
#endif
    }

    char *oneBytePointer = (char *) arr;

    for (int i = startIndex; i <= endIndex; i++)
        copyFun(oneBytePointer + i * elemSize, fillValue);

}


/** This function will take two arrays,
 * then it will compare there values, and it will return one if the two arrays are equal,
 * other wise it will return zero.
 *
 * @param fArr the first array pointer
 * @param fLength the first array length
 * @param sArr the second array pointer
 * @param sLength the second array length
 * @param elemSize the size of the arrays elements in bytes
 * @param cmp the comparator function pointer, that will be called to compare the arrays values
 * @return it will return one if the two arrays are equal, other wise it will return zero
 */

int arrCompare(void *fArr, int fLength, void *sArr, int sLength, int elemSize, int (*cmp)(const void *, const void *)) {

    if (fArr == NULL) {
#ifdef C_DATASTRUCTURES_ERRORSTESTSTRUCT_H
        ERROR_TEST->errorCode = NULL_POINTER;
        return -1;
#else
        fprintf(stderr, NULL_POINTER_MESSAGE, "first passed array", "array compare function");
        exit(NULL_POINTER);
#endif
    } else if (sArr == NULL) {
#ifdef C_DATASTRUCTURES_ERRORSTESTSTRUCT_H
        ERROR_TEST->errorCode = NULL_POINTER;
        return -1;
#else
        fprintf(stderr, NULL_POINTER_MESSAGE, "second passed array", "array compare function");
        exit(NULL_POINTER);
#endif
    } else if (cmp == NULL) {
#ifdef C_DATASTRUCTURES_ERRORSTESTSTRUCT_H
        ERROR_TEST->errorCode = INVALID_ARG;
        return -1;
#else
        fprintf(stderr, INVALID_ARG_MESSAGE, "comparator function pointer", "array compare function");
        exit(INVALID_ARG);
#endif
    } else if (fLength < 0 || sLength < 0) {
#ifdef C_DATASTRUCTURES_ERRORSTESTSTRUCT_H
        ERROR_TEST->errorCode = INVALID_ARG;
        return -1;
#else
        fprintf(stderr, INVALID_ARG_MESSAGE, "arrays length", "array compare function");
        exit(INVALID_ARG);
#endif
    } else if (elemSize <= 0) {
#ifdef C_DATASTRUCTURES_ERRORSTESTSTRUCT_H
        ERROR_TEST->errorCode = INVALID_ARG;
        return -1;
#else
        fprintf(stderr, INVALID_ARG_MESSAGE, "element size", "array compare function");
        exit(INVALID_ARG);
#endif
    }

    if (fLength != sLength)
        return 0;

    char *fOneBytePointer = (char *) fArr;
    char *sOneBytePointer = (char *) sArr;

    for (int i = 0; i < fLength; i++) {

        if (cmp(fOneBytePointer + i * elemSize, sOneBytePointer + i * elemSize) != 0)
            return 0;

    }

    return 1;

}


/** This function will take two array,
 * then it will compare them between the passed two indices,
 * if there value between the two indices are equal the function will return one (1),
 * other wise it will return zero (0).
 *
 * @param fArr the first array pointer
 * @param fLength the first array length
 * @param sArr the second array pointer
 * @param sLength the second array length
 * @param elemSize the size of the arrays elements in bytes
 * @param startIndex the comparing start index
 * @param endIndex the comparing end index
 * @param cmp the comparator function pointer, that will be called to compare the arrays values
 * @return it will return one if the values between the indices are equal, other wise it will return zero
 */

int arrCompareOfRange(void *fArr, int fLength, void *sArr, int sLength, int elemSize, int startIndex, int endIndex,
                      int (*cmp)(const void *, const void *)) {

    if (fArr == NULL) {
#ifdef C_DATASTRUCTURES_ERRORSTESTSTRUCT_H
        ERROR_TEST->errorCode = NULL_POINTER;
        return -1;
#else
        fprintf(stderr, NULL_POINTER_MESSAGE, "first passed array", "array compare of range function");
        exit(NULL_POINTER);
#endif
    } else if (sArr == NULL) {
#ifdef C_DATASTRUCTURES_ERRORSTESTSTRUCT_H
        ERROR_TEST->errorCode = NULL_POINTER;
        return -1;
#else
        fprintf(stderr, NULL_POINTER_MESSAGE, "second passed array", "array compare of range function");
        exit(NULL_POINTER);
#endif
    } else if (cmp == NULL) {
#ifdef C_DATASTRUCTURES_ERRORSTESTSTRUCT_H
        ERROR_TEST->errorCode = INVALID_ARG;
        return -1;
#else
        fprintf(stderr, INVALID_ARG_MESSAGE, "comparator function pointer", "array compare of range function");
        exit(INVALID_ARG);
#endif
    } else if (fLength < 0 || sLength < 0) {
#ifdef C_DATASTRUCTURES_ERRORSTESTSTRUCT_H
        ERROR_TEST->errorCode = INVALID_ARG;
        return -1;
#else
        fprintf(stderr, INVALID_ARG_MESSAGE, "arrays length", "array compare of range function");
        exit(INVALID_ARG);
#endif
    } else if (elemSize <= 0) {
#ifdef C_DATASTRUCTURES_ERRORSTESTSTRUCT_H
        ERROR_TEST->errorCode = INVALID_ARG;
        return -1;
#else
        fprintf(stderr, INVALID_ARG_MESSAGE, "element size", "array compare of range function");
        exit(INVALID_ARG);
#endif
    } else if (startIndex < 0 || startIndex > endIndex || endIndex >= fLength || endIndex >= sLength) {
#ifdef C_DATASTRUCTURES_ERRORSTESTSTRUCT_H
        ERROR_TEST->errorCode = INVALID_ARG;
        return -1;
#else
        fprintf(stderr, INVALID_ARG_MESSAGE, "range of compare", "array compare of range function");
        exit(INVALID_ARG);
#endif
    }


    char *fOneBytePointer = (char *) fArr;
    char *sOneBytePointer = (char *) sArr;

    for (int i = startIndex; i <= endIndex; i++) {

        if (cmp(fOneBytePointer + i * elemSize, sOneBytePointer + i * elemSize) != 0)
            return 0;

    }

    return 1;

}


/** This function will take two arrays,
 * then it will search for the first element that mismatch between the two arrays,
 * if the mismatch found the function will return the mismatch index,
 * other wise it will return minus one (-1).
 *
 * Note: if the two array hasn't the same length the function will check for smallest length.
 *
 * @param fArr the first array pointer
 * @param fLength the first array length
 * @param sArr the second array pointer
 * @param sLength the second array length
 * @param elemSize the size of the arrays elements in bytes
 * @param cmp the comparator function pointer, that will be called to compare the arrays values
 * @return it will return the index of the first mismatch if found, other wise it will return -1
 */

int
arrMismatch(void *fArr, int fLength, void *sArr, int sLength, int elemSize, int (*cmp)(const void *, const void *)) {

    if (fArr == NULL) {
#ifdef C_DATASTRUCTURES_ERRORSTESTSTRUCT_H
        ERROR_TEST->errorCode = NULL_POINTER;
        return -1;
#else
        fprintf(stderr, NULL_POINTER_MESSAGE, "first passed array", "array mismatch function");
        exit(NULL_POINTER);
#endif
    } else if (sArr == NULL) {
#ifdef C_DATASTRUCTURES_ERRORSTESTSTRUCT_H
        ERROR_TEST->errorCode = NULL_POINTER;
        return -1;
#else
        fprintf(stderr, NULL_POINTER_MESSAGE, "second passed array", "array mismatch function");
        exit(NULL_POINTER);
#endif
    } else if (cmp == NULL) {
#ifdef C_DATASTRUCTURES_ERRORSTESTSTRUCT_H
        ERROR_TEST->errorCode = INVALID_ARG;
        return -1;
#else
        fprintf(stderr, INVALID_ARG_MESSAGE, "comparator function pointer", "array mismatch function");
        exit(INVALID_ARG);
#endif
    } else if (fLength < 0 || sLength < 0) {
#ifdef C_DATASTRUCTURES_ERRORSTESTSTRUCT_H
        ERROR_TEST->errorCode = INVALID_ARG;
        return -1;
#else
        fprintf(stderr, INVALID_ARG_MESSAGE, "arrays length", "array mismatch function");
        exit(INVALID_ARG);
#endif
    } else if (elemSize <= 0) {
#ifdef C_DATASTRUCTURES_ERRORSTESTSTRUCT_H
        ERROR_TEST->errorCode = INVALID_ARG;
        return -1;
#else
        fprintf(stderr, INVALID_ARG_MESSAGE, "element size", "array mismatch function");
        exit(INVALID_ARG);
#endif
    }


    char *fOneBytePointer = (char *) fArr;
    char *sOneBytePointer = (char *) sArr;

    for (int i = 0; i < (fLength < sLength ? fLength : sLength); i++) {

        if (cmp(fOneBytePointer + i * elemSize, sOneBytePointer + i * elemSize) != 0)
            return i;

    }

    return -1;

}


/** This function will take two arrays,
 * then it will search for the first element that mismatch between the two arrays between the provided range,
 * if the mismatch found the function will return the mismatch index,
 * other wise it will return minus one (-1).
 *
 * @param fArr the first array pointer
 * @param fLength the first array length
 * @param sArr the second array pointer
 * @param sLength the second array length
 * @param elemSize the size of the arrays elements in bytes
 * @param startIndex the checking start index
 * @param endIndex the checking end index
 * @param cmp the comparator function pointer, that will be called to compare the arrays values
 * @return it will return the index of the first mismatch if found, other wise it will return -1
 */

int arrMismatchOfRange(void *fArr, int fLength, void *sArr, int sLength, int elemSize, int startIndex, int endIndex,
                       int (*cmp)(const void *, const void *)) {

    if (fArr == NULL) {
#ifdef C_DATASTRUCTURES_ERRORSTESTSTRUCT_H
        ERROR_TEST->errorCode = NULL_POINTER;
        return -1;
#else
        fprintf(stderr, NULL_POINTER_MESSAGE, "first passed array", "array mismatch of range function");
        exit(NULL_POINTER);
#endif
    } else if (sArr == NULL) {
#ifdef C_DATASTRUCTURES_ERRORSTESTSTRUCT_H
        ERROR_TEST->errorCode = NULL_POINTER;
        return -1;
#else
        fprintf(stderr, NULL_POINTER_MESSAGE, "second passed array", "array mismatch of range function");
        exit(NULL_POINTER);
#endif
    } else if (cmp == NULL) {
#ifdef C_DATASTRUCTURES_ERRORSTESTSTRUCT_H
        ERROR_TEST->errorCode = INVALID_ARG;
        return -1;
#else
        fprintf(stderr, INVALID_ARG_MESSAGE, "comparator function pointer", "array mismatch of range function");
        exit(INVALID_ARG);
#endif
    } else if (fLength < 0 || sLength < 0) {
#ifdef C_DATASTRUCTURES_ERRORSTESTSTRUCT_H
        ERROR_TEST->errorCode = INVALID_ARG;
        return -1;
#else
        fprintf(stderr, INVALID_ARG_MESSAGE, "arrays length", "array mismatch of range function");
        exit(INVALID_ARG);
#endif
    } else if (elemSize <= 0) {
#ifdef C_DATASTRUCTURES_ERRORSTESTSTRUCT_H
        ERROR_TEST->errorCode = INVALID_ARG;
        return -1;
#else
        fprintf(stderr, INVALID_ARG_MESSAGE, "element size", "array mismatch of range function");
        exit(INVALID_ARG);
#endif
    } else if (startIndex < 0 || startIndex > endIndex || endIndex >= fLength || endIndex >= sLength) {
#ifdef C_DATASTRUCTURES_ERRORSTESTSTRUCT_H
        ERROR_TEST->errorCode = INVALID_ARG;
        return -1;
#else
        fprintf(stderr, INVALID_ARG_MESSAGE, "range of compare", "array mismatch of range function");
        exit(INVALID_ARG);
#endif
    }

    char *fOneBytePointer = (char *) fArr;
    char *sOneBytePointer = (char *) sArr;

    for (int i = startIndex; i <= endIndex; i++) {

        if (cmp(fOneBytePointer + i * elemSize, sOneBytePointer + i * elemSize) != 0)
            return i;

    }

    return -1;

}


/** This function will take two array,
 * then it will check if the two arrays has the same values or not,
 * and if they are the function will return one (1), other wise it will return zero (0).
 *
 * Note: this function will sort the arrays.
 *
 * @param fArr the first array pointer
 * @param fLength the first array length
 * @param sArr the second array pointer
 * @param sLength the second array length
 * @param elemSize the size of the arrays elements in bytes
 * @param cmp the comparator function pointer, that will be called to compare the arrays values.
 * @return it will return 1 if the two array has the same values, other wise it will return 0
 */

int
arrAnagramsS(void *fArr, int fLength, void *sArr, int sLength, int elemSize, int (*cmp)(const void *, const void *)) {

    if (fArr == NULL) {
#ifdef C_DATASTRUCTURES_ERRORSTESTSTRUCT_H
        ERROR_TEST->errorCode = NULL_POINTER;
        return -1;
#else
        fprintf(stderr, NULL_POINTER_MESSAGE, "first passed array", "arrAnagramsS function");
        exit(NULL_POINTER);
#endif
    } else if (sArr == NULL) {
#ifdef C_DATASTRUCTURES_ERRORSTESTSTRUCT_H
        ERROR_TEST->errorCode = NULL_POINTER;
        return -1;
#else
        fprintf(stderr, NULL_POINTER_MESSAGE, "second passed array", "arrAnagramsS function");
        exit(NULL_POINTER);
#endif
    } else if (cmp == NULL) {
#ifdef C_DATASTRUCTURES_ERRORSTESTSTRUCT_H
        ERROR_TEST->errorCode = INVALID_ARG;
        return -1;
#else
        fprintf(stderr, INVALID_ARG_MESSAGE, "comparator function pointer", "arrAnagramsS function");
        exit(INVALID_ARG);
#endif
    } else if (fLength < 0 || sLength < 0) {
#ifdef C_DATASTRUCTURES_ERRORSTESTSTRUCT_H
        ERROR_TEST->errorCode = INVALID_ARG;
        return -1;
#else
        fprintf(stderr, INVALID_ARG_MESSAGE, "arrays length", "arrAnagramsS function");
        exit(INVALID_ARG);
#endif
    } else if (elemSize <= 0) {
#ifdef C_DATASTRUCTURES_ERRORSTESTSTRUCT_H
        ERROR_TEST->errorCode = INVALID_ARG;
        return -1;
#else
        fprintf(stderr, INVALID_ARG_MESSAGE, "element size", "arrAnagramsS function");
        exit(INVALID_ARG);
#endif
    }

    if (fLength != sLength)
        return 0;

    qsort(fArr, fLength, elemSize, cmp);
    qsort(sArr, sLength, elemSize, cmp);

    char *fOneBytePointer = (char *) fArr;
    char *sOneBytePointer = (char *) sArr;

    for (int i = 0; i < fLength; i++) {
        if (cmp(fOneBytePointer + i * elemSize, sOneBytePointer + i * elemSize) != 0)
            return 0;

    }

    return 1;

}


/** This function will take two array,
 * then it will check if the two arrays has the same values or not,
 * and if they are the function will return one (1), other wise it will return zero (0).
 *
 * Note: this function will use hash map data structure, so it need the hash function.
 *
 * Time Complexity: O (n ^ 2).
 *
 * Space Complexity: O (n).
 *
 * @param fArr the first array pointer
 * @param fLength the length of the first array
 * @param sArr the second array pointer
 * @param sLength the length of the second array
 * @param elemSize the size of the arrays elements in bytes
 * @param cmp the comparator function pointer, that will be called to compare the arrays values.
 * @param hashFun the hashing function that will return a unique integer representing the hash map key
 * @return it will return 1 if the two array has the same values, other wise it will return 0
 */

int arrAnagramsH(void *fArr, int fLength, void *sArr, int sLength, int elemSize, int (*cmp)(const void *, const void *),
                 int (*hashFun)(const void *)) {

    if (fArr == NULL) {
#ifdef C_DATASTRUCTURES_ERRORSTESTSTRUCT_H
        ERROR_TEST->errorCode = NULL_POINTER;
        return -1;
#else
        fprintf(stderr, NULL_POINTER_MESSAGE, "first passed array", "arrAnagramsH function");
        exit(NULL_POINTER);
#endif
    } else if (sArr == NULL) {
#ifdef C_DATASTRUCTURES_ERRORSTESTSTRUCT_H
        ERROR_TEST->errorCode = NULL_POINTER;
        return -1;
#else
        fprintf(stderr, NULL_POINTER_MESSAGE, "second passed array", "arrAnagramsH function");
        exit(NULL_POINTER);
#endif
    } else if (cmp == NULL) {
#ifdef C_DATASTRUCTURES_ERRORSTESTSTRUCT_H
        ERROR_TEST->errorCode = INVALID_ARG;
        return -1;
#else
        fprintf(stderr, INVALID_ARG_MESSAGE, "comparator function pointer", "arrAnagramsH function");
        exit(INVALID_ARG);
#endif
    } else if (hashFun == NULL) {
#ifdef C_DATASTRUCTURES_ERRORSTESTSTRUCT_H
        ERROR_TEST->errorCode = INVALID_ARG;
        return -1;
#else
        fprintf(stderr, INVALID_ARG_MESSAGE, "hash function pointer", "arrAnagramsH function");
        exit(INVALID_ARG);
#endif
    } else if (fLength < 0 || sLength < 0) {
#ifdef C_DATASTRUCTURES_ERRORSTESTSTRUCT_H
        ERROR_TEST->errorCode = INVALID_ARG;
        return -1;
#else
        fprintf(stderr, INVALID_ARG_MESSAGE, "arrays length", "arrAnagramsH function");
        exit(INVALID_ARG);
#endif
    } else if (elemSize <= 0) {
#ifdef C_DATASTRUCTURES_ERRORSTESTSTRUCT_H
        ERROR_TEST->errorCode = INVALID_ARG;
        return -1;
#else
        fprintf(stderr, INVALID_ARG_MESSAGE, "element size", "arrAnagramsH function");
        exit(INVALID_ARG);
#endif
    }


    if (fLength != sLength)
        return 0;


    char *fOneBytePointer = (char *) fArr;
    char *sOneBytePointer = (char *) sArr;

    HashMap *valuesCounterMap = hashMapInitialization(nullFreeFunArrAlg, intFreeFunArrAlg, cmp, hashFun);
    unsigned int oneValue = 1;

    for (int i = 0; i < fLength; i++) {
        char *currentItem = fOneBytePointer + i * elemSize;
        int *currentItemCount = (int *) hashMapGet(valuesCounterMap, currentItem);

        if (currentItemCount == NULL)
            hashMapInsert(valuesCounterMap, currentItem, generateIntPointerArrAlg(&oneValue));
        else
            *currentItemCount += 1;

    }

    for (int i = 0; i < sLength; i++) {
        char *currentItem = sOneBytePointer + i * elemSize;
        int *currentItemCount = (int *) hashMapGet(valuesCounterMap, currentItem);

        if (currentItemCount == NULL || *currentItemCount <= 0) {
            destroyHashMap(valuesCounterMap);
            return 0;
        } else
            *currentItemCount -= 1;

    }

    destroyHashMap(valuesCounterMap);

    return 1;

}


/** This function will take an array,
 * then it will remove all the duplicates values from the array.
 *
 * Note: the function will memory copy the value index i + 1 to remove the value in index i,
 * so if the value need to be freed first then pass the free function, other wise pass NULL function pointer.
 *
 * Note: this function will use hash set to detect the duplicates.
 *
 * Note: the function needs a hash value function because the function uses hash set data structure,
 * to detect the duplicates with less complexity.
 *
 * @param arr the array pointer
 * @param length the length of the array
 * @param elemSize the array elements size in bytes
 * @param cmp the comparator function pointer, that will be called to compare two value
 * @param hashFun the hashing function that will return a unique integer representing the hash map key
 * @param freeFun the free function pointer, that will be called to free the value before removing it from the array
 * @return it will return the new length of the array after removing the duplicates
 */

int arrRemoveDuplicatesH(void *arr, int length, int elemSize,
                         int (*cmp)(const void *, const void *),
                         int (*hashFun)(const void *),
                         void (*freeFun)(void *)) {

    if (arr == NULL) {
#ifdef C_DATASTRUCTURES_ERRORSTESTSTRUCT_H
        ERROR_TEST->errorCode = NULL_POINTER;
        return -1;
#else
        fprintf(stderr, NULL_POINTER_MESSAGE, "passed array", "array remove duplicates function");
        exit(NULL_POINTER);
#endif
    } else if (cmp == NULL) {
#ifdef C_DATASTRUCTURES_ERRORSTESTSTRUCT_H
        ERROR_TEST->errorCode = INVALID_ARG;
        return -1;
#else
        fprintf(stderr, INVALID_ARG_MESSAGE, "comparator function pointer", "array remove duplicates function");
        exit(INVALID_ARG);
#endif
    } else if (length < 0) {
#ifdef C_DATASTRUCTURES_ERRORSTESTSTRUCT_H
        ERROR_TEST->errorCode = INVALID_ARG;
        return -1;
#else
        fprintf(stderr, INVALID_ARG_MESSAGE, "array length", "array remove duplicates function");
        exit(INVALID_ARG);
#endif
    } else if (elemSize <= 0) {
#ifdef C_DATASTRUCTURES_ERRORSTESTSTRUCT_H
        ERROR_TEST->errorCode = INVALID_ARG;
        return -1;
#else
        fprintf(stderr, INVALID_ARG_MESSAGE, "element size", "array remove duplicates function");
        exit(INVALID_ARG);
#endif
    } else if (hashFun == NULL) {
#ifdef C_DATASTRUCTURES_ERRORSTESTSTRUCT_H
        ERROR_TEST->errorCode = INVALID_ARG;
        return -1;
#else
        fprintf(stderr, INVALID_ARG_MESSAGE, "hash function pointer", "array remove duplicates function");
        exit(INVALID_ARG);
#endif
    }

    char *oneBytePointer = (char *) arr;

    HashSet *valuesSet = hashSetInitialization(nullFreeFunArrAlg, cmp, hashFun);
    int index = 0;

    while (index < length) {
        char *currentValue = oneBytePointer + index * elemSize;
        int valueExistFlag = hashSetContains(valuesSet, currentValue);
        if (valueExistFlag) {

            length--;

            if (freeFun != NULL)
                freeFun(currentValue);

            for (int i = index; i < length; i++) // this loop is to shift the values to delete the duplicated value
                memcpy(oneBytePointer + i * elemSize, oneBytePointer + (i + 1) * elemSize, elemSize);

        } else {
            hashSetInsert(valuesSet, currentValue);
            index++;
        }

    }

    destroyHashSet(valuesSet);

    return length;

}


/** This function will take an array,
 * then it will remove all the duplicates values from the array.
 *
 * Note: the function will memory copy the value index i + 1 to remove the value in index i,
 * so if the value need to be freed first then pass the free function, other wise pass NULL function pointer.
 *
 * Note: this function will use an array to detect the duplicates.
 *
 * @param arr the array pointer
 * @param length the length of the array
 * @param elemSize the array elements size in bytes
 * @param cmp the comparator function pointer, that will be called to compare two value
 * @param freeFun the free function pointer, that will be called to free the value before removing it from the array
 * @return it will return the new length of the array after removing the duplicates
 */

int arrRemoveDuplicatesA(void *arr, int length, int elemSize,
                         int (*cmp)(const void *, const void *),
                         void (*freeFun)(void *)) {

    if (arr == NULL) {
#ifdef C_DATASTRUCTURES_ERRORSTESTSTRUCT_H
        ERROR_TEST->errorCode = NULL_POINTER;
        return -1;
#else
        fprintf(stderr, NULL_POINTER_MESSAGE, "passed array", "array remove duplicates function");
        exit(NULL_POINTER);
#endif
    } else if (cmp == NULL) {
#ifdef C_DATASTRUCTURES_ERRORSTESTSTRUCT_H
        ERROR_TEST->errorCode = INVALID_ARG;
        return -1;
#else
        fprintf(stderr, INVALID_ARG_MESSAGE, "comparator function pointer", "array remove duplicates function");
        exit(INVALID_ARG);
#endif
    } else if (length < 0) {
#ifdef C_DATASTRUCTURES_ERRORSTESTSTRUCT_H
        ERROR_TEST->errorCode = INVALID_ARG;
        return -1;
#else
        fprintf(stderr, INVALID_ARG_MESSAGE, "array length", "array remove duplicates function");
        exit(INVALID_ARG);
#endif
    } else if (elemSize <= 0) {
#ifdef C_DATASTRUCTURES_ERRORSTESTSTRUCT_H
        ERROR_TEST->errorCode = INVALID_ARG;
        return -1;
#else
        fprintf(stderr, INVALID_ARG_MESSAGE, "element size", "array remove duplicates function");
        exit(INVALID_ARG);
#endif
    }

    char *oneBytePointer = (char *) arr;

    Vector *valuesVector = vectorInitialization(length / 2 == 0 ? 1 : length / 2, nullFreeFunArrAlg, cmp);
    int index = 0;

    while (index < length) {
        char *currentValue = oneBytePointer + index * elemSize;
        if (vectorContains(valuesVector, currentValue)) {

            length--;

            if (freeFun != NULL)
                freeFun(currentValue);

            for (int i = index; i < length; i++) // this loop is to shift the values to delete the duplicated value
                memcpy(oneBytePointer + i * elemSize, oneBytePointer + (i + 1) * elemSize, elemSize);

        } else {
            vectorAdd(valuesVector, currentValue);
            index++;
        }

    }

    destroyVector(valuesVector);

    return length;
}


/** This function will take an array and a values array,
 * then it will remove any value in the values array from the first array,
 * and finally the function will return the new length of the array.
 *
 * Note: the function will memory copy the value index i + 1 to remove the value in index i,
 * so if the value need to be freed first then pass the free function, other wise pass NULL function pointer.
 *
 * @param arr the array pointer
 * @param arrLength the length of the array
 * @param values the values array
 * @param valuesArrLength the length of the values array
 * @param elemSize the size of the values elements
 * @param cmp the comparator function pointer, that will be called to compare values
 * @param freeFun the free function pointer, that will be called to free the value before removing them
 * @return it will return the new length of the array after deleting the values
 */

int arrRemoveValues(void *arr, int arrLength, void *values, int valuesArrLength, int elemSize,
                    int (*cmp)(const void *, const void *),
                    void (*freeFun)(void *)) {

    if (arr == NULL) {
#ifdef C_DATASTRUCTURES_ERRORSTESTSTRUCT_H
        ERROR_TEST->errorCode = NULL_POINTER;
        return -1;
#else
        fprintf(stderr, NULL_POINTER_MESSAGE, "passed array", "array remove values function");
        exit(NULL_POINTER);
#endif
    } else if (values == NULL) {
#ifdef C_DATASTRUCTURES_ERRORSTESTSTRUCT_H
        ERROR_TEST->errorCode = INVALID_ARG;
        return -1;
#else
        fprintf(stderr, NULL_POINTER_MESSAGE, "passed values array", "array remove values function");
        exit(NULL_POINTER);
#endif
    } else if (cmp == NULL) {
#ifdef C_DATASTRUCTURES_ERRORSTESTSTRUCT_H
        ERROR_TEST->errorCode = INVALID_ARG;
        return -1;
#else
        fprintf(stderr, INVALID_ARG_MESSAGE, "comparator function pointer", "array remove values function");
        exit(INVALID_ARG);
#endif
    } else if (arrLength < 0) {
#ifdef C_DATASTRUCTURES_ERRORSTESTSTRUCT_H
        ERROR_TEST->errorCode = INVALID_ARG;
        return -1;
#else
        fprintf(stderr, INVALID_ARG_MESSAGE, "array length", "array remove values function");
        exit(INVALID_ARG);
#endif
    } else if (valuesArrLength < 0) {
#ifdef C_DATASTRUCTURES_ERRORSTESTSTRUCT_H
        ERROR_TEST->errorCode = INVALID_ARG;
        return -1;
#else
        fprintf(stderr, INVALID_ARG_MESSAGE, "values array length", "array remove values function");
        exit(INVALID_ARG);
#endif
    } else if (elemSize <= 0) {
#ifdef C_DATASTRUCTURES_ERRORSTESTSTRUCT_H
        ERROR_TEST->errorCode = INVALID_ARG;
        return -1;
#else
        fprintf(stderr, INVALID_ARG_MESSAGE, "element size", "array remove values function");
        exit(INVALID_ARG);
#endif
    }


    char *oneBytePointer = (char *) arr;

    for (int i = 0; i < arrLength; i++) {

        if (arrContains(values, oneBytePointer + i * elemSize, valuesArrLength, elemSize, cmp)) {

            arrRemoveAtIndex(oneBytePointer, i, arrLength, elemSize, freeFun);
            arrLength--;
            i--;

        }

    }

    return arrLength;

}


/** This function will take an array and a values array,
 * then it will count the number of values in the first array that exist in the values array.
 *
 * @param arr the array pointer
 * @param arrLength the length of the array
 * @param values the values array
 * @param valuesArrLength the length of the values array
 * @param elemSize the size of the values elements
 * @param cmp the comparator function pointer, that will be called to compare values
 * @return it will return the number of values in the first array that exist in the values array
 */

int arrCountValues(void *arr, int arrLength, void *values, int valuesArrLength, int elemSize,
                   int (*cmp)(const void *, const void *)) {

    if (arr == NULL) {
#ifdef C_DATASTRUCTURES_ERRORSTESTSTRUCT_H
        ERROR_TEST->errorCode = NULL_POINTER;
        return -1;
#else
        fprintf(stderr, NULL_POINTER_MESSAGE, "passed array", "array count values function");
        exit(NULL_POINTER);
#endif
    } else if (values == NULL) {
#ifdef C_DATASTRUCTURES_ERRORSTESTSTRUCT_H
        ERROR_TEST->errorCode = INVALID_ARG;
        return -1;
#else
        fprintf(stderr, NULL_POINTER_MESSAGE, "passed values array", "array count values function");
        exit(NULL_POINTER);
#endif
    } else if (cmp == NULL) {
#ifdef C_DATASTRUCTURES_ERRORSTESTSTRUCT_H
        ERROR_TEST->errorCode = INVALID_ARG;
        return -1;
#else
        fprintf(stderr, INVALID_ARG_MESSAGE, "comparator function pointer", "array count values function");
        exit(INVALID_ARG);
#endif
    } else if (arrLength < 0) {
#ifdef C_DATASTRUCTURES_ERRORSTESTSTRUCT_H
        ERROR_TEST->errorCode = INVALID_ARG;
        return -1;
#else
        fprintf(stderr, INVALID_ARG_MESSAGE, "array length", "array count values function");
        exit(INVALID_ARG);
#endif
    } else if (valuesArrLength < 0) {
#ifdef C_DATASTRUCTURES_ERRORSTESTSTRUCT_H
        ERROR_TEST->errorCode = INVALID_ARG;
        return -1;
#else
        fprintf(stderr, INVALID_ARG_MESSAGE, "values array length", "array count values function");
        exit(INVALID_ARG);
#endif
    } else if (elemSize <= 0) {
#ifdef C_DATASTRUCTURES_ERRORSTESTSTRUCT_H
        ERROR_TEST->errorCode = INVALID_ARG;
        return -1;
#else
        fprintf(stderr, INVALID_ARG_MESSAGE, "element size", "array count values function");
        exit(INVALID_ARG);
#endif
    }

    char *oneBytePointer = (char *) arr;

    int counter = 0;
    for (int i = 0; i < arrLength; i++) {

        if (arrContains(values, oneBytePointer + i * elemSize, valuesArrLength, elemSize, cmp))
            counter++;

    }

    return counter;

}


/** This function will check if the passed values array,
 * is a sub array from the original array, and if it was the function will return one (1),
 * other wise it will return zero (0).
 *
 * @param arr the array pointer
 * @param arrLength the length of the array
 * @param values the values array
 * @param valuesArrLength the length of the values array
 * @param elemSize the size of the values elements
 * @param cmp the comparator function pointer, that will be called to compare values
 * @return it will return 1 if the values array is a sub array from the original array, other wise it will return 0
 */

int isSubArr(void *arr, int arrLength, void *values, int valuesArrLength, int elemSize,
             int (*cmp)(const void *, const void *)) {

    if (arr == NULL) {
#ifdef C_DATASTRUCTURES_ERRORSTESTSTRUCT_H
        ERROR_TEST->errorCode = NULL_POINTER;
        return -1;
#else
        fprintf(stderr, NULL_POINTER_MESSAGE, "passed array", "is sub array function");
        exit(NULL_POINTER);
#endif
    } else if (values == NULL) {
#ifdef C_DATASTRUCTURES_ERRORSTESTSTRUCT_H
        ERROR_TEST->errorCode = INVALID_ARG;
        return -1;
#else
        fprintf(stderr, NULL_POINTER_MESSAGE, "passed values array", "is sub array function");
        exit(NULL_POINTER);
#endif
    } else if (cmp == NULL) {
#ifdef C_DATASTRUCTURES_ERRORSTESTSTRUCT_H
        ERROR_TEST->errorCode = INVALID_ARG;
        return -1;
#else
        fprintf(stderr, INVALID_ARG_MESSAGE, "comparator function pointer", "is sub array function");
        exit(INVALID_ARG);
#endif
    } else if (arrLength < 0) {
#ifdef C_DATASTRUCTURES_ERRORSTESTSTRUCT_H
        ERROR_TEST->errorCode = INVALID_ARG;
        return -1;
#else
        fprintf(stderr, INVALID_ARG_MESSAGE, "array length", "is sub array function");
        exit(INVALID_ARG);
#endif
    } else if (valuesArrLength < 0) {
#ifdef C_DATASTRUCTURES_ERRORSTESTSTRUCT_H
        ERROR_TEST->errorCode = INVALID_ARG;
        return -1;
#else
        fprintf(stderr, INVALID_ARG_MESSAGE, "values array length", "is sub array function");
        exit(INVALID_ARG);
#endif
    } else if (elemSize <= 0) {
#ifdef C_DATASTRUCTURES_ERRORSTESTSTRUCT_H
        ERROR_TEST->errorCode = INVALID_ARG;
        return -1;
#else
        fprintf(stderr, INVALID_ARG_MESSAGE, "element size", "is sub array function");
        exit(INVALID_ARG);
#endif
    }

    if (valuesArrLength == 0)
        return 1;

    char *oneBytePointer = (char *) arr;
    char *valueArrCharPointer = (char *) values;

    for (int i = 0; i <= arrLength - valuesArrLength; i++) {

        if (cmp(oneBytePointer + i * elemSize, valueArrCharPointer) == 0) {

            for (int j = 0; j < valuesArrLength; j++) {

                if (j == valuesArrLength - 1 &&
                    cmp(oneBytePointer + (i + j) * elemSize, valueArrCharPointer + j * elemSize) == 0)
                    return 1;
                else if (cmp(oneBytePointer + (i + j) * elemSize, valueArrCharPointer + j * elemSize) != 0)
                    break;

            }

        }

    }

    return 0;

}


/** This function will check if the passed values array,
 * is a sub array from the original array, and if it was the function will return the start index,
 * other wise it will return minus one (-1).
 *
 * @param arr the array pointer
 * @param arrLength the length of the array
 * @param values the values array
 * @param valuesArrLength the length of the values array
 * @param elemSize the size of the values elements
 * @param cmp the comparator function pointer, that will be called to compare values
 * @return it will return the start index of the sub array if the values array is a sub array from the original array, other wise it will return -1
 */

int arrGetStartIndex(void *arr, int arrLength, void *values, int valuesArrLength, int elemSize,
                     int (*cmp)(const void *, const void *)) {

    if (arr == NULL) {
#ifdef C_DATASTRUCTURES_ERRORSTESTSTRUCT_H
        ERROR_TEST->errorCode = NULL_POINTER;
        return -1;
#else
        fprintf(stderr, NULL_POINTER_MESSAGE, "passed array", "array get start index function");
        exit(NULL_POINTER);
#endif
    } else if (values == NULL) {
#ifdef C_DATASTRUCTURES_ERRORSTESTSTRUCT_H
        ERROR_TEST->errorCode = INVALID_ARG;
        return -1;
#else
        fprintf(stderr, NULL_POINTER_MESSAGE, "passed values array", "array get start index function");
        exit(NULL_POINTER);
#endif
    } else if (cmp == NULL) {
#ifdef C_DATASTRUCTURES_ERRORSTESTSTRUCT_H
        ERROR_TEST->errorCode = INVALID_ARG;
        return -1;
#else
        fprintf(stderr, INVALID_ARG_MESSAGE, "comparator function pointer", "array get start index function");
        exit(INVALID_ARG);
#endif
    } else if (arrLength < 0) {
#ifdef C_DATASTRUCTURES_ERRORSTESTSTRUCT_H
        ERROR_TEST->errorCode = INVALID_ARG;
        return -1;
#else
        fprintf(stderr, INVALID_ARG_MESSAGE, "array length", "array get start index function");
        exit(INVALID_ARG);
#endif
    } else if (valuesArrLength < 0) {
#ifdef C_DATASTRUCTURES_ERRORSTESTSTRUCT_H
        ERROR_TEST->errorCode = INVALID_ARG;
        return -1;
#else
        fprintf(stderr, INVALID_ARG_MESSAGE, "values array length", "array get start index function");
        exit(INVALID_ARG);
#endif
    } else if (elemSize <= 0) {
#ifdef C_DATASTRUCTURES_ERRORSTESTSTRUCT_H
        ERROR_TEST->errorCode = INVALID_ARG;
        return -1;
#else
        fprintf(stderr, INVALID_ARG_MESSAGE, "element size", "array get start index function");
        exit(INVALID_ARG);
#endif
    }


    char *oneBytePointer = (char *) arr;
    char *valueArrCharPointer = (char *) values;

    for (int i = 0; i <= arrLength - valuesArrLength; i++) {

        if (cmp(oneBytePointer + i * elemSize, valueArrCharPointer) == 0) {

            for (int j = 0; j < valuesArrLength; j++) {

                if (j == valuesArrLength - 1 &&
                    cmp(oneBytePointer + (i + j) * elemSize, valueArrCharPointer + j * elemSize) == 0)
                    return i;
                else if (cmp(oneBytePointer + (i + j) * elemSize, valueArrCharPointer + j * elemSize) != 0)
                    break;

            }

        }

    }

    return -1;

}


/** This function will take an array and value,
 * then it will return one (1) if the values is in the array, other wise it will return zero (0).
 *
 * @param arr the array pointer
 * @param value the value pointer
 * @param length the length of the array
 * @param elemSize the size of the array elements in bytes
 * @param cmp the comparator function pointer, that will be called to compare the values
 * @return it will return 1 if the values exist in the array, other wise it will return 0
 */

int arrContains(void *arr, void *value, int length, int elemSize, int (*cmp)(const void *, const void *)) {

    if (arr == NULL) {
#ifdef C_DATASTRUCTURES_ERRORSTESTSTRUCT_H
        ERROR_TEST->errorCode = NULL_POINTER;
        return -1;
#else
        fprintf(stderr, NULL_POINTER_MESSAGE, "passed array", "array contains function");
        exit(NULL_POINTER);
#endif
    } else if (value == NULL) {
#ifdef C_DATASTRUCTURES_ERRORSTESTSTRUCT_H
        ERROR_TEST->errorCode = INVALID_ARG;
        return -1;
#else
        fprintf(stderr, NULL_POINTER_MESSAGE, "passed value", "array contains function");
        exit(NULL_POINTER);
#endif
    } else if (cmp == NULL) {
#ifdef C_DATASTRUCTURES_ERRORSTESTSTRUCT_H
        ERROR_TEST->errorCode = INVALID_ARG;
        return -1;
#else
        fprintf(stderr, INVALID_ARG_MESSAGE, "comparator function pointer", "array contains function");
        exit(INVALID_ARG);
#endif
    } else if (length < 0) {
#ifdef C_DATASTRUCTURES_ERRORSTESTSTRUCT_H
        ERROR_TEST->errorCode = INVALID_ARG;
        return -1;
#else
        fprintf(stderr, INVALID_ARG_MESSAGE, "array length", "array contains function");
        exit(INVALID_ARG);
#endif
    } else if (elemSize <= 0) {
#ifdef C_DATASTRUCTURES_ERRORSTESTSTRUCT_H
        ERROR_TEST->errorCode = INVALID_ARG;
        return -1;
#else
        fprintf(stderr, INVALID_ARG_MESSAGE, "element size", "array contains function");
        exit(INVALID_ARG);
#endif
    }

    char *oneBytePointer = (char *) arr;

    for (int i = 0; i < length; i++) {

        if (cmp(value, oneBytePointer + i * elemSize) == 0)
            return 1;

    }

    return 0;

}


/** This function will take an array and index,
 * then it will remove the value in the given index.
 *
 * Note: the function will memory copy the value index i + 1 to remove the value in index i,
 * so if the value need to be freed first then pass the free function, other wise pass NULL function pointer.
 *
 * @param arr the array pointer
 * @param index the index of the value
 * @param length the length of the array
 * @param elemSize the size of the array elements in bytes
 * @param freeFun the free function pointer, that will be called to free the value before removing it from the array
 */

void arrRemoveAtIndex(void *arr, int index, int length, int elemSize, void (*freeFun)(void *)) {

    if (arr == NULL) {
#ifdef C_DATASTRUCTURES_ERRORSTESTSTRUCT_H
        ERROR_TEST->errorCode = NULL_POINTER;
        return;
#else
        fprintf(stderr, NULL_POINTER_MESSAGE, "passed array", "array remove function");
        exit(NULL_POINTER);
#endif
    } else if (length < 0) {
#ifdef C_DATASTRUCTURES_ERRORSTESTSTRUCT_H
        ERROR_TEST->errorCode = INVALID_ARG;
        return;
#else
        fprintf(stderr, INVALID_ARG_MESSAGE, "array length", "array remove function");
        exit(INVALID_ARG);
#endif
    } else if (elemSize <= 0) {
#ifdef C_DATASTRUCTURES_ERRORSTESTSTRUCT_H
        ERROR_TEST->errorCode = INVALID_ARG;
        return;
#else
        fprintf(stderr, INVALID_ARG_MESSAGE, "element size", "array remove function");
        exit(INVALID_ARG);
#endif
    } else if (index < 0 || index >= length) {
#ifdef C_DATASTRUCTURES_ERRORSTESTSTRUCT_H
        ERROR_TEST->errorCode = INVALID_ARG;
        return;
#else
        fprintf(stderr, OUT_OF_RANGE_MESSAGE, "remove at index function array");
        exit(OUT_OF_RANGE);
#endif
    }

    char *oneBytePointer = (char *) arr;

    if (freeFun != NULL)
        freeFun(oneBytePointer + index * elemSize);

    for (int i = index; i < length - 1; i++)
        memcpy(oneBytePointer + i * elemSize, oneBytePointer + (i + 1) * elemSize, elemSize);

}


/** This function will take an array,
 * then it will sort the array using quick sort algorithm.
 *
 * @param arr the array pointer
 * @param length the length of the array
 * @param elemSize the size of the array elements
 * @param cmp the comparator function pointer, that will be called to compare the values
 */

void arrSort(void *arr, int length, int elemSize, int (*cmp)(const void *, const void *)) {

    if (arr == NULL) {
#ifdef C_DATASTRUCTURES_ERRORSTESTSTRUCT_H
        ERROR_TEST->errorCode = NULL_POINTER;
        return;
#else
        fprintf(stderr, NULL_POINTER_MESSAGE, "passed array", "array sort function");
        exit(NULL_POINTER);
#endif
    } else if (cmp == NULL) {
#ifdef C_DATASTRUCTURES_ERRORSTESTSTRUCT_H
        ERROR_TEST->errorCode = INVALID_ARG;
        return;
#else
        fprintf(stderr, INVALID_ARG_MESSAGE, "comparator function pointer", "array sort function");
        exit(INVALID_ARG);
#endif
    } else if (length < 0) {
#ifdef C_DATASTRUCTURES_ERRORSTESTSTRUCT_H
        ERROR_TEST->errorCode = INVALID_ARG;
        return;
#else
        fprintf(stderr, INVALID_ARG_MESSAGE, "array length", "array sort function");
        exit(INVALID_ARG);
#endif
    } else if (elemSize <= 0) {
#ifdef C_DATASTRUCTURES_ERRORSTESTSTRUCT_H
        ERROR_TEST->errorCode = INVALID_ARG;
        return;
#else
        fprintf(stderr, INVALID_ARG_MESSAGE, "element size", "array sort function");
        exit(INVALID_ARG);
#endif
    }

    quickSort(arr, length, elemSize, cmp);

}


/** This function will take an array and a value,
 * then it will return the index of the first occurrence of the value in the array if found,
 * other wise it will return minus one (-1).
 * @param arr the array pointer
 * @param value the value pointer
 * @param length the length of the array
 * @param elemSize the size of the array elements in bytes
 * @param cmp the comparator function pointer, that will be called to compare the values
 * @return it will return the index of the first occurrence of the value if found, other wise it will return -1
 */

int arrGetFirst(void *arr, void *value, int length, int elemSize, int (*cmp)(const void *, const void *)) {

    if (arr == NULL) {
#ifdef C_DATASTRUCTURES_ERRORSTESTSTRUCT_H
        ERROR_TEST->errorCode = NULL_POINTER;
        return -1;
#else
        fprintf(stderr, NULL_POINTER_MESSAGE, "passed array", "array get first function");
        exit(NULL_POINTER);
#endif
    } else if (value == NULL) {
#ifdef C_DATASTRUCTURES_ERRORSTESTSTRUCT_H
        ERROR_TEST->errorCode = INVALID_ARG;
        return -1;
#else
        fprintf(stderr, INVALID_ARG_MESSAGE, "value pointer", "array get first function");
        exit(INVALID_ARG);
#endif
    } else if (cmp == NULL) {
#ifdef C_DATASTRUCTURES_ERRORSTESTSTRUCT_H
        ERROR_TEST->errorCode = INVALID_ARG;
        return -1;
#else
        fprintf(stderr, INVALID_ARG_MESSAGE, "comparator function pointer", "array get first function");
        exit(INVALID_ARG);
#endif
    } else if (length < 0) {
#ifdef C_DATASTRUCTURES_ERRORSTESTSTRUCT_H
        ERROR_TEST->errorCode = INVALID_ARG;
        return -1;
#else
        fprintf(stderr, INVALID_ARG_MESSAGE, "array length", "array get first function");
        exit(INVALID_ARG);
#endif
    } else if (elemSize <= 0) {
#ifdef C_DATASTRUCTURES_ERRORSTESTSTRUCT_H
        ERROR_TEST->errorCode = INVALID_ARG;
        return -1;
#else
        fprintf(stderr, INVALID_ARG_MESSAGE, "element size", "array get first function");
        exit(INVALID_ARG);
#endif
    }

    return linearSearch(arr, value, length, elemSize, cmp);

}


/** This function will take an array and a value,
 * then it will return the index of the last occurrence of the value in the array if found,
 * other wise it will return minus one (-1).
 *
 * @param arr the array pointer
 * @param value the value pointer
 * @param length the length of the array
 * @param elemSize the size of the array elements in bytes
 * @param cmp the comparator function pointer, that will be called to compare the values
 * @return it will return the index of the last occurrence of the value if found, other wise it will return -1
 */

int arrGetLast(void *arr, void *value, int length, int elemSize, int (*cmp)(const void *, const void *)) {

    if (arr == NULL) {
#ifdef C_DATASTRUCTURES_ERRORSTESTSTRUCT_H
        ERROR_TEST->errorCode = NULL_POINTER;
        return -1;
#else
        fprintf(stderr, NULL_POINTER_MESSAGE, "passed array", "array get last function");
        exit(NULL_POINTER);
#endif
    } else if (value == NULL) {
#ifdef C_DATASTRUCTURES_ERRORSTESTSTRUCT_H
        ERROR_TEST->errorCode = INVALID_ARG;
        return -1;
#else
        fprintf(stderr, INVALID_ARG_MESSAGE, "value pointer", "array get last function");
        exit(INVALID_ARG);
#endif
    } else if (cmp == NULL) {
#ifdef C_DATASTRUCTURES_ERRORSTESTSTRUCT_H
        ERROR_TEST->errorCode = INVALID_ARG;
        return -1;
#else
        fprintf(stderr, INVALID_ARG_MESSAGE, "comparator function pointer", "array get last function");
        exit(INVALID_ARG);
#endif
    } else if (length < 0) {
#ifdef C_DATASTRUCTURES_ERRORSTESTSTRUCT_H
        ERROR_TEST->errorCode = INVALID_ARG;
        return -1;
#else
        fprintf(stderr, INVALID_ARG_MESSAGE, "array length", "array get last function");
        exit(INVALID_ARG);
#endif
    } else if (elemSize <= 0) {
#ifdef C_DATASTRUCTURES_ERRORSTESTSTRUCT_H
        ERROR_TEST->errorCode = INVALID_ARG;
        return -1;
#else
        fprintf(stderr, INVALID_ARG_MESSAGE, "element size", "array get last function");
        exit(INVALID_ARG);
#endif
    }

    return linearSearchGetLast(arr, value, length, elemSize, cmp);

}


/** This function will take an array and a value,
 * then it will return a vector that contains all the occurrence indices of the value in the array.
 *
 * @param arr the array pointer
 * @param value the value pointer
 * @param length the length of the array
 * @param elemSize the size of the array elements in bytes
 * @param cmp the comparator function pointer, that will be called to compare the values
 * @return it will return a vector that contains all the occurrence indices of the value in the array.
 */

Vector *arrGetAll(void *arr, void *value, int length, int elemSize, int (*cmp)(const void *, const void *)) {

    if (arr == NULL) {
#ifdef C_DATASTRUCTURES_ERRORSTESTSTRUCT_H
        ERROR_TEST->errorCode = NULL_POINTER;
        return NULL;
#else
        fprintf(stderr, NULL_POINTER_MESSAGE, "passed array", "array get all function");
        exit(NULL_POINTER);
#endif
    } else if (value == NULL) {
#ifdef C_DATASTRUCTURES_ERRORSTESTSTRUCT_H
        ERROR_TEST->errorCode = INVALID_ARG;
        return NULL;
#else
        fprintf(stderr, INVALID_ARG_MESSAGE, "value pointer", "array get all function");
        exit(INVALID_ARG);
#endif
    } else if (cmp == NULL) {
#ifdef C_DATASTRUCTURES_ERRORSTESTSTRUCT_H
        ERROR_TEST->errorCode = INVALID_ARG;
        return NULL;
#else
        fprintf(stderr, INVALID_ARG_MESSAGE, "comparator function pointer", "array get all function");
        exit(INVALID_ARG);
#endif
    } else if (length < 0) {
#ifdef C_DATASTRUCTURES_ERRORSTESTSTRUCT_H
        ERROR_TEST->errorCode = INVALID_ARG;
        return NULL;
#else
        fprintf(stderr, INVALID_ARG_MESSAGE, "array length", "array get all function");
        exit(INVALID_ARG);
#endif
    } else if (elemSize <= 0) {
#ifdef C_DATASTRUCTURES_ERRORSTESTSTRUCT_H
        ERROR_TEST->errorCode = INVALID_ARG;
        return NULL;
#else
        fprintf(stderr, INVALID_ARG_MESSAGE, "element size", "array get all function");
        exit(INVALID_ARG);
#endif
    }

    return linearSearchGetAll(arr, value, length, elemSize, cmp);

}


/** This function will take an array and a value,
 * then it will search for the value using binary search algorithm,
 * and finally return the index of the value if found, other wise it will return minus one (-1).
 *
 * @param arr the array pointer
 * @param value the value pointer
 * @param length the length of the array
 * @param elemSize the size of the array elements in bytes
 * @param cmp the comparator function pointer, that will be called to compare the value
 * @return it will return the index of the value if found, other wise it will return -1
 */

int arrBinarySearch(void *arr, void *value, int length, int elemSize, int (*cmp)(const void *, const void *)) {

    if (arr == NULL) {
#ifdef C_DATASTRUCTURES_ERRORSTESTSTRUCT_H
        ERROR_TEST->errorCode = NULL_POINTER;
        return -1;
#else
        fprintf(stderr, NULL_POINTER_MESSAGE, "passed array", "array binary search function");
        exit(NULL_POINTER);
#endif
    } else if (value == NULL) {
#ifdef C_DATASTRUCTURES_ERRORSTESTSTRUCT_H
        ERROR_TEST->errorCode = INVALID_ARG;
        return -1;
#else
        fprintf(stderr, INVALID_ARG_MESSAGE, "value pointer", "array binary search function");
        exit(INVALID_ARG);
#endif
    } else if (cmp == NULL) {
#ifdef C_DATASTRUCTURES_ERRORSTESTSTRUCT_H
        ERROR_TEST->errorCode = INVALID_ARG;
        return -1;
#else
        fprintf(stderr, INVALID_ARG_MESSAGE, "comparator function pointer", "array binary search function");
        exit(INVALID_ARG);
#endif
    } else if (length < 0) {
#ifdef C_DATASTRUCTURES_ERRORSTESTSTRUCT_H
        ERROR_TEST->errorCode = INVALID_ARG;
        return -1;
#else
        fprintf(stderr, INVALID_ARG_MESSAGE, "array length", "array binary search function");
        exit(INVALID_ARG);
#endif
    } else if (elemSize <= 0) {
#ifdef C_DATASTRUCTURES_ERRORSTESTSTRUCT_H
        ERROR_TEST->errorCode = INVALID_ARG;
        return -1;
#else
        fprintf(stderr, INVALID_ARG_MESSAGE, "element size", "array binary search function");
        exit(INVALID_ARG);
#endif
    }

    return binarySearchI(arr, value, length, elemSize, cmp);

}


/** This function will check if the passed array is a palindrome or not,
 * and if it was the function will return one (1), other wise it will return zero (0).
 *
 * @param arr the array pointer
 * @param length the length of the array
 * @param elemSize the size of the array elements in bytes
 * @param cmp the comparator function pointer, that will be called to compare the array values
 * @return it will return 1 if the array is a palindrome, other wise it will return 0
 */

int arrIsPalindrome(void *arr, int length, int elemSize, int (*cmp)(const void *, const void *)) {

    if (arr == NULL) {
#ifdef C_DATASTRUCTURES_ERRORSTESTSTRUCT_H
        ERROR_TEST->errorCode = NULL_POINTER;
        return -1;
#else
        fprintf(stderr, NULL_POINTER_MESSAGE, "passed array", "array is palindrome function");
        exit(NULL_POINTER);
#endif
    } else if (cmp == NULL) {
#ifdef C_DATASTRUCTURES_ERRORSTESTSTRUCT_H
        ERROR_TEST->errorCode = INVALID_ARG;
        return -1;
#else
        fprintf(stderr, INVALID_ARG_MESSAGE, "comparator function pointer", "array is palindrome function");
        exit(INVALID_ARG);
#endif
    } else if (length < 0) {
#ifdef C_DATASTRUCTURES_ERRORSTESTSTRUCT_H
        ERROR_TEST->errorCode = INVALID_ARG;
        return -1;
#else
        fprintf(stderr, INVALID_ARG_MESSAGE, "array length", "array is palindrome function");
        exit(INVALID_ARG);
#endif
    } else if (elemSize <= 0) {
#ifdef C_DATASTRUCTURES_ERRORSTESTSTRUCT_H
        ERROR_TEST->errorCode = INVALID_ARG;
        return -1;
#else
        fprintf(stderr, INVALID_ARG_MESSAGE, "element size", "array is palindrome function");
        exit(INVALID_ARG);
#endif
    }

    char *oneBytePointer = (char *) arr;

    for (int i = 0; i < length / 2; i++) {

        if (cmp(oneBytePointer + i * elemSize, oneBytePointer + (length - 1 - i) * elemSize) != 0)
            return 0;

    }

    return 1;

}


/** This function will take two array,
 * then it will return one (1) if the the first and second arrays are equal but they are rotation of each other,
 * other wise it will return zero (0).
 *
 * Ex of rotation arrays:
 *
 * first array:     [1, 2, 3, 4, 5].
 *
 * second array:    [3, 4, 5, 1, 2].
 *
 * @param fArr the first array pointer
 * @param fLength the first array length
 * @param sArr the second array pointer
 * @param sLength the second array length
 * @param elemSize the size of the arrays elements in bytes
 * @param cmp the comparator function pointer, that will be called to compare the arrays elements
 * @return it will return 1 if the first and second array is rotation of each other, otherwise it will return 0
 */

int
arrIsRotation(void *fArr, int fLength, void *sArr, int sLength, int elemSize, int (*cmp)(const void *, const void *)) {

    if (fArr == NULL) {
#ifdef C_DATASTRUCTURES_ERRORSTESTSTRUCT_H
        ERROR_TEST->errorCode = NULL_POINTER;
        return -1;
#else
        fprintf(stderr, NULL_POINTER_MESSAGE, "first passed array", "array is rotation function");
        exit(NULL_POINTER);
#endif
    } else if (sArr == NULL) {
#ifdef C_DATASTRUCTURES_ERRORSTESTSTRUCT_H
        ERROR_TEST->errorCode = NULL_POINTER;
        return -1;
#else
        fprintf(stderr, NULL_POINTER_MESSAGE, "second passed array", "array is rotation function");
        exit(NULL_POINTER);
#endif
    } else if (cmp == NULL) {
#ifdef C_DATASTRUCTURES_ERRORSTESTSTRUCT_H
        ERROR_TEST->errorCode = INVALID_ARG;
        return -1;
#else
        fprintf(stderr, INVALID_ARG_MESSAGE, "comparator function pointer", "array is rotation function");
        exit(INVALID_ARG);
#endif
    } else if (fLength < 0 || sLength < 0) {
#ifdef C_DATASTRUCTURES_ERRORSTESTSTRUCT_H
        ERROR_TEST->errorCode = INVALID_ARG;
        return -1;
#else
        fprintf(stderr, INVALID_ARG_MESSAGE, "arrays length", "array is rotation function");
        exit(INVALID_ARG);
#endif
    } else if (elemSize <= 0) {
#ifdef C_DATASTRUCTURES_ERRORSTESTSTRUCT_H
        ERROR_TEST->errorCode = INVALID_ARG;
        return -1;
#else
        fprintf(stderr, INVALID_ARG_MESSAGE, "element size", "array is rotation function");
        exit(INVALID_ARG);
#endif
    }

    if (fLength != sLength)
        return 0;

    char *fOneBytePointer = (char *) fArr;
    char *sOneBytePointer = (char *) sArr;

    for (int i = 0; i < fLength; i++) {

        if (cmp(fOneBytePointer + i * elemSize, sOneBytePointer) == 0) {

            int firstArrIndex = i;
            int secondArrIndex = 0;
            int isRotationFlag = 1;

            while (secondArrIndex != sLength) {

                if (cmp(fOneBytePointer + firstArrIndex * elemSize, sOneBytePointer + secondArrIndex * elemSize) != 0) {
                    isRotationFlag = 0;
                    break;
                }

                firstArrIndex = (firstArrIndex + 1) % fLength;
                secondArrIndex++;

            }

            if (isRotationFlag)
                return 1;

        }

    }

    return 0;

}


/** This function will take an array, index and value,
 * then it will free int item in the passed index, then memory copy the passed value in the index.
 *
 * Note: if the items don't need to be freed, then pass a NULL free function.
 *
 * @param arr the array pointer
 * @param value the new value pointer
 * @param length the length of the array
 * @param elemSize the size of the array elements in bytes
 * @param index the index of the value that will be updated
 * @param freeFun the freeing function pointer, that will be called to free the value before updating it
 */

void arrUpdateElem(void *arr, void *value, int length, int elemSize, int index, void (*freeFun)(void *)) {

    if (arr == NULL) {
#ifdef C_DATASTRUCTURES_ERRORSTESTSTRUCT_H
        ERROR_TEST->errorCode = NULL_POINTER;
        return;
#else
        fprintf(stderr, NULL_POINTER_MESSAGE, "passed array", "arr update element function");
        exit(NULL_POINTER);
#endif
    } else if (value == NULL) {
#ifdef C_DATASTRUCTURES_ERRORSTESTSTRUCT_H
        ERROR_TEST->errorCode = INVALID_ARG;
        return;
#else
        fprintf(stderr, INVALID_ARG_MESSAGE, "passed value", "arr update element function");
        exit(INVALID_ARG);
#endif
    } else if (length < 0) {
#ifdef C_DATASTRUCTURES_ERRORSTESTSTRUCT_H
        ERROR_TEST->errorCode = INVALID_ARG;
        return;
#else
        fprintf(stderr, INVALID_ARG_MESSAGE, "array length", "arr update element function");
        exit(INVALID_ARG);
#endif
    } else if (elemSize <= 0) {
#ifdef C_DATASTRUCTURES_ERRORSTESTSTRUCT_H
        ERROR_TEST->errorCode = INVALID_ARG;
        return;
#else
        fprintf(stderr, INVALID_ARG_MESSAGE, "element size", "arr update element function");
        exit(INVALID_ARG);
#endif
    } else if (index < 0 || index >= length) {
#ifdef C_DATASTRUCTURES_ERRORSTESTSTRUCT_H
        ERROR_TEST->errorCode = INVALID_ARG;
        return;
#else
        fprintf(stderr, OUT_OF_RANGE_MESSAGE, "array add function");
        exit(OUT_OF_RANGE);
#endif
    }

    char *oneBytePointer = (char *) arr;

    if (freeFun != NULL)
        freeFun(oneBytePointer + index * elemSize);

    memcpy(oneBytePointer + index * elemSize, value, elemSize);

}


/** This function will take an array and a value,
 * then it will insert the new value in the given index.
 *
 * Note: the array should have a free space at the end.
 *
 * Note: this function will memory copy the new value.
 *
 * @param arr the array pointer
 * @param value the new value pointer
 * @param length the length of the array
 * @param elemSize the size of the array elements in bytes
 * @param index the index that the new value will be inserted in.
 */

void arrAdd(void *arr, void *value, int length, int elemSize, int index) {

    if (arr == NULL) {
#ifdef C_DATASTRUCTURES_ERRORSTESTSTRUCT_H
        ERROR_TEST->errorCode = NULL_POINTER;
        return;
#else
        fprintf(stderr, NULL_POINTER_MESSAGE, "passed array", "array add function");
        exit(NULL_POINTER);
#endif
    } else if (value == NULL) {
#ifdef C_DATASTRUCTURES_ERRORSTESTSTRUCT_H
        ERROR_TEST->errorCode = INVALID_ARG;
        return;
#else
        fprintf(stderr, INVALID_ARG_MESSAGE, "passed value", "array add function");
        exit(INVALID_ARG);
#endif
    } else if (length < 0) {
#ifdef C_DATASTRUCTURES_ERRORSTESTSTRUCT_H
        ERROR_TEST->errorCode = INVALID_ARG;
        return;
#else
        fprintf(stderr, INVALID_ARG_MESSAGE, "array length", "array add function");
        exit(INVALID_ARG);
#endif
    } else if (elemSize <= 0) {
#ifdef C_DATASTRUCTURES_ERRORSTESTSTRUCT_H
        ERROR_TEST->errorCode = INVALID_ARG;
        return;
#else
        fprintf(stderr, INVALID_ARG_MESSAGE, "element size", "array add function");
        exit(INVALID_ARG);
#endif
    } else if (index < 0 || index >= length) {
#ifdef C_DATASTRUCTURES_ERRORSTESTSTRUCT_H
        ERROR_TEST->errorCode = INVALID_ARG;
        return;
#else
        fprintf(stderr, OUT_OF_RANGE_MESSAGE, "array add function");
        exit(OUT_OF_RANGE);
#endif
    }

    char *oneBytePointer = (char *) arr;

    for (int i = length + 1; i > index; i--)
        memcpy(oneBytePointer + i * elemSize, oneBytePointer + (i - 1) * elemSize, elemSize);

    memcpy(oneBytePointer + index * elemSize, value, elemSize);

}


/** This function will take an array and a values array,
 * then it will insert the values in the values array into the original array in the given index.
 *
 * Note: the array should have a free space at the end.
 *
 * Note: this function will memory copy the new values.
 *
 * @param arr the array pointer
 * @param arrLength the length of the array
 * @param values the values array pointer
 * @param valuesArrLength the length of the values array
 * @param elemSize the size of the values in bytes
 * @param index the index that the new values will be inserted in
 */

void arrAddAll(void *arr, int arrLength, void *values, int valuesArrLength, int elemSize, int index) {

    if (arr == NULL) {
#ifdef C_DATASTRUCTURES_ERRORSTESTSTRUCT_H
        ERROR_TEST->errorCode = NULL_POINTER;
        return;
#else
        fprintf(stderr, NULL_POINTER_MESSAGE, "passed array", "array add all function");
        exit(NULL_POINTER);
#endif
    } else if (values == NULL) {
#ifdef C_DATASTRUCTURES_ERRORSTESTSTRUCT_H
        ERROR_TEST->errorCode = INVALID_ARG;
        return;
#else
        fprintf(stderr, NULL_POINTER_MESSAGE, "passed values array", "array add all function");
        exit(NULL_POINTER);
#endif
    } else if (arrLength < 0) {
#ifdef C_DATASTRUCTURES_ERRORSTESTSTRUCT_H
        ERROR_TEST->errorCode = INVALID_ARG;
        return;
#else
        fprintf(stderr, INVALID_ARG_MESSAGE, "array length", "array add all function");
        exit(INVALID_ARG);
#endif
    } else if (valuesArrLength < 0) {
#ifdef C_DATASTRUCTURES_ERRORSTESTSTRUCT_H
        ERROR_TEST->errorCode = INVALID_ARG;
        return;
#else
        fprintf(stderr, INVALID_ARG_MESSAGE, "values array length", "array add all function");
        exit(INVALID_ARG);
#endif
    } else if (elemSize <= 0) {
#ifdef C_DATASTRUCTURES_ERRORSTESTSTRUCT_H
        ERROR_TEST->errorCode = INVALID_ARG;
        return;
#else
        fprintf(stderr, INVALID_ARG_MESSAGE, "element size", "array add all function");
        exit(INVALID_ARG);
#endif
    } else if (index < 0 || index >= arrLength) {
#ifdef C_DATASTRUCTURES_ERRORSTESTSTRUCT_H
        ERROR_TEST->errorCode = INVALID_ARG;
        return;
#else
        fprintf(stderr, OUT_OF_RANGE_MESSAGE, "array add all function");
        exit(OUT_OF_RANGE);
#endif
    }

    char *oneBytePointer = (char *) arr;
    char *valueArrCharPointer = (char *) values;

    for (int i = arrLength + valuesArrLength - 1; i > index; i--)
        memcpy(oneBytePointer + i * elemSize, oneBytePointer + (i - valuesArrLength) * elemSize, elemSize);

    for (int i = 0; i < valuesArrLength; i++)
        memcpy(oneBytePointer + (index + i) * elemSize, valueArrCharPointer + i * elemSize, elemSize);

}