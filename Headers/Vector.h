#ifndef C_DATASTRUCTURES_VECTOR_H
#define C_DATASTRUCTURES_VECTOR_H


#include "Utils.h"


typedef struct Vector {
    void **arr;
    int length;
    int count;
    int sizeOfType;
} Vector;



Vector *vectorListInitialization(int initialLength, int sizeOfType);


void vectorListAdd(Vector *list, void *item);


void vectorAddAll(Vector *list, void *array, int arrayLength);


void vectorRemove(Vector *list);


void vectorRemoveAtIndex(Vector *list, int index);


int vectorContains(Vector *list, void *item, int (*comparator)(const void *, const void *));


int vectorGetIndex(Vector *list, void *item, int (*comparator)(const void *, const void *));


int vectorGetLastIndex(Vector *list, void *item, int (*comparator)(const void *, const void *));


void *vectorGet(Vector *list, int index);


void *vectorToArray(Vector *list);


void *vectorToSubArray(Vector *list, int start, int end);


void vectorSort(Vector *list, int (*comparator)(const void *, const void *));


int vectorGetLength(Vector *list);


int vectorIsEmpty(Vector *list);


void printVector(Vector *list, void (*printFun) (const void *));


void clearVector(Vector *list);


void destroyVector(Vector *list);


#endif //C_DATASTRUCTURES_VECTOR_H
