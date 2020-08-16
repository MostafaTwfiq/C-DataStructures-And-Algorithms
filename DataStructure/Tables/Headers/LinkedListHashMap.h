#ifndef C_DATASTRUCTURES_LINKEDLISTHASHMAP_H
#define C_DATASTRUCTURES_LINKEDLISTHASHMAP_H

#ifdef __cplusplus
extern "C" {
#endif


/** @struct Entry
*  @brief This structure implements a basic hashmap entry.
*  @var Entry::key
*  Member 'key' is a pointer to the entry key.
*  @var Entry::item
*  Member 'item' is a pointer to the entry item.
*  @var Entry::freeItemFun
*  Member 'freeItemFun' is a pointer to the item freeing function, that frees the item.
*  @var Entry::freeKeyFun
*  Member 'freeKeyFun' is a pointer to the key freeing function, that frees the key.
*/

typedef struct Entry {
    void *key;
    void *item;

    void (*freeKeyFun)(void *);

    void (*freeItemFun)(void *);

    int (*keyCompFun)(const void *, const void *);
} Entry;


/** @struct HashMap
*  @brief This structure implements a basic generic hashmap using doubly linked list.
*  @var HashMap::arr
*  Member 'arr' is a pointer to the doubly linked list hashmap array.
*  @var HashMap::length
*  Member 'length' holds the size of the allocated array.
*  @var HashMap::count
*  Member 'count' holds the current number of items in the hashmap.
*  @var HashMap::freeItemFun
*  Member 'freeItemFun' is a pointer to the item freeing function, that frees the hashmap items.
*  @var HashMap::freeKeyFun
*  Member 'freeKeyFun' is a pointer to the key freeing function, that frees the hashmap key.
*  @var HashMap::keyCompFun
*  Member 'keyCompFun' is a pointer to the key comparator function, that compare the hashmap keys.
*  @var HashMap::hashFun
*  Member 'hashFun' is a pointer to the hashing function, that returns an unique number representing the hashmap item.
*/

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
linkedListHashMapInitialization(int mapLength, void (*freeKey)(void *), void (*freeItem)(void *),
                                int (*keyComp)(const void *, const void *), int (*hashFun)(const void *));

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

void destroyLLHashMap(void *map);

#ifdef __cplusplus
}
#endif

#endif //C_DATASTRUCTURES_LINKEDLISTHASHMAP_H
