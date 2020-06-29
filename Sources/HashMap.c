#include "../Headers/HashMap.h"
#include "limits.h"
#include <string.h>





unsigned int fHashCal(unsigned int address, unsigned int sizeOfKey, unsigned int length);


unsigned int sHashCal(unsigned int address, unsigned int sizeOfKey, unsigned int bPrime);


unsigned int calIndex(unsigned int fHash, unsigned int sHash, unsigned int index, unsigned int length);


int calBPrime(int length);


int getNextPrime(int num);







/** This function will take the size of the stored data type in the map as a parameter,
   then it will initialize a new hash map,
   then the function will return the address of the hash map.
 * @param sizeOfType
 * @return
 */

HashMap *hashMapInitialization(int sizeOfType) {
    HashMap *map = (HashMap *) malloc(sizeof(HashMap));

    map->length = getNextPrime(10); //the length of the map array should always be a prime number.
    map->arr = (Entry **) calloc(sizeof(Entry *), map->length);
    map->count = 0;
    map->sizeOfType = sizeOfType;
    map->bPrime = calBPrime(map->length);

    return map;

}





/** This function will take the map address, the key address, the item address, and the size of the key in bytes,
    as a parameters, then it will insert the item in the map.
 * Note: if the key is already in the map then the map will override the data and free the old item and it's key.
 * @param map
 * @param key
 * @param item
 * @param sizeOfKey
 */

void hashMapInsert(HashMap *map, void *key, void *item, int sizeOfKey) {
    if (map->count == map->length) {
        map->length = getNextPrime(map->length * 2); //the length of the map array should always be a prime number.
        map->arr = (Entry **) malloc(sizeof(Entry *) * map->length);
        map->bPrime = calBPrime(map->length);
    }

    unsigned int fHash, sHash = sHashCal( (unsigned int) key, sizeOfKey, map->bPrime);
    unsigned int index = fHash = fHashCal( (unsigned int) key, sizeOfKey, map->length);
    while (map->arr[index] != NULL) {

        if (sizeOfKey == map->arr[index]->sizeOfKey && memcmp(map->arr[index]->key, key, sizeOfKey) == 0) {
            free(map->arr[index]->value);
            free(map->arr[index]->key);
            map->arr[index]->key = key;
            map->arr[index]->value = item;
            return;
        }

        index = calIndex(fHash, sHash, index + 1, map->length);
    }

    Entry *newEntry = (Entry *) malloc(sizeof(Entry));
    newEntry->key = key;
    newEntry->sizeOfKey = sizeOfKey;
    newEntry->value = item;
    map->arr[index] = newEntry;
    map->count++;

}






/** This function will take the map address, the key address, and the key size as a parameters,
    then it will return (1) if the key is in the map,
    other wise it will return zero (0).
 * @param map
 * @param key
 * @param sizeOfKey
 * @return
 */

int hashMapContains(HashMap *map, void *key, int sizeOfKey) {
    unsigned int fHash, sHash = sHashCal( (unsigned int) key, sizeOfKey, map->bPrime);
    unsigned int index = fHash = fHashCal( (unsigned int) key, sizeOfKey, map->length);
    unsigned int firstIndex = index;
    do {

        if (map->arr[index] != NULL) {
            if (sizeOfKey == map->arr[index]->sizeOfKey && memcmp(map->arr[index]->key, key, sizeOfKey) == 0)
                return 1;

        }

        index = calIndex(fHash, sHash, index + 1, map->length);

    } while (firstIndex != index);

    return 0;

}





/** This function will take the map address, the key address, and the key size as a parameter,
    then it will return the item address if the key existed,
    other wise it will return NULL.
 * @param map
 * @param key
 * @param sizeOfKey
 * @return
 */

void *hashMapGet(HashMap *map, void *key, int sizeOfKey) {
    unsigned int fHash, sHash = sHashCal( (unsigned int) key, sizeOfKey, map->bPrime);
    unsigned int index = fHash = fHashCal( (unsigned int) key, sizeOfKey, map->length);
    unsigned int firstIndex = index;
    do {

        if (map->arr[index] != NULL) {
            if (sizeOfKey == map->arr[index]->sizeOfKey && memcmp(map->arr[index]->key, key, sizeOfKey) == 0)
                return map->arr[index]->value;

        }

        index = calIndex(fHash, sHash, index + 1, map->length);

    } while (firstIndex != index);

    return NULL;

}






/** This function will take the map address, the key address, and the size of the key as a parameters,
    then it will delete and free the key and the item that linked to the key.
 * @param map
 * @param key
 * @param sizeOfKey
 */

