#include "../Headers/HashSet.h"
#include "../../../System/Utils.h"
#include "../../../Unit Test/CuTest/CuTest.h"
#include <limits.h>


int hashSetCalBPrime(int length);

int hashSetGetNextPrime(int num);

unsigned int hashSetFHashCal(int (*hashFun)(const void *), void *key, unsigned int length);

unsigned int hashSetSHashCal(int (*hashFun)(const void *), void *key, unsigned int bPrime);

unsigned int hashSetCalIndex(unsigned int fHash, unsigned int sHash, unsigned int index, unsigned int length);


/** This function will take the size of the hash set elements type, and the comparing items function as a parameters,
 * then it will return a new hash set address.
 *
 * @param freeItem the freeing item function address, that will be called to free the hash set items
 * @param itemComp the comparing item function address, that will be called to compare two items.
 * @param hashFun the hashing function that will return a unique integer representing the hash set item
 * @return it will return a new hash set pointer
 */

HashSet *hashSetInitialization(
        void (*freeItem)(void *),
        int (*itemComp)(const void *, const void *),
        int (*hashFun)(const void *)
) {

    if (freeItem == NULL) {
#ifdef C_DATASTRUCTURES_ERRORSTESTSTRUCT_H
        ERROR_TEST->errorCode = INVALID_ARG;
        return NULL;
#else
        fprintf(stderr, INVALID_ARG_MESSAGE, "free function pointer", "hash set data structure");
        exit(INVALID_ARG);
#endif

    } else if (itemComp == NULL) {
#ifdef C_DATASTRUCTURES_ERRORSTESTSTRUCT_H
        ERROR_TEST->errorCode = INVALID_ARG;
        return NULL;
#else
        fprintf(stderr, INVALID_ARG_MESSAGE, "comparator function pointer", "hash set data structure");
        exit(INVALID_ARG);
#endif

    } else if (hashFun == NULL) {
#ifdef C_DATASTRUCTURES_ERRORSTESTSTRUCT_H
        ERROR_TEST->errorCode = INVALID_ARG;
        return NULL;
#else
        fprintf(stderr, INVALID_ARG_MESSAGE, "hash function pointer", "hash set data structure");
        exit(INVALID_ARG);
#endif
    }

    HashSet *hashSet = (HashSet *) malloc(sizeof(HashSet));
    if (hashSet == NULL) {
#ifdef C_DATASTRUCTURES_ERRORSTESTSTRUCT_H
        ERROR_TEST->errorCode = FAILED_ALLOCATION;
        return NULL;
#else
        fprintf(stderr, FAILED_ALLOCATION_MESSAGE, "hash set", "hash set data structure");
        exit(FAILED_ALLOCATION);
#endif

    }

    hashSet->length = hashSetGetNextPrime(10);
    hashSet->arr = (void **) calloc(sizeof(void *), hashSet->length);
    if (hashSet->arr == NULL) {
#ifdef C_DATASTRUCTURES_ERRORSTESTSTRUCT_H
        ERROR_TEST->errorCode = FAILED_ALLOCATION;
        return NULL;
#else
        fprintf(stderr, FAILED_ALLOCATION_MESSAGE, "hash set array", "hash set data structure");
        exit(FAILED_ALLOCATION);
#endif

    }

    hashSet->count = 0;
    hashSet->freeItem = freeItem;
    hashSet->bPrime = hashSetCalBPrime(hashSet->length);

    hashSet->itemComp = itemComp;
    hashSet->freeItem = freeItem;
    hashSet->hashFun = hashFun;

    return hashSet;

}


/** This function will take the hash set address, and the new item address as a parameters,
 * then it will insert the provided item into the hash set.
 *
 * Note: the hash set will hold the provided item address (it will not copy the item data into the hash set).
 *
 * @param hashSet the hash set address
 * @param item the new item address
 */

