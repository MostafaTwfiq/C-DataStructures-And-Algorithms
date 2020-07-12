#ifndef C_DATASTRUCTURES_ARRAYLIST_H
#define C_DATASTRUCTURES_ARRAYLIST_H

#include "Utils.h"
#include "math.h"



typedef struct ArrayListItem {
    void *value;
    int sizeOfItem;
} ArrayListItem;


typedef struct ArrayList {
    ArrayListItem **arr;
    int length;
    int count;
    void (*freeItem)(void *);
} ArrayList;



ArrayList *arrayListInitialization(int initialLength, void (*freeFun)(void *));


void arrayListAdd(ArrayList *list, void *item, int sizeOfItem);


void arrayListAddAll(ArrayList *list, void **array, int arrayLength, int sizeOfItem);


void arrayListRemove(ArrayList *list);


void arrayListRemoveAtIndex(ArrayList *list, int index);


int arrayListContains(ArrayList *list, void *item, int (*comparator)(const void *, const void *));


int arrayListGetIndex(ArrayList *list, void *item, int (*comparator)(const void *, const void *));


int arrayListGetLastIndex(ArrayList *list, void *item, int (*comparator)(const void *, const void *));


void *arrayListGet(ArrayList *list, int index);


void **arrayListToArray(ArrayList *list);


void **arrayListToSubArray(ArrayList *list, int start, int end);


void arrayListSort(ArrayList *list, int (*comparator)(const void *, const void *));


int arrayListGetLength(ArrayList *list);


int arrayListIsEmpty(ArrayList *list);


void printArrayList(ArrayList *list, void (*printFun) (const void *));


void clearArrayList(ArrayList *list);


void destroyArrayList(ArrayList *list);


#endif //C_DATASTRUCTURES_ARRAYLIST_H
