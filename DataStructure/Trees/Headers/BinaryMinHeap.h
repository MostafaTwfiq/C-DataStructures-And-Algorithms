#ifndef C_DATASTRUCTURES_MinHeap_H
#define C_DATASTRUCTURES_MinHeap_H
#include "../../../System/Utils.h"


#define PARENT(i)      (int) (i - 1)/2
#define LCHILD(i)      (2*i) + 1
#define RCHILD(i)      (2*i+1) + 1
#define HAS_LEFT(h,i)  (LCHILD(i) < h->size)
#define HAS_RIGHT(h,i) (RCHILD(i) < h->size)

#ifdef __cplusplus
extern "C" {
#endif


/** @struct BinaryMinHeap
 *  @brief This structure implements a basic generic minimum binary heap.
 *  @var BinaryMinHeap::capacity
 *  Member 'capacity' is the total allocated space by the memory of the heap.
 *  @var BinaryMinHeap::size
 *  Member 'size' holds the number of nodes currently present in the heap.
 *  @var BinaryMinHeap::cmp
 *  Member 'cmp' is a pointer to the comparision function that is going to be used throughout the tree.
 *  @var BinaryMinHeap::freeFn
 *  Member 'freeFn' is a pointer to the free function.
 */
typedef struct BinaryMinHeap {
    void **memory;
    uint32_t capacity;
    uint32_t size;
    int32_t (*cmpFn)(const void *, const void *);
    void (*freeFn)(void *);
} BinaryMinHeap;

BinaryMinHeap *MinHeapInitialize(int32_t (*cmp)(const void *, const void *), void (*freeFn)(void *));

void MinHeapInsert(BinaryMinHeap *binaryMinHeap, void *value);

BinaryMinHeap *MinHeapify(void *arr, uint32_t size, int32_t (*cmp)(const void *, const void *));

void MinHeapDestroy(BinaryMinHeap *binaryMinHeap);

void printMinHeap(BinaryMinHeap *binaryMinHeap, void (*printfn)(void *));

void MinHeapifyDown(BinaryMinHeap *binaryMinHeap, int index);

void MinHeapDelete(BinaryMinHeap *binaryMinHeap, void **res);

void MinHeapAddAll(BinaryMinHeap *binaryMinHeap, void **arr, uint32_t size);

void MinHeapClear(BinaryMinHeap *binaryMinHeap);

uint32_t isEqual(BinaryMinHeap *binaryMinHeap,BinaryMinHeap *binaryMinHeap2);

uint32_t BinaryMinHeapContains(BinaryMinHeap * binaryMinHeap, void *item);

#ifdef __cplusplus
}
#endif


#endif //C_DATASTRUCTURES_MinHeap_H

