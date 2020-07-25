#ifndef C_DATASTRUCTURES_HASHSET_H
#define C_DATASTRUCTURES_HASHSET_H


#ifdef __cplusplus
extern "C" {
#endif

typedef struct HashSet {
    void **arr;
    int length;
    int count;
    int bPrime;
    void (*freeItem)(void *);
    int (*itemComp)(const void *, const void *);
    int (*hashFun)(const void *);
} HashSet;


HashSet *hashSetInitialization(void (*freeItem)(void *), int (*itemComp)(const void *, const void *), int (*hashFun)(const void *));

void hashSetInsert(HashSet *hashSet, void *item);

void hashSetDelete(HashSet *hashSet, void *item);

void *hashSetDeleteWtoFr(HashSet *hashSet, void *item);

int hashSetContains(HashSet *hashSet, void *item);

void **hashSetToArray(HashSet *hashSet);

int hashSetGetLength(HashSet *hashSet);

int hashSetIsEmpty(HashSet *hashSet);

void clearHashSet(HashSet *hashSet);

void destroyHashSet(HashSet *hashSet);

#ifdef __cplusplus
}
#endif

#endif //C_DATASTRUCTURES_HASHSET_H