void hashSetInsert(HashSet *hashSet, void *item) {

    if (hashSet == NULL) {
#ifdef C_DATASTRUCTURES_ERRORSTESTSTRUCT_H
        ERROR_TEST->errorCode = NULL_POINTER;
        return;
#else
        fprintf(stderr, NULL_POINTER_MESSAGE, "hash set", "hash set data structure");
        exit(NULL_POINTER);
#endif

    } else if (item == NULL) {
#ifdef C_DATASTRUCTURES_ERRORSTESTSTRUCT_H
        ERROR_TEST->errorCode = INVALID_ARG;
        return;
#else
        fprintf(stderr, INVALID_ARG_MESSAGE, "item pointer", "hash set data structure");
        exit(INVALID_ARG);
#endif

    }

    if (hashSet->count == hashSet->length) {
        hashSet->length = hashSetGetNextPrime(hashSet->length * 2);
        hashSet->bPrime = hashSetCalBPrime(hashSet->length);
        hashSet->arr = (void **) realloc(hashSet->arr, sizeof(void *) * hashSet->length);
        if (hashSet->arr == NULL) {
#ifdef C_DATASTRUCTURES_ERRORSTESTSTRUCT_H
            ERROR_TEST->errorCode = FAILED_REALLOCATION;
            return;
#else
            fprintf(stderr, FAILED_REALLOCATION_MESSAGE, "hash set array", "hash set data structure");
            exit(FAILED_REALLOCATION);
#endif

        }

        for (int i = hashSet->count; i < hashSet->length; i++)
            hashSet->arr[i] = NULL;

    }


    unsigned int fHash = hashSetFHashCal(hashSet->hashFun, item, hashSet->length),
            sHash = hashSetSHashCal(hashSet->hashFun, item, hashSet->bPrime);

    unsigned int pHashIndex = 1;
    unsigned int index = hashSetCalIndex(fHash, sHash, pHashIndex, hashSet->length);

    while (hashSet->arr[index] != NULL) {

        if (hashSet->itemComp(item, hashSet->arr[index]) == 0) {
            hashSet->freeItem(hashSet->arr[index]);
            hashSet->arr[index] = item;
            return;
        }

        pHashIndex++;
        index = hashSetCalIndex(fHash, sHash, pHashIndex, hashSet->length);

    }

    hashSet->arr[index] = item;
    hashSet->count++;

}


/** This function will take the hash set address, and the item address as a parameters,
 * then it will delete and free the provided item from the hash set.
 *
 * Note: if the item was found in the hash set, then the function will free the item in the hash set,
 * without freeing the provided one in the parameters.
 *
 * @param hashSet the hash set address
 * @param item the item address that hash the same data as the item that will be deleted
 */

void hashSetDelete(HashSet *hashSet, void *item) {
    if (hashSet == NULL) {
#ifdef C_DATASTRUCTURES_ERRORSTESTSTRUCT_H
        ERROR_TEST->errorCode = NULL_POINTER;
        return;
#else
        fprintf(stderr, NULL_POINTER_MESSAGE, "hash set", "hash set data structure");
        exit(NULL_POINTER);
#endif

    } else if (item == NULL) {
#ifdef C_DATASTRUCTURES_ERRORSTESTSTRUCT_H
        ERROR_TEST->errorCode = INVALID_ARG;
        return;
#else
        fprintf(stderr, INVALID_ARG_MESSAGE, "item pointer", "hash set data structure");
        exit(INVALID_ARG);
#endif

    }

    unsigned int fHash = hashSetFHashCal(hashSet->hashFun, item, hashSet->length),
            sHash = hashSetSHashCal(hashSet->hashFun, item, hashSet->bPrime);

    unsigned int pHashIndex = 1;
    unsigned int index = hashSetCalIndex(fHash, sHash, pHashIndex, hashSet->length);
    unsigned int firstIndex = index;

    do {

        if (hashSet->arr[index] != NULL) {
            if (hashSet->itemComp(item, hashSet->arr[index]) == 0) {
                hashSet->freeItem(hashSet->arr[index]);
                hashSet->arr[index] = NULL;
                hashSet->count--;
                return;
            }

        }

        pHashIndex++;
        index = hashSetCalIndex(fHash, sHash, pHashIndex, hashSet->length);

    } while (firstIndex != index);

}


/** This function will take the hash set address, and the item address, as a parameters,
 * then it will delete the provided item from the hash set without freeing it.
 *
 * Note: the function will not free the passed item.
 *
 * @param hashSet the hash set address
 * @param item the item address that hash the same data as the item that will be deleted
 * @return it will return the deleted item pointer if found, other wise it will return NULL
 */

