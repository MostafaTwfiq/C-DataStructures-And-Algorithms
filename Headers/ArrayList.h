#ifndef C_DATASTRUCTURES_ARRAYLIST_H
#define C_DATASTRUCTURES_ARRAYLIST_H
#include "Utils.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef struct ArrayList {
    void **arr;
    int length;
    int count;
    void (*freeItem)(void *);
    int (*comparator)(const void *, const void *);
} ArrayList;


ArrayList *
arrayListInitialization(int initialLength, void (*freeFun)(void *), int (*comparator)(const void *, const void *));

void arrayListAdd(ArrayList *list, void *item);

void arrayListAddAll(ArrayList *list, void **array, int arrayLength);

void arrayListRemove(ArrayList *list);

void arrayListRemoveWtFr(ArrayList *list);

void arrayListRemoveAtIndex(ArrayList *list, int index);

void arrayListRemoveAtIndexWtFr(ArrayList *list, int index);

int arrayListContains(ArrayList *list, void *item);

int arrayListGetIndex(ArrayList *list, void *item);

int arrayListGetLastIndex(ArrayList *list, void *item);

void *arrayListGet(ArrayList *list, int index);

void **arrayListToArray(ArrayList *list);

void **arrayListToSubArray(ArrayList *list, int start, int end);

void arrayListSort(ArrayList *list);

int arrayListGetLength(ArrayList *list);

int arrayListIsEmpty(ArrayList *list);

void printArrayList(ArrayList *list, void (*printFun)(const void *));

void clearArrayList(ArrayList *list);

void destroyArrayList(ArrayList *list);

#ifdef __cplusplus
}
#endif

#endif //C_DATASTRUCTURES_ARRAYLIST_H
