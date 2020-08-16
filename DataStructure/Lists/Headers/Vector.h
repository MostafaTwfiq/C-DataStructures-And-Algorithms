#ifndef C_DATASTRUCTURES_VECTOR_H
#define C_DATASTRUCTURES_VECTOR_H

#ifdef __cplusplus
extern "C" {
#endif


/** @struct Vector
*  @brief This structure implements a basic generic vector.
*  @var Vector::arr
*  Member 'arr' is a pointer to the vector items.
*  @var Vector::length
*  Member 'length' holds the current allocated length of the vector.
*  @var Vector::count
*  Member 'count' holds the index to a free space to the next item.
*  @var Vector::freeItem
*  Member 'freeItem' the freeing item function pointer
 * @var Vector::comparator
 * Member 'comparator' the items comparator function pointer
*/

typedef struct Vector {
    void **arr;
    int length;
    int count;

    void (*freeItem)(void *);

    int (*comparator)(const void *, const void *);
} Vector;

Vector *vectorInitialization(int initialLength, void (*freeFun)(void *), int (*comparator)(const void *, const void *));

void vectorAdd(Vector *list, void *item);

void vectorAddAtIndex(Vector *list, void *item, int index);

void vectorAddAll(Vector *list, void **array, int arrayLength);

void vectorRemove(Vector *list);

void *vectorRemoveWtFr(Vector *list);

void vectorRemoveAtIndex(Vector *list, int index);

void *vectorRemoveAtIndexWtFr(Vector *list, int index);

int vectorContains(Vector *list, void *item);

int vectorGetIndex(Vector *list, void *item);

int vectorGetLastIndex(Vector *list, void *item);

void *vectorGet(Vector *list, int index);

void **vectorToArray(Vector *list);

void **vectorToSubArray(Vector *list, int start, int end);

void vectorSort(Vector *list, int (*sortComp)(const void *, const void *));

int vectorGetLength(Vector *list);

int vectorIsEmpty(Vector *list);

void printVector(Vector *list, void (*printFun)(const void *));

void clearVector(Vector *list);

void destroyVector(void *list);

#ifdef __cplusplus
}
#endif

#endif //C_DATASTRUCTURES_VECTOR_H
