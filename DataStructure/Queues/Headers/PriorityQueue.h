#ifndef C_DATASTRUCTURES_PRIORITYQUEUE_H
#define C_DATASTRUCTURES_PRIORITYQUEUE_H

#ifdef __cplusplus
extern "C" {
#endif


/** @struct PriorityQueue
*  @brief This structure implements a basic generic priority queue.
*  @var PriorityQueue:: arr
*  Member 'arr' is a pointer to the the Queue's memory (array).
*  @var PriorityQueue::length
*  Member 'length' holds the current max allocated size for the Queue.
*  @var PriorityQueue::count
*  Member 'count' holds the index to the last Queue Element.
*  @var PriorityQueue::fPointer
*  Member 'fPointer' holds the index to the front of the Queue Element.
*  @var PriorityQueue:: 'freeItem'
*  Member 'freeItem' holds pointer to the function responsible for freeing the elements stored in the queue.
*  @var PriorityQueue:: 'comp'
*  Member 'comp' holds pointer to the function responsible for comparing the elements stored in the queue.
*/

typedef struct PriorityQueue {
    void **arr;
    int length;
    int count;
    int fPointer;

    void (*freeItem)(void *);

    int (*comp)(const void *, const void *);

} PriorityQueue;

PriorityQueue *priorityQueueInitialization(void (*freeItem)(void *), int (*comp)(const void *, const void *));

void pQueueEnqueue(PriorityQueue *queue, void *item);

void pQueueEnqueueAll(PriorityQueue *queue, void **items, int arrLength);

void *pQueueDequeue(PriorityQueue *queue);

void *pQueuePeek(PriorityQueue *queue);

int pQueueGetLength(PriorityQueue *queue);

int pQueueIsEmpty(PriorityQueue *queue);

void **pQueueToArray(PriorityQueue *queue);

void clearPQueue(PriorityQueue *queue);

void destroyPQueue(void *queue);

#ifdef __cplusplus
}
#endif

#endif //C_DATASTRUCTURES_PRIORITYQUEUE_H
