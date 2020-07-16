#ifndef C_DATASTRUCTURES_PRIORITYQUEUE_H
#define C_DATASTRUCTURES_PRIORITYQUEUE_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef struct PriorityQueue {
    struct PQueueItem **arr;
    int length;
    int count;
    int fPointer;

    void (*freeItem)(void *item);

    int (*comp)(const void *, int, const void *, int);
} PriorityQueue;


PriorityQueue *
priorityQueueInitialization(void (*freeItem)(void *item), int (*comp)(const void *, int, const void *, int));

void pQueueEnqueue(PriorityQueue *queue, void *item, int sizeOfItem);

void pQueueEnqueueAll(PriorityQueue *queue, void **items, int arrLength, int sizeOfItem);

void *pQueueDequeue(PriorityQueue *queue);

void *pQueuePeek(PriorityQueue *queue);

int pQueueGetLength(PriorityQueue *queue);

int pQueueIsEmpty(PriorityQueue *queue);

void **pQueueToArray(PriorityQueue *queue);

void clearPQueue(PriorityQueue *queue);

void destroyPQueue(PriorityQueue *queue);

#ifdef __cplusplus
}
#endif

#endif //C_DATASTRUCTURES_PRIORITYQUEUE_H
