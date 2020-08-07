#ifndef C_DATASTRUCTURES_BINARYHEAP_H
#define C_DATASTRUCTURES_BINARYHEAP_H


typedef struct BinaryHeap {
    void **arr;
    int length;
    int count;
    void (*freeFun)(void *);
    int (*cmp)(const void *, const void *);
} BinaryHeap;


BinaryHeap *binaryHeapInitialization(void (*freeFun)(void *), int (*cmp)(const void *, const void *));

void binaryHeapInsert(BinaryHeap *heap, void *item);

void binaryHeapInsertAll(BinaryHeap *heap, void **items, int length);

void binaryHeapDeleteRoot(BinaryHeap *heap);

void binaryHeapDeleteRootWtoFr(BinaryHeap *heap);

int binaryHeapContains(BinaryHeap *heap, void *item);

void *binaryHeapGet(BinaryHeap *heap, void *item);

int binaryHeapGetSize(BinaryHeap *heap);

int binaryHeapIsEmpty(BinaryHeap *heap);

void **binaryHeapToArray(BinaryHeap *heap);

void clearBinaryHeap(BinaryHeap *heap);

void destroyBinaryHeap(BinaryHeap *heap);

int binaryHeapIsEmpty(BinaryHeap *binaryHeap);


#endif //C_DATASTRUCTURES_BINARYHEAP_H
