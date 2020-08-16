#ifndef C_DATASTRUCTURES_HPRIORITYQUEUE_H
#define C_DATASTRUCTURES_HPRIORITYQUEUE_H


#ifdef __cplusplus
extern "C" {
#endif

/** @struct HPriorityQueue
*  @brief This structure implements a basic generic priority queue using binary heap.
*  @var HPriorityQueue::heap
*  Member 'heap' the heap pointer.
*/

typedef struct HPriorityQueue {

    struct BinaryHeap *heap;

} HPriorityQueue;


HPriorityQueue *hPriorityQueueInitialization(void (*freeFn)(void *), int (*cmp)(const void *, const void *));

void hpQueueEnqueue(HPriorityQueue *queue, void *item);

void hpQueueEnqueueAll(HPriorityQueue *queue, void *items, int length);

void *hpQueueDequeue(HPriorityQueue *queue);

void *hpQueuePeek(HPriorityQueue *queue);

int hpQueueGetLength(HPriorityQueue *queue);

int hpQueueIsEmpty(HPriorityQueue *queue);

void **hpQueueToArray(HPriorityQueue *queue);

void clearHPQueue(HPriorityQueue *queue);

void destroyHPQueue(HPriorityQueue *queue);

#ifdef __cplusplus
}
#endif

#endif //C_DATASTRUCTURES_HPRIORITYQUEUE_H
