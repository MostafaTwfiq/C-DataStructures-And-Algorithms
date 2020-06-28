#ifndef C_DATASTRUCTURES_HEAP_H
#define C_DATASTRUCTURES_HEAP_H
#include "Utils.h"

#define MAX_HEAP  0
#define MIN_HEAP 1

typedef struct Heap{
    void **heapArr;
    uint8_t  type;
    uint32_t capacity;
    uint32_t sizeOfType;
}Heap;

Heap * HeapInitialize(char type,uint32_t size);

#endif //C_DATASTRUCTURES_HEAP_H

