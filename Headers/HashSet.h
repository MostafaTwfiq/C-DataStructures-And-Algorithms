#ifndef C_DATASTRUCTURES_HASHSET_H
#define C_DATASTRUCTURES_HASHSET_H




#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>



typedef struct HashSet {
    void **arr;
    int length;
    int count;
    int sizeOfType;
    int bPrime;

} HashSet;



HashSet *hashSetInitialization(int sizeOfType);


void hashSetInsert(HashSet *hashSet, void *item);


void hashSetDelete(HashSet *hashSet, void *item);


int hashSetContains(HashSet *hashSet, void *item);


void **hashSetToArray(HashSet *hashSet);


int hashSetGetLength(HashSet *hashSet);


int hashSetIsEmpty(HashSet *hashSet);


void clearHashSet(HashSet *hashSet);


void destroyHashSet(HashSet *hashSet);



#endif //C_DATASTRUCTURES_HASHSET_H
