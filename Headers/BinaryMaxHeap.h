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

typedef struct BinaryMaxHeap{
    void **  memory;
    uint32_t capacity;
    uint32_t size;
    uint16_t sizeOfType;
    int16_t  (*cmpFn)(const void* ,const void* );
}BinaryMaxHeap;

BinaryMaxHeap *MaxHeapInitialize(uint16_t size, int16_t (*cmp)(const void*, const void*));

void MaxHeapInsert(BinaryMaxHeap* h, void* value);

BinaryMaxHeap *MaxHeapify(void **arr, uint16_t size,int16_t (*cmp)(const void*, const void*));

void printMaxHeap(BinaryMaxHeap *h, void (*printfn)(void *));

void MaxHeapifyDown(BinaryMaxHeap* h, int index);

void MaxHeapPrint(BinaryMaxHeap *MaxHeap, int i, void (*printfn)(void *));

void MaxHeapDelete(BinaryMaxHeap* heap, void ** res);

#endif //C_DATASTRUCTURES_BINARYMAXHEAP_H
