#ifndef C_DATASTRUCTURES_LINKEDLISTQUEUE_H
#define C_DATASTRUCTURES_LINKEDLISTQUEUE_H



#include "LinkedList.h"



typedef struct LinkedListQueue {

    LinkedList *linkedList;

} LinkedListQueue;



LinkedListQueue *linkedListQueueInitialization(void (*freeFun));


void lLQueueEnqueue(LinkedListQueue *queue, void *item, int sizeOfItem);


void lLQueueEnqueueAll(LinkedListQueue *queue, void **arr, int arrLength, int sizeOfItem);


void *lLQueueDequeue(LinkedListQueue *queue);


void *lLQueuePeek(LinkedListQueue *queue);


int lLQueueGetLength(LinkedListQueue *queue);


int lLQueueIsEmpty(LinkedListQueue *queue);


void **lLQueueToArray(LinkedListQueue *queue);


void clearLLQueue(LinkedListQueue *queue);


void destroyLLQueue(LinkedListQueue *queue);


#endif //C_DATASTRUCTURES_LINKEDLISTQUEUE_H
