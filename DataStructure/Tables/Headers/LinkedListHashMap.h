#ifndef C_DATASTRUCTURES_LINKEDLISTHASHMAP_H
#define C_DATASTRUCTURES_LINKEDLISTHASHMAP_H

#ifdef __cplusplus
extern "C" {
#endif

typedef struct Entry {
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
    int (*hashFun)(const void *);
} LinkedListHashMap;

LinkedListHashMap *
linkedListHashMapInitialization(int mapLength, void (*freeKey)(void *), void (*freeItem)(void *), int (*keyComp)(const void *, const void *), int (*hashFun)(const void *));

void lLHashMapInsert(LinkedListHashMap *map, void *key, void *item);

int lLHashMapContains(LinkedListHashMap *map, void *key);

void *lLHashMapGet(LinkedListHashMap *map, void *key);

void *lLHashMapGetKey(LinkedListHashMap *map, void *key);

void lLHashMapDelete(LinkedListHashMap *map, void *key);

void *lLHashMapDeleteWtoFr(LinkedListHashMap *map, void *key);

Entry *lLHashMapDeleteWtoFrAll(LinkedListHashMap *map, void *key);

void **lLHashMapToArray(LinkedListHashMap *map);

Entry **lLHashMapToEntryArray(LinkedListHashMap *map);

int lLHashMapGetLength(LinkedListHashMap *map);

int lLHashMapIsEmpty(LinkedListHashMap *map);

void clearLLHashMap(LinkedListHashMap *map);

void destroyLLHashMap(LinkedListHashMap *map);

#ifdef __cplusplus
}
#endif

#endif //C_DATASTRUCTURES_LINKEDLISTHASHMAP_H
