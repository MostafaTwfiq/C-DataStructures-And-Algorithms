#ifndef C_DATASTRUCTURES_LINEKDLISTHASHMAP_H
#define C_DATASTRUCTURES_LINEKDLISTHASHMAP_H


#include "DoublyLinkedList.h"


typedef struct Entry{
    void *key;
    void *value;
    int sizeOfKey;
} Entry;

typedef struct LinkedListHashMap {
    DoublyLinkedList **arr;
    int length;
    int count;
    int sizeOfType;
} LinkedListHashMap;


LinkedListHashMap *linkedListHashMapInitialization(int mapLength, int sizeOfType);


        void lLHashMapInsert(LinkedListHashMap *map, void *key, void *item, int sizeOfKey);


int lLHashMapContains(LinkedListHashMap *map, void *key, int sizeOfKey);


void *lLHashMapGet(LinkedListHashMap *map, void *key, int sizeOfKey);


void lLHashMapDelete(LinkedListHashMap *map, void *key, int sizeOfKey);


void **lLHashMapToArray(LinkedListHashMap *map);


Entry **lLHashMapToEntryArray(LinkedListHashMap *map);


int lLHashMapGetLength(LinkedListHashMap *map);


int lLHashMapIsEmpty(LinkedListHashMap *map);


void clearLLHashMap(LinkedListHashMap *map);


void destroyLLHashMap(LinkedListHashMap *map);


#endif //C_DATASTRUCTURES_LINEKDLISTHASHMAP_H
