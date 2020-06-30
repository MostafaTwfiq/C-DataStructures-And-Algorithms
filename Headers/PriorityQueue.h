#ifndef C_DATASTRUCTURES_PRIORITYQUEUE_H
#define C_DATASTRUCTURES_PRIORITYQUEUE_H


#include <stdio.h>
#include <stdlib.h>
#include <string.h>



typedef struct PriorityQueue {
    void **arr;
    int length;
    int count;
    int fPointer;
    int sizeOfType;
    int (*comp)(const void *, const void *);
} PriorityQueue;




PriorityQueue *priorityQueueInitialization(int sizeOfType, int (*comp)(const void *, const void *));


void pQueueEnqueue(PriorityQueue *queue, void *item);


void pQueueEnqueueAll(PriorityQueue *queue, void **items, int arrLength);


void *pQueueDequeue(PriorityQueue *queue);


void *pQueuePeek(PriorityQueue *queue);


int pQueueGetLength(PriorityQueue *queue);


int pQueueIsEmpty(PriorityQueue *queue);


void **pQueueToArray(PriorityQueue *queue);


void clearPQueue(PriorityQueue *queue);


void destroyPQueue(PriorityQueue *queue);


#endif //C_DATASTRUCTURES_PRIORITYQUEUE_H
