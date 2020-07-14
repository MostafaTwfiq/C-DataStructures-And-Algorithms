#ifndef C_DATASTRUCTURES_VECTOR_H
#define C_DATASTRUCTURES_VECTOR_H


#include "math.h"
#include "Utils.h"


typedef struct VectorItem {
    void *value;
    int sizeOfItem;
} VectorItem;

typedef struct Vector {
    VectorItem **arr;
    int length;
    int count;
    void (*freeItem)(void *);
} Vector;



Vector *vectorInitialization(int initialLength, void (*freeFun)(void *));


void vectorAdd(Vector *list, void *item, int sizeOfItem);


void vectorAddAll(Vector *list, void **array, int arrayLength, int sizeOfItem);


void vectorRemove(Vector *list);


void vectorRemoveWtFr(Vector *list);


void vectorRemoveAtIndex(Vector *list, int index);


void vectorRemoveAtIndexWtFr(Vector *list, int index);


int vectorContains(Vector *list, void *item, int (*comparator)(const void *, const void *));


int vectorGetIndex(Vector *list, void *item, int (*comparator)(const void *, const void *));


int vectorGetLastIndex(Vector *list, void *item, int (*comparator)(const void *, const void *));


void *vectorGet(Vector *list, int index);


void **vectorToArray(Vector *list);


void **vectorToSubArray(Vector *list, int start, int end);


void vectorSort(Vector *list, int (*comparator)(const void *, const void *));


int vectorGetLength(Vector *list);


int vectorIsEmpty(Vector *list);


void printVector(Vector *list, void (*printFun) (const void *));


void clearVector(Vector *list);


void destroyVector(Vector *list);


#endif //C_DATASTRUCTURES_VECTOR_H
