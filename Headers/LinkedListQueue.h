#ifndef C_DATASTRUCTURES_LINKEDLISTQUEUE_H
#define C_DATASTRUCTURES_LINKEDLISTQUEUE_H



#include "LinkedList.h"



typedef struct LinkedListQueue {

    LinkedList *linkedList;

} LinkedListQueue;



LinkedListQueue *linkedListQueueInitialization(int sizeOfType);


void lLQueueEnqueue(LinkedListQueue *queue, void *item);


void *lLQueueDequeue(LinkedListQueue *queue);


void *lLQueuePeek(LinkedListQueue *queue);


int lLQueueIsEmpty(LinkedListQueue *queue);


void clearLLQueue(LinkedListQueue *queue);

void destroyLLQueue(LinkedListQueue *queue);


#endif //C_DATASTRUCTURES_LINKEDLISTQUEUE_H