void *hashSetDeleteWtoFr(HashSet *hashSet, void *item) {
    if (hashSet == NULL) {
#ifdef C_DATASTRUCTURES_ERRORSTESTSTRUCT_H
        ERROR_TEST->errorCode = NULL_POINTER;
        return NULL;
#else
        fprintf(stderr, NULL_POINTER_MESSAGE, "hash set", "hash set data structure");
        exit(NULL_POINTER);
#endif

    } else if (item == NULL) {
#ifdef C_DATASTRUCTURES_ERRORSTESTSTRUCT_H
        ERROR_TEST->errorCode = INVALID_ARG;
        return NULL;
#else
        fprintf(stderr, INVALID_ARG_MESSAGE, "item pointer", "hash set data structure");
        exit(INVALID_ARG);
#endif

    }

    unsigned int fHash = hashSetFHashCal(hashSet->hashFun, item, hashSet->length),
            sHash = hashSetSHashCal(hashSet->hashFun, item, hashSet->bPrime);

    unsigned int pHashIndex = 1;
    unsigned int index = hashSetCalIndex(fHash, sHash, pHashIndex, hashSet->length);
    unsigned int firstIndex = index;

    do {

        if (hashSet->arr[index] != NULL) {
            if (hashSet->itemComp(item, hashSet->arr[index]) == 0) {
                void *returnItem = hashSet->arr[index];
                hashSet->arr[index] = NULL;
                hashSet->count--;
                return returnItem;
            }

        }

        pHashIndex++;
        index = hashSetCalIndex(fHash, sHash, pHashIndex, hashSet->length);

    } while (firstIndex != index);


    return NULL;

}


/** This function will take the hash set address, and the item address, as a parameters,
 * then it will return one (1) if the provided item is in the hash set,
 * other wise it will return zero (0).
 *
 * Note: the function will not free the passed item.
 *
 * @param hashSet the hash set address
 * @param item the item address that has the same data as the one that you are searching for.
 * @return it will return one if the provided item is in the hash set, other wise it will return zero
 */

int hashSetContains(HashSet *hashSet, void *item) {
    if (hashSet == NULL) {
#ifdef C_DATASTRUCTURES_ERRORSTESTSTRUCT_H
        ERROR_TEST->errorCode = NULL_POINTER;
        return -1;
#else
        fprintf(stderr, NULL_POINTER_MESSAGE, "hash set", "hash set data structure");
        exit(NULL_POINTER);
#endif

    } else if (item == NULL) {
#ifdef C_DATASTRUCTURES_ERRORSTESTSTRUCT_H
        ERROR_TEST->errorCode = INVALID_ARG;
        return -1;
#else
        fprintf(stderr, INVALID_ARG_MESSAGE, "item pointer", "hash set data structure");
        exit(INVALID_ARG);
#endif

    }

    unsigned int fHash = hashSetFHashCal(hashSet->hashFun, item, hashSet->length),
            sHash = hashSetSHashCal(hashSet->hashFun, item, hashSet->bPrime);

    unsigned int pHashIndex = 1;
    unsigned int index = hashSetCalIndex(fHash, sHash, pHashIndex, hashSet->length);
    unsigned int firstIndex = index;

    do {

        if (hashSet->arr[index] != NULL) {
            if (hashSet->itemComp(item, hashSet->arr[index]) == 0)
                return 1;

        }

        pHashIndex++;
        index = hashSetCalIndex(fHash, sHash, pHashIndex, hashSet->length);

    } while (firstIndex != index);

    return 0;
}


/** This function will take the hash set address, and the item address, as a parameters,
 * then it will return the item pointer if found, other wise it will return NULL.
 *
 * Note: the function will not free the passed item.
 *
 * @param hashSet the hash set address
 * @param item the item address that has the same data as the one that you are searching for.
 * @return it will return the item pointer if found, other wise it will return NULL
 */

