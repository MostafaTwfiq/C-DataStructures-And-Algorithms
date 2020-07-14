#ifndef C_DATASTRUCTURES_HASHSET_H
#define C_DATASTRUCTURES_HASHSET_H




#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>


typedef struct HashSetItem {
    void *value;
    int sizeOfItem;
} HashSetItem;



typedef struct HashSet {
    HashSetItem **arr;
    int length;
    int count;
    int bPrime;
    void (*freeItem)(void *item);

} HashSet;



HashSet *hashSetInitialization(void (*freeItem)(void *item), int (*itemComp)(const void *item1, int s1, const void *item2, int s2));


void hashSetInsert(HashSet *hashSet, void *item, int sizeOfItem);


void hashSetDelete(HashSet *hashSet, void *item, int sizeOfItem);


int hashSetContains(HashSet *hashSet, void *item, int sizeOfItem);


void **hashSetToArray(HashSet *hashSet);


int hashSetGetLength(HashSet *hashSet);


int hashSetIsEmpty(HashSet *hashSet);


void clearHashSet(HashSet *hashSet);


void destroyHashSet(HashSet *hashSet);



#endif //C_DATASTRUCTURES_HASHSET_H
