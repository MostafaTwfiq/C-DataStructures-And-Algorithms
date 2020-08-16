#ifndef C_DATASTRUCTURES_HASHSET_H
#define C_DATASTRUCTURES_HASHSET_H


#ifdef __cplusplus
extern "C" {
#endif


/** @struct HashSet
*  @brief This structure implements a basic generic hashset.
*  @var HashSet::arr
*  Member 'arr' is a pointer to the Hashset array.
*  @var HashSet::length
*  Member 'length' holds the size of the allocated array.
*  @var HashSet::count
*  Member 'count' holds the current number of items in the Hashset.
*  @var HashSet::bPrime
*  Member 'bPrime' holds the biggest prime number that is smaller than the length of the Hashset array.
*  @var HashSet::freeItem
*  Member 'freeItem' is a pointer to the item freeing function, that frees the Hashset items.
*  @var HashSet::itemComp
*  Member 'itemComp' is a pointer to the item comparator function, that compare the Hashset items.
*  @var HashSet::hashFun
*  Member 'hashFun' is a pointer to the hashing function, that returns an unique number representing the Hashset item.
*/

typedef struct HashSet {
    void **arr;
    int length;
    int count;
    int bPrime;

    void (*freeItem)(void *);

    int (*itemComp)(const void *, const void *);

    int (*hashFun)(const void *);
} HashSet;


HashSet *hashSetInitialization(void (*freeItem)(void *), int (*itemComp)(const void *, const void *),
                               int (*hashFun)(const void *));

void hashSetInsert(HashSet *hashSet, void *item);

void hashSetDelete(HashSet *hashSet, void *item);

void *hashSetDeleteWtoFr(HashSet *hashSet, void *item);

int hashSetContains(HashSet *hashSet, void *item);

void *hashSetGet(HashSet *hashSet, void *item);

void **hashSetToArray(HashSet *hashSet);

int hashSetGetLength(HashSet *hashSet);

int hashSetIsEmpty(HashSet *hashSet);

void clearHashSet(HashSet *hashSet);

void destroyHashSet(void *hashSet);

#ifdef __cplusplus
}
#endif

#endif //C_DATASTRUCTURES_HASHSET_H
