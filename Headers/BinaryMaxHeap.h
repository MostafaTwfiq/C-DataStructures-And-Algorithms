#ifndef C_DATASTRUCTURES_BINARYMAXHEAP_H
#define C_DATASTRUCTURES_BINARYMAXHEAP_H
#include "Utils.h"

#ifndef C_DATASTRUCTURES_MinHeap_H
    #define PARENT(i)      (int) (i - 1)/2
    #define LCHILD(i)      (2*i) + 1
    #define RCHILD(i)      (2*i+1) + 1
    #define HAS_LEFT(h,i)  (LCHILD(i) < h->size)
    #define HAS_RIGHT(h,i) (RCHILD(i) < h->size)
#endif

/** @struct BinaryMaxHeap
 *  @brief This structure implements a basic generic maximum binary heap.
 *  @var BinaryMaxHeap::capacity
 *  Member 'capacity' is the total allocated space by the memory of the heap.
 *  @var BinaryMaxHeap::size
 *  Member 'size' holds the number of nodes currently present in the heap.
 *  @var BinaryMaxHeap::cmp
 *  Member 'cmp' is a pointer to the comparision function that is going to be used throughout the tree.
 */
typedef struct BinaryMaxHeap{
    void **  memory;
    uint32_t capacity;
    uint32_t size;
    int32_t  (*cmpFn)(const void* ,const void* );
}BinaryMaxHeap;

BinaryMaxHeap *MaxHeapInitialize( int32_t (*cmp)(const void*, const void*));

void MaxHeapInsert(BinaryMaxHeap* h, void* value);

BinaryMaxHeap *MaxHeapify(void **arr, uint32_t size,int32_t (*cmp)(const void*, const void*));

void printMaxHeap(BinaryMaxHeap *h, void (*printfn)(void *));

void MaxHeapifyDown(BinaryMaxHeap* h, int index);

void MaxHeapPrint(BinaryMaxHeap *MaxHeap, int i, void (*printfn)(void *));

void MaxHeapDelete(BinaryMaxHeap* heap, void ** res);

void clearMaxHeap(BinaryMaxHeap * pMaxHeap);

void  MaxHeapAddAll(BinaryMaxHeap *binaryMaxHeap,void **arr, uint32_t size);

#endif //C_DATASTRUCTURES_BINARYMAXHEAP_H
