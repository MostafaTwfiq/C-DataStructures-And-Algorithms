#ifndef C_DATASTRUCTURES_ARRAYLIST_H
#define C_DATASTRUCTURES_ARRAYLIST_H

#include "Utils.h"


typedef struct ArrayList {
    void **arr;
    int length;
    int count;
    int sizeOfType;
} ArrayList;



ArrayList *arrayListInitialization(int initialLength, int sizeOfType);


void arrayListAdd(ArrayList *list, void *item);


void arrayListAddAll(ArrayList *list, void **array, int arrayLength);


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
