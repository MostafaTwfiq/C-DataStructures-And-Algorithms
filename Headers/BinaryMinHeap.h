#ifndef C_DATASTRUCTURES_MinHeap_H
#define C_DATASTRUCTURES_MinHeap_H
#include "Utils.h"


#define PARENT(i)      (int) (i - 1)/2
#define LCHILD(i)      (2*i) + 1
#define RCHILD(i)      (2*i+1) + 1
#define HAS_LEFT(h,i)  (LCHILD(i) < h->size)
#define HAS_RIGHT(h,i) (RCHILD(i) < h->size)

/** @struct BinaryMinHeap
 *  @brief This structure implements a basic generic minimum binary heap.
 *  @var BinaryMinHeap::capacity
 *  Member 'capacity' is the total allocated space by the memory of the heap.
 *  @var BinaryMinHeap::size
 *  Member 'size' holds the number of nodes currently present in the heap.
 *  @var BinaryMinHeap::cmp
 *  Member 'cmp' is a pointer to the comparision function that is going to be used throughout the tree.
 */
typedef struct BinaryMinHeap {
    void **  memory;
    uint32_t capacity;
    uint32_t size;
    int32_t  (*cmpFn)(const void* ,const void* );
}BinaryMinHeap;

BinaryMinHeap *MinHeapInitialize(int32_t (*cmp)(const void*, const void*));

void MinHeapInsert(BinaryMinHeap* pMinHeap, void* value);

BinaryMinHeap *MinHeapify(void *arr, uint32_t size,int32_t (*cmp)(const void*, const void*));

void destroyMinHeap(BinaryMinHeap *pMinHeap);

void printMinHeap(BinaryMinHeap *pMinHeap, void (*printfn)(void *));

void MinHeapifyDown(BinaryMinHeap* pMinHeap, int index);

void MinHeapDelete(BinaryMinHeap* pMinHeap, void ** res);

void MinHeapAddAll(BinaryMinHeap *pMinHeap, void **arr, uint32_t size);

void clearMinHeap(BinaryMinHeap * pMinHeap);

#endif //C_DATASTRUCTURES_MinHeap_H

