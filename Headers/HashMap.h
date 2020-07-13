#ifndef C_DATASTRUCTURES_HASHMAP_H
#define C_DATASTRUCTURES_HASHMAP_H


#include <stdio.h>
#include <stdlib.h>


typedef struct Entry{
    void *key;
    void *item;
    int sizeOfKey;
} Entry;



typedef struct HashMap {
    Entry **arr;
    int length;
    int count;
    int sizeOfType;
    int bPrime;
} HashMap;



HashMap *hashMapInitialization(int sizeOfType);


void hashMapInsert(HashMap *map, void *key, void *item, int sizeOfKey);


int hashMapContains(HashMap *map, void *key, int sizeOfKey);


void *hashMapGet(HashMap *map, void *key, int sizeOfKey);


void hashMapDelete(HashMap *map, void *key, int sizeOfKey);


void **hashMapToArray(HashMap *map);


Entry **hashMapToEntryArray(HashMap *map);


int hashMapGetLength(HashMap *map);


int hashMapIsEmpty(HashMap *map);


void clearHashMap(HashMap *map);


void destroyHashMap(HashMap *map);


#endif //C_DATASTRUCTURES_HASHMAP_H
