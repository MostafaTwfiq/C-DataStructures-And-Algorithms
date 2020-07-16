#ifndef C_DATASTRUCTURES_HASHMAP_H
#define C_DATASTRUCTURES_HASHMAP_H

#include <stdio.h>
#include <stdlib.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef struct Entry {
    void *key;
    void *item;
    void (*freeItemFun)(void *);
    void (*freeKeyFun)(void *);
} Entry;

typedef struct HashMap {
    Entry **arr;
    int length;
    int count;
    int bPrime;
    void (*freeItemFun)(void *);
    void (*freeKeyFun)(void *);
    int (*keyComp)(const void *, const void *);
} HashMap;

HashMap *hashMapInitialization(void (*freeKey)(void *), void (*freeItem)(void *), int (*keyComp)(const void *, const void *));

void hashMapInsert(HashMap *map, void *key, int sizeOfKey, void *item);

int hashMapContains(HashMap *map, void *key, int sizeOfKey);

void *hashMapGet(HashMap *map, void *key, int sizeOfKey);

void hashMapDelete(HashMap *map, void *key, int sizeOfKey);

void *hashMapDeleteWtoFr(HashMap *map, void *key, int sizeOfKey);

void **hashMapToArray(HashMap *map);

Entry **hashMapToEntryArray(HashMap *map);

int hashMapGetLength(HashMap *map);

int hashMapIsEmpty(HashMap *map);

void clearHashMap(HashMap *map);

void destroyHashMap(HashMap *map);

#ifdef __cplusplus
}
#endif

#endif //C_DATASTRUCTURES_HASHMAP_H
