#ifndef C_DATASTRUCTURES_HASHMAP_H
#define C_DATASTRUCTURES_HASHMAP_H

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

    void (*freeItemFun)(void *);

    void (*freeKeyFun)(void *);
} Entry;


/** @struct HashMap
*  @brief This structure implements a basic generic hashmap.
*  @var HashMap::arr
*  Member 'arr' is a pointer to the hashmap array.
*  @var HashMap::length
*  Member 'length' holds the size of the allocated array.
*  @var HashMap::count
*  Member 'count' holds the current number of items in the hashmap.
*  @var HashMap::bPrime
*  Member 'bPrime' holds the biggest prime number that is smaller than the length of the hashmap array.
*  @var HashMap::freeItemFun
*  Member 'freeItemFun' is a pointer to the item freeing function, that frees the hashmap items.
*  @var HashMap::freeKeyFun
*  Member 'freeKeyFun' is a pointer to the key freeing function, that frees the hashmap key.
*  @var HashMap::keyComp
*  Member 'keyComp' is a pointer to the key comparator function, that compare the hashmap keys.
*  @var HashMap::hashFun
*  Member 'hashFun' is a pointer to the hashing function, that returns an unique number representing the hashmap item.
*/

typedef struct HashMap {
    Entry **arr;
    int length;
    int count;
    int bPrime;

    void (*freeItemFun)(void *);

    void (*freeKeyFun)(void *);

    int (*keyComp)(const void *, const void *);

    int (*hashFun)(const void *);
} HashMap;

HashMap *
hashMapInitialization(void (*freeKey)(void *), void (*freeItem)(void *), int (*keyComp)(const void *, const void *),
                      int (*hashFun)(const void *));

void hashMapInsert(HashMap *map, void *key, void *item);

int hashMapContains(HashMap *map, void *key);

void *hashMapGet(HashMap *map, void *key);

void *hashMapGetKey(HashMap *map, void *key);

void hashMapDelete(HashMap *map, void *key);

void *hashMapDeleteWtoFr(HashMap *map, void *key);

Entry *hashMapDeleteWtoFrAll(HashMap *map, void *key);

void **hashMapToArray(HashMap *map);

Entry **hashMapToEntryArray(HashMap *map);

int hashMapGetLength(HashMap *map);

int hashMapIsEmpty(HashMap *map);

void clearHashMap(HashMap *map);

void destroyHashMap(void *map);

#ifdef __cplusplus
}
#endif

#endif //C_DATASTRUCTURES_HASHMAP_H