void *hashSetGet(HashSet *hashSet, void *item) {
    if (hashSet == NULL) {
#ifdef C_DATASTRUCTURES_ERRORSTESTSTRUCT_H
        ERROR_TEST->errorCode = NULL_POINTER;
        return NULL;
#else
        fprintf(stderr, NULL_POINTER_MESSAGE, "hash set", "hash set data structure");
        exit(NULL_POINTER);
#endif

    } else if (item == NULL) {
#ifdef C_DATASTRUCTURES_ERRORSTESTSTRUCT_H
        ERROR_TEST->errorCode = INVALID_ARG;
        return NULL;
#else
        fprintf(stderr, INVALID_ARG_MESSAGE, "item pointer", "hash set data structure");
        exit(INVALID_ARG);
#endif

    }

    unsigned int fHash = hashSetFHashCal(hashSet->hashFun, item, hashSet->length),
            sHash = hashSetSHashCal(hashSet->hashFun, item, hashSet->bPrime);

    unsigned int pHashIndex = 1;
    unsigned int index = hashSetCalIndex(fHash, sHash, pHashIndex, hashSet->length);
    unsigned int firstIndex = index;

    do {

        if (hashSet->arr[index] != NULL) {
            if (hashSet->itemComp(item, hashSet->arr[index]) == 0)
                return hashSet->arr[index];

        }

        pHashIndex++;
        index = hashSetCalIndex(fHash, sHash, pHashIndex, hashSet->length);

    } while (firstIndex != index);

    return NULL;

}


/** This function will take the hash set address as a parameter,
 * then it will return a double void pointer array that hash a copy of all items in the hash set.
 *
 * @param hashSet the address of the hash set
 * @return it will return a double void array that is a copy of the hash set items
 */

void **hashSetToArray(HashSet *hashSet) {
    if (hashSet == NULL) {
#ifdef C_DATASTRUCTURES_ERRORSTESTSTRUCT_H
        ERROR_TEST->errorCode = NULL_POINTER;
        return NULL;
#else
        fprintf(stderr, NULL_POINTER_MESSAGE, "hash set", "hash set data structure");
        exit(NULL_POINTER);
#endif

    }

    void **array = (void **) malloc(sizeof(void *) * hashSetGetLength(hashSet));
    if (array == NULL) {
#ifdef C_DATASTRUCTURES_ERRORSTESTSTRUCT_H
        ERROR_TEST->errorCode = FAILED_ALLOCATION;
        return NULL;
#else
        fprintf(stderr, FAILED_ALLOCATION_MESSAGE, "to array", "hash set data structure");
        exit(FAILED_ALLOCATION);
#endif

    }

    for (int i = 0, index = 0; i < hashSet->length; i++) {
        if (hashSet->arr[i] != NULL)
            array[index++] = hashSet->arr[i];

    }

    return array;

}


/** This function will take the hash set address as a parameter,
 * then it will return the number of items in the hash set.
 *
 * @param hashSet the hash set address
 * @return it will return the number of items in the hash set
 */

int hashSetGetLength(HashSet *hashSet) {

    if (hashSet == NULL) {
#ifdef C_DATASTRUCTURES_ERRORSTESTSTRUCT_H
        ERROR_TEST->errorCode = NULL_POINTER;
        return -1;
#else
        fprintf(stderr, NULL_POINTER_MESSAGE, "hash set", "hash set data structure");
        exit(NULL_POINTER);
#endif

    }

    return hashSet->count;

}


/** This function will take the hash set address as a parameter,
 * then it will return one (1) if the hash set is empty,
 * other wise it will return zero (0).
 *
 * @param hashSet the hash set address
 * @return it will return one if the hash set is empty, other wise it will return zero
 */

int hashSetIsEmpty(HashSet *hashSet) {

    if (hashSet == NULL) {
#ifdef C_DATASTRUCTURES_ERRORSTESTSTRUCT_H
        ERROR_TEST->errorCode = NULL_POINTER;
        return -1;
#else
        fprintf(stderr, NULL_POINTER_MESSAGE, "hash set", "hash set data structure");
        exit(NULL_POINTER);
#endif

    }

    return hashSet->count == 0;
}


/** This function will take the hash set address as a parameter,
 * then it will clear and free all the items in the hash set,
 * without destroying the hash set.
 *
 * @param hashSet the hash set address
 */

