#ifndef C_DATASTRUCTURES_LINKEDLISTHASHMAP_H
#define C_DATASTRUCTURES_LINKEDLISTHASHMAP_H


#include "DoublyLinkedList.h"


typedef struct LLHashMapItem {
    void *value;
    int sizeOfItem;
} LLHashMapItem;

typedef struct Entry{
    void *key;
    LLHashMapItem *item;
    int sizeOfKey;
} Entry;

typedef struct LinkedListHashMap {
    DoublyLinkedList **arr;
    int length;
    int count;
} LinkedListHashMap;


LinkedListHashMap *linkedListHashMapInitialization(int mapLength, void (*freeKey)(void *key), void (*freeItem)(void *item), int (*keyComp)(const void *key1, int s1, const void *key2, int s2));


void lLHashMapInsert(LinkedListHashMap *map, void *key, int sizeOfKey, void *item, int sizeOfItem);


int lLHashMapContains(LinkedListHashMap *map, void *key, int sizeOfKey);


void *lLHashMapGet(LinkedListHashMap *map, void *key, int sizeOfKey);


void lLHashMapDelete(LinkedListHashMap *map, void *key, int sizeOfKey);


void **lLHashMapToArray(LinkedListHashMap *map);


Entry **lLHashMapToEntryArray(LinkedListHashMap *map);


int lLHashMapGetLength(LinkedListHashMap *map);


int lLHashMapIsEmpty(LinkedListHashMap *map);


void clearLLHashMap(LinkedListHashMap *map);


void destroyLLHashMap(LinkedListHashMap *map);


#endif //C_DATASTRUCTURES_LINKEDLISTHASHMAP_H
