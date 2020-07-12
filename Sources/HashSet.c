#include "../Headers/HashSet.h"



int hashSetCalBPrime(int length);

int hashSetGetNextPrime(int num);

unsigned int hashSetFHashCal(unsigned int address, unsigned int sizeOfKey, unsigned int length);

unsigned int hashSetSHashCal(unsigned int address, unsigned int sizeOfKey, unsigned int bPrime);

unsigned int hashSetCalIndex(unsigned int fHash, unsigned int sHash, unsigned int index, unsigned int length);







/** This function will take the size of the hash set elements type as a parameter,
 * then it will return a new hash set address.
 * @param sizeOfType size of the type, that the hash set will hold
 * @return it will return a new hash set pointer
 */

HashSet *hashSetInitialization(int sizeOfType) {
    HashSet *hashSet = (HashSet *) malloc(sizeof(HashSet));

    hashSet->length = hashSetGetNextPrime(10);
    hashSet->arr = (void **) calloc(sizeof(void *), hashSet->length);
    hashSet->count = 0;
    hashSet->sizeOfType = sizeOfType;
    hashSet->bPrime = hashSetCalBPrime(hashSet->length);

    return hashSet;

}









/** This function will take the hash set address, and the new item address as a parameters,
 * then it will insert the provided item into the hash set.
 * Note: the hash set will hold the provided item address (it will not copy the item data into the hash set).
 * @param hashSet the hash set address
 * @param item the new item address
 */

void hashSetInsert(HashSet *hashSet, void *item) {

    if (hashSet == NULL) {
        fprintf(stderr, "Illegal argument, the hash set is null.");
        exit(-3);
    }

    if (hashSet->count == hashSet->length) {
        hashSet->length *= 2;
        hashSet->length = hashSetGetNextPrime(hashSet->length);
        hashSet->bPrime = hashSetCalBPrime(hashSet->length);
        hashSet->arr = (void **) realloc(hashSet->arr, sizeof(void *) * hashSet->length);
    }


    unsigned int fHash, sHash = hashSetSHashCal( (unsigned int) item, hashSet->sizeOfType, hashSet->bPrime);
    unsigned int index = fHash = hashSetFHashCal( (unsigned int) item, hashSet->sizeOfType, hashSet->length);
    while (hashSet->arr[index] != NULL) {

        if (memcmp(hashSet->arr[index], item, hashSet->sizeOfType) == 0) {
            free(hashSet->arr[index]);
            hashSet->arr[index] = item;
            return;
        }

        index = hashSetCalIndex(fHash, sHash, index + 1, hashSet->length);
    }

    hashSet->arr[index] = item;
    hashSet->count++;

}









/** This function will take the hash set address, and the item address as a parameters,
 * then it will delete the provided item from the hash set.
 * Note: the function will memory compare the provided item with the items in the hash set.
 * Note: if the item was found in the hash set, then the function will free the item in the hash set,
 * without freeing the provided one in the parameters.
 * @param hashSet the hash set address
 * @param item the item address that hash the same data as the item that will be deleted
 */

void hashSetDelete(HashSet *hashSet, void *item) {
    if (hashSet == NULL) {
        fprintf(stderr, "Illegal argument, the hash set is null.");
        exit(-3);
    } else if (item == NULL) {
        fprintf(stderr, "Illegal argument, the passed item is null.");
        exit(-3);
    }

    unsigned int fHash, sHash = hashSetSHashCal( (unsigned int) item, hashSet->sizeOfType, hashSet->bPrime);
    unsigned int index = fHash = hashSetFHashCal( (unsigned int) item, hashSet->sizeOfType, hashSet->length);
    unsigned int firstIndex = index;
    do {

        if (hashSet->arr[index] != NULL) {
            if (memcmp(hashSet->arr[index], item, hashSet->sizeOfType) == 0) {
                free(hashSet->arr[index]);
                hashSet->arr[index] = NULL;
                hashSet->count--;
                return;
            }

        }

        index = hashSetCalIndex(fHash, sHash, index + 1, hashSet->length);

    } while (firstIndex != index);

}









/** This function will take the hash set address, and the item address as a parameters,
 * then it will return one (1) if the provided item is in the hash set,
 * other wise it will return zero (0).
 * Note: the provided item should has the same data as the one that will be searched for,
 * because the function will memory compare the provided item and the hash set items.
 * @param hashSet the hash set address
 * @param item the item address that has the same data as the one that you are searching for.
 * @return
 */

int hashSetContains(HashSet *hashSet, void *item) {
    if (hashSet == NULL) {
        fprintf(stderr, "Illegal argument, the hash set is null.");
        exit(-3);
    } else if (item == NULL) {
        fprintf(stderr, "Illegal argument, the passed item is null.");
        exit(-3);
    }

    unsigned int fHash, sHash = hashSetSHashCal( (unsigned int) item, hashSet->sizeOfType, hashSet->bPrime);
    unsigned int index = fHash = hashSetFHashCal( (unsigned int) item, hashSet->sizeOfType, hashSet->length);
    unsigned int firstIndex = index;
    do {

        if (hashSet->arr[index] != NULL) {
            if (memcmp(hashSet->arr[index], item, hashSet->sizeOfType) == 0)
                return 1;

        }

        index = hashSetCalIndex(fHash, sHash, index + 1, hashSet->length);

    } while (firstIndex != index);

    return 0;
}









