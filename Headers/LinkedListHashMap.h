#ifndef C_DATASTRUCTURES_LINKEDLISTHASHMAP_H
#define C_DATASTRUCTURES_LINKEDLISTHASHMAP_H


typedef struct Entry{
    void *key;
    void *item;
    void (*freeKeyFun)(void *);
    void (*freeItemFun)(void *);
    int (*keyCompFun)(const void *, const void *);
} Entry;

typedef struct LinkedListHashMap {
    struct DoublyLinkedList **arr;
    int length;
    int count;
    void (*freeKeyFun)(void *);
    void (*freeItemFun)(void *);
    int (*keyCompFun)(const void *, const void *);

} LinkedListHashMap;


LinkedListHashMap *linkedListHashMapInitialization(int mapLength, void (*freeKey)(void *key), void (*freeItem)(void *item), int (*keyComp)(const void *key1,  const void *key2));


void lLHashMapInsert(LinkedListHashMap *map, void *key, int sizeOfKey, void *item);


int lLHashMapContains(LinkedListHashMap *map, void *key, int sizeOfKey);


void *lLHashMapGet(LinkedListHashMap *map, void *key, int sizeOfKey);


void lLHashMapDelete(LinkedListHashMap *map, void *key, int sizeOfKey);


void lLHashMapDeleteWtoFr(LinkedListHashMap *map, void *key, int sizeOfKey);


void **lLHashMapToArray(LinkedListHashMap *map);


Entry **lLHashMapToEntryArray(LinkedListHashMap *map);


int lLHashMapGetLength(LinkedListHashMap *map);


int lLHashMapIsEmpty(LinkedListHashMap *map);


void clearLLHashMap(LinkedListHashMap *map);


void destroyLLHashMap(LinkedListHashMap *map);


#endif //C_DATASTRUCTURES_LINKEDLISTHASHMAP_H
