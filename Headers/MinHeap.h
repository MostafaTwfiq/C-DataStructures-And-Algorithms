#ifndef C_DATASTRUCTURES_MinHeap_H
#define C_DATASTRUCTURES_MINMinHeap_H
#include "Utils.h"

#define MAX_MinHeap 0
#define MIN_MinHeap 1

#define PARENT(i)      (int) (i - 1)/2
#define LCHILD(i)      (2*i) + 1
#define RCHILD(i)      (2*i+1) + 1
#define HAS_LEFT(h,i)  (LCHILD(i) < h->size)
#define HAS_RIGHT(h,i) (RCHILD(i) < h->size)

typedef struct {
    void **  memory;
    uint32_t capacity;
    uint32_t size;
    uint16_t sizeOfType;
    int16_t  (*cmpFn)(const void* ,const void* );
}MinHeap;

MinHeap *MinHeapInitialize(uint8_t type, uint16_t size,int16_t (*cmp)(const void*,const void*));

void insertInMinHeap(MinHeap* h,void* value);

MinHeap *MinHeapify(void *arr,uint16_t size, uint8_t type);

void destroyMinHeap(MinHeap *);

void printMinHeap(MinHeap *h, void (*printfn)(void *));

void MinHeapifyDown(MinHeap* h, int index);

void MinHeapPrint(MinHeap *MinHeap,int i,void (*printfn)(void *));

#endif //C_DATASTRUCTURES_MinHeap_H