/** This function will take the hash set address as a parameter,
 * then it will return a double void pointer array that hash a copy of all items in the hash set.
 * @param hashSet the address of the hash set
 * @return it will return a double void array that is a copy of the hash set items
 */

void **hashSetToArray(HashSet *hashSet) {
    if (hashSet == NULL) {
        fprintf(stderr, "Illegal argument, the hash set is null.");
        exit(-3);
    }

    void **array = (void **) malloc(sizeof(void *) * hashSetGetLength(hashSet));
    for (int i = 0, index = 0; i < hashSet->length; i++) {
        if (hashSet->arr[i] != NULL) {
            array[index] = (void *) malloc(hashSet->sizeOfType);
            memcpy(array[index], hashSet->arr[i], hashSet->sizeOfType);
            index++;
        }

    }

    return array;

}





/** This function will take the hash set address as a parameter,
 * then it will return the number of items in the hash set.
 * @param hashSet the hash set address
 * @return it will return the number of items in the hash set
 */

int hashSetGetLength(HashSet *hashSet) {

    if (hashSet == NULL) {
        fprintf(stderr, "Illegal argument, the hash set is null.");
        exit(-3);
    }

    return hashSet->count;
}








/** This function will take the hash set address as a parameter,
 * then it will return one (1) if the hash set is empty,
 * other wise it will return zero (0).
 * @param hashSet the hash set address
 * @return it will return one if the hash set is empty, other wise it will return zero
 */

int hashSetIsEmpty(HashSet *hashSet) {

    if (hashSet == NULL) {
        fprintf(stderr, "Illegal argument, the hash set is null.");
        exit(-3);
    }

    return hashSet->count == 0;
}









/** This function will take the hash set address as a parameter,
 * then it will clear and free all the items in the hash set,
 * without destroying the hash set.
 * @param hashSet the hash set address
 */

void clearHashSet(HashSet *hashSet) {

    if (hashSet == NULL) {
        fprintf(stderr, "Illegal argument, the hash set is null.");
        exit(-3);
    }

    for (int i = 0; i < hashSet->length; i++) {
        if (hashSet->arr[i] != NULL) {
            free(hashSet->arr[i]);
            hashSet->arr[i] = NULL;
        }

    }

    hashSet->count = 0;

}








/** This function will take the hash set address as a parameter,
 * then it will destroy and free the hash set and all it's items.
 * @param hashSet the hash set address
 */

void destroyHashSet(HashSet *hashSet) {
    clearHashSet(hashSet);

    free(hashSet->arr);
    free(hashSet);

}








/** This function will take the key address as an integer, the size of the key and the length of the hash set,
    as a parameters, then it will return the first hash of this key.
 * Note: this function should only be called from the hash set functions.
 * @param address the address of the item presented as an unsigned integer number
 * @param sizeOfKey the size of the hash set items
 * @param length the length of the hash set array
 * @return it will return the first hashed key
 */

unsigned int hashSetFHashCal(unsigned int address, unsigned int sizeOfKey, unsigned int length) {
    unsigned int *key = (int *) calloc(sizeof(int), 1);
    memcpy(key, (void *) address, sizeOfKey > 4 ? 4 : sizeOfKey);
    unsigned int hash = (*key % length);
    free(key);
    return hash;
}








/** This function will take the key address as an integer, the size of the key and the biggest prime number,
    that smaller than the map array length as a parameters, then it will return the second hash of this key.
 * Note: this function should only be called from the hash map functions.
 * @param address
 * @param sizeOfKey
 * @param length
 * @return
 */

unsigned int hashSetSHashCal(unsigned int address, unsigned int sizeOfKey, unsigned int bPrime) {
    unsigned int *key = (int *) calloc(sizeof(int), 1);
    memcpy(key, (void *) address, sizeOfKey > 4 ? 4 : sizeOfKey);
    unsigned int hash = (bPrime - (*key % bPrime));
    free(key);
    return hash;

}








/** This function will take the first hash of the key, the second hash of the key, the index, and the length of the hash set array
    as a parameters, then it will return the next index that should be available.
 * Note: this function should only be called from the hash set functions.
 * @param fHash the first hashed key
 * @param sHash the second hashed key
 * @param index the current index that wasn't empty
 * @param length the length if the hash set array
 * @return it will return the new index that should be empty
 */

unsigned int hashSetCalIndex(unsigned int fHash, unsigned int sHash, unsigned int index, unsigned int length) {
    return ((fHash + (index * sHash))  % length);
}









/** This function will take the length of the hash set array as a parameter,
    then it will return the biggest prime number that is smaller than the length.
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
    then it will return the next prime number that bigger than or equal to the passed parameter,
    other wise it will return 1 if the function didn't found any prime numbers.
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