void hashMapDelete(HashMap *map, void *key, int sizeOfKey) {
    unsigned int fHash, sHash = sHashCal( (unsigned int) key, sizeOfKey, map->bPrime);
    unsigned int index = fHash = fHashCal( (unsigned int) key, sizeOfKey, map->length);
    unsigned int firstIndex = index;
    do {

        if (map->arr[index] != NULL) {
            if (sizeOfKey == map->arr[index]->sizeOfKey && memcmp(map->arr[index]->key, key, sizeOfKey) == 0) {
                free(map->arr[index]->value);
                free(map->arr[index]->key);
                free(map->arr[index]);
                map->arr[index] = NULL;
                map->count--;
                return;
            }

        }

        index = calIndex(fHash, sHash, index + 1, map->length);

    } while (firstIndex != index);

}






/** This function will take the map address as a parameter,
    then it will return double void pointer that has a copy of all the items in the map.
 * @param map
 * @return
 */

void *hashMapToArray(HashMap *map) {
    void **arr = (void *) malloc(sizeof(void *) * map->count);
    for (int i = 0, index = 0; i < map->length; i++) {
        if (map->arr[i] != NULL) {
            arr[index] = (void *) malloc(sizeof(map->sizeOfType));
            memcpy(arr[index], map->arr[i]->value, map->sizeOfType);
            index++;
        }
    }

    return arr;

}



/** This function will take the map address as a parameter,
    then it will return an entry array that contains a copy of all the items and it's key in the map.
 * @param map
 * @return
 */

Entry *hashMapToEntryArray(HashMap *map) {
    Entry *arr = (Entry *) malloc(sizeof(Entry) * map->count);
    for (int i = 0, index = 0; i < map->length; i++) {
        if (map->arr[i] != NULL) {
            arr[index].sizeOfKey = map->arr[i]->sizeOfKey;
            arr[index].key = (void *) malloc(map->arr[i]->sizeOfKey);
            arr[index].value = (void *) malloc(map->sizeOfType);
            memcpy(arr[index].key, map->arr[i]->key, map->arr[i]->sizeOfKey);
            memcpy(arr[index].value, map->arr[i]->value, map->sizeOfType);
            index++;
        }
    }

    return arr;

}




/** This function will take the map address as a parameter,
    then it will return the number of items in the map.
 * @param map
 * @return
 */

int hashMapGetLength(HashMap *map) {
    return map->count;
}





/** This function will take the map address as a parameter,
    then it will return one (1) if the map is empty,
    other wise it will return zero (0).
 * @param map
 * @return
 */

int hashMapIsEmpty(HashMap *map) {
    return map->count == 0;
}





/** This function will take the map address as a parameter,
 * then it will clear and free all the items and it's key from the map without freeing the map.
 * @param map
 */

void clearHashMap(HashMap *map) {
    for (int i = 0; i < map->count; i++) {
        if (map->arr[i] != NULL) {
            free(map->arr[i]->value);
            free(map->arr[i]->key);
            free(map->arr[i]);
            map->arr[i] = NULL;
        }

    }

    map->count = 0;

}





/** This function will take the map address as a parameter,
    then it will destroy and free the map and all it's entries.
 * @param map
 */

void destroyHashMap(HashMap *map) {
    clearHashMap(map);
    free(map->arr);
    free(map);

}





/** This function will take the key address as an integer, the size of the key and the length of the map,
    as a parameters, then it will return the first hash of this key.
 * Note: this function should only be called from the hash map functions.
 * @param address
 * @param sizeOfKey
 * @param length
 * @return
 */

unsigned int fHashCal(unsigned int address, unsigned int sizeOfKey, unsigned int length) {
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

unsigned int sHashCal(unsigned int address, unsigned int sizeOfKey, unsigned int bPrime) {
    unsigned int *key = (int *) calloc(sizeof(int), 1);
    memcpy(key, (void *) address, sizeOfKey > 4 ? 4 : sizeOfKey);
    unsigned int hash = (bPrime - (*key % bPrime));
    free(key);
    return hash;

}





/** This function will take the first hash of the key, the second hash of the key, the index, and the length of the map array
    as a parameters, then it will return the next index that should be available.
 * Note: this function should only be called from the hash map functions.
 * @param fHash
 * @param sHash
 * @param index
 * @param length
 * @return
 */

unsigned int calIndex(unsigned int fHash, unsigned int sHash, unsigned int index, unsigned int length) {
    return ((fHash + (index * sHash))  % length);
}




/** This function will take the length of the map array as a parameter,
    then it will return the biggest prime number that is smaller than the length.
 * @param length
 * @return
 */

int calBPrime(int length) {
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
 * @param num
 * @return
 */

int getNextPrime(int num) {
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