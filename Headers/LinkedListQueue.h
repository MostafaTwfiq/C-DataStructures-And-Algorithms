#ifndef C_DATASTRUCTURES_LINKEDLISTQUEUE_H
#define C_DATASTRUCTURES_LINKEDLISTQUEUE_H

#ifdef __cplusplus
extern "C" {
#endif

typedef struct LinkedListQueue {
    struct LinkedList *linkedList;
} LinkedListQueue;

LinkedListQueue *linkedListQueueInitialization(void (*freeFun)(void *));

void lLQueueEnqueue(LinkedListQueue *queue, void *item);

void lLQueueEnqueueAll(LinkedListQueue *queue, void **arr, int arrLength);

void *lLQueueDequeue(LinkedListQueue *queue);

void *lLQueuePeek(LinkedListQueue *queue);

int lLQueueGetLength(LinkedListQueue *queue);

int lLQueueIsEmpty(LinkedListQueue *queue);

void **lLQueueToArray(LinkedListQueue *queue);

void clearLLQueue(LinkedListQueue *queue);

void destroyLLQueue(LinkedListQueue *queue);

#ifdef __cplusplus
}
#endif

#endif //C_DATASTRUCTURES_LINKEDLISTQUEUE_H