void clearHashSet(HashSet *hashSet) {

    if (hashSet == NULL) {
#ifdef C_DATASTRUCTURES_ERRORSTESTSTRUCT_H
        ERROR_TEST->errorCode = NULL_POINTER;
        return;
#else
        fprintf(stderr, NULL_POINTER_MESSAGE, "hash set", "hash set data structure");
        exit(NULL_POINTER);
#endif

    }

    for (int i = 0; i < hashSet->length; i++) {
        if (hashSet->arr[i] != NULL) {
            hashSet->freeItem(hashSet->arr[i]);
            hashSet->arr[i] = NULL;
        }

    }

    hashSet->count = 0;

}


/** This function will take the hash set address as a parameter,
 * then it will destroy and free the hash set and all it's items.
 *
 * @param hashSet the hash set address
 */

void destroyHashSet(void *hashSet) {

    if (hashSet == NULL) {
#ifdef C_DATASTRUCTURES_ERRORSTESTSTRUCT_H
        ERROR_TEST->errorCode = NULL_POINTER;
        return;
#else
        fprintf(stderr, NULL_POINTER_MESSAGE, "hash set", "hash set data structure");
        exit(NULL_POINTER);
#endif

    }

    clearHashSet(hashSet);

    free(((HashSet *) hashSet)->arr);
    free(hashSet);

}


/** This function will take the hash function pointer, the key pointer, and the hash set array length as a parameters,
 * then it will return the first hash of this key.
 *
 * Note: this function should only be called from the hash set functions.
 *
 * @param hashFun the hash function pointer
 * @param key the key pointer
 * @param length the length of the hash set array
 * @return it will return the first hashed key
 */

unsigned int hashSetFHashCal(int (*hashFun)(const void *), void *key, unsigned int length) {
    return (hashFun(key) % length);
}


/** This function will take the hash function pointer, the key address, and the biggest prime number,
 * that smaller than the set array length as a parameters, then it will return the second hash of this key.
 *
 * Note: this function should only be called from the hash set functions.
 *
 * @param hashFun the hash function pointer
 * @param key the key pointer
 * @param bPrime the biggest prime number, that smaller than the set array length
 * @return it will return the second hashed key
 */

unsigned int hashSetSHashCal(int (*hashFun)(const void *), void *key, unsigned int bPrime) {
    return (bPrime - (hashFun(key) % bPrime));
}


/** This function will take the first hash of the key, the second hash of the key, the index, and the length of the hash set array
 * as a parameters, then it will return the next index that should be available.
 *
 * Note: this function should only be called from the hash set functions.
 *
 * @param fHash the first hashed key
 * @param sHash the second hashed key
 * @param index the current index that wasn't empty
 * @param length the length if the hash set array
 * @return it will return the new index that should be empty
 */

unsigned int hashSetCalIndex(unsigned int fHash, unsigned int sHash, unsigned int index, unsigned int length) {
    return ((fHash + (index * sHash)) % length);
}


/** This function will take the length of the hash set array as a parameter,
 * then it will return the biggest prime number that is smaller than the length.
 * @param length the length of the hash set array
 * @return it will return the biggest prime number that is smaller than the length
 */

int hashSetCalBPrime(int length) {
    for (int i = length - 1; i >= 1; i--) {
        for (int j = i / 2; j > 1; j--) {
            if (i % j == 0)
                break;
            else if (i % j != 0 && j == 2)
                return i;

        }
    }

    return 1;

}


/** This function will take an integer number as a parameter,
 * then it will return the next prime number that bigger than or equal to the passed parameter,
 * other wise it will return 1 if the function didn't found any prime numbers.
 *
 * @param num the number that the function will start from it to check for the prime numbers.
 * @return it will return the first prime number that is bigger or equal to the provided parameter,
 * and if the didn't find any prime number the function will return one (1)
 */

int hashSetGetNextPrime(int num) {
    for (int i = num; i <= INT_MAX; i++) {
        for (int j = i / 2; j > 1; j--) {

            if (i % j == 0)
                break;
            else if (j == 2 && i % j != 0)
                return i;

        }

    }

    return 1;

}

