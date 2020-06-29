#ifndef C_DATASTRUCTURES_HEAP_H
#define C_DATASTRUCTURES_HEAP_H
#include "Utils.h"

#define MAX_HEAP 0
#define MIN_HEAP 1

#define PARENT(i)      (int) (i - 1)/2
#define LCHILD(i)      (2*i) + 1
#define RCHILD(i)      (2*i+1) + 1
#define HAS_LEFT(h,i)  (LCHILD(i) < h->size)
#define HAS_RIGHT(h,i) (RCHILD(i) < h->size)

typedef struct {
    void **  memory;
    uint8_t  type;
    uint32_t capacity;
    uint32_t size;
    uint16_t sizeOfType;
    int16_t  (*cmpFn)(void* ,void* );
}Heap;

Heap *HeapInitialize(uint8_t type, uint16_t size,int16_t (*cmp)(void*,void*));

void insertInHeap(Heap* h,void* value);

Heap *heapify(void *arr,uint16_t size, uint8_t type);

void destroyHeap(Heap *);

void printHeap(Heap *h, void (*printfn)(void *));

void heapifyDown(Heap* h, int index);

#endif //C_DATASTRUCTURES_HEAP_H

