#ifndef C_DATASTRUCTURES_MinHeap_H
#define C_DATASTRUCTURES_MinHeap_H
#include "Utils.h"


#define PARENT(i)      (int) (i - 1)/2
#define LCHILD(i)      (2*i) + 1
#define RCHILD(i)      (2*i+1) + 1
#define HAS_LEFT(h,i)  (LCHILD(i) < h->size)
#define HAS_RIGHT(h,i) (RCHILD(i) < h->size)

typedef struct BinaryMinHeap{
    void **  memory;
    uint32_t capacity;
    uint32_t size;
    uint16_t sizeOfType;
    int16_t  (*cmpFn)(const void* ,const void* );
}BinaryMinHeap;

BinaryMinHeap *MinHeapInitialize(uint16_t size, int16_t (*cmp)(const void*, const void*));

void insertInMinHeap(BinaryMinHeap* h, void* value);

BinaryMinHeap *MinHeapify(void *arr, uint16_t size, uint8_t type);

void destroyMinHeap(BinaryMinHeap *);

void printMinHeap(BinaryMinHeap *h, void (*printfn)(void *));

void MinHeapifyDown(BinaryMinHeap* h, int index);

void MinHeapDelete(BinaryMinHeap* heap, void ** res);

void * MinHeapAddAll(BinaryMinHeap *binaryMaxHeap,void **arr, uint16_t size);

#endif //C_DATASTRUCTURES_MinHeap_H

