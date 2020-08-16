#ifndef C_DATASTRUCTURES_BINARYHEAP_H
#define C_DATASTRUCTURES_BINARYHEAP_H


/** @struct BinaryHeap
 *  @brief This structure implements a basic generic binary heap.
 *  @var BinaryHeap::arr
 *  Member 'arr' is a pointer to the heap array.
 *  @var BinaryHeap::length
 *  Member 'length' is the total allocated space by the memory of the heap.
 *  @var BinaryHeap::count
 *  Member 'count' holds the number of nodes currently present in the heap.
 *  @var BinaryHeap::freeFun
 *  Member 'freeFun' is a pointer to the free function.
 *  @var BinaryHeap::cmp
 *  Member 'cmp' is a pointer to the comparison function that is going to be used throughout the heap.
 */

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

void *binaryHeapDeleteRootWtoFr(BinaryHeap *heap);

int binaryHeapContains(BinaryHeap *heap, void *item);

void *binaryHeapGet(BinaryHeap *heap, void *item);

int binaryHeapGetSize(BinaryHeap *heap);

int binaryHeapIsEmpty(BinaryHeap *heap);

void **binaryHeapToArray(BinaryHeap *heap);

void clearBinaryHeap(BinaryHeap *heap);

void destroyBinaryHeap(void *heap);

#endif //C_DATASTRUCTURES_BINARYHEAP_H
