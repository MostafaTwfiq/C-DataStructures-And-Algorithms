#include "../Headers/LinkedListQueue.h"
#include "../Headers/Utils.h"





/** This function will take the size of the items type as a parameter,
    then it will initialize a new linked list queue, and return it's address.
 * @param freeFun the free function address that will be called to free the queue items
 */

LinkedListQueue *linkedListQueueInitialization(void (*freeFun)(void *)) {

    LinkedListQueue *queue = (LinkedListQueue *) malloc(sizeof(LinkedListQueue));

    queue->linkedList = linkedListInitialization(freeFun, NULL);

    return queue;
}




/** This function will take the queue address, and the item address as a parameter,
    then it will push the item into the queue.
 * @param queue the queue address
 * @param item the new item address
 */

void lLQueueEnqueue(LinkedListQueue *queue, void *item) {

    if (queue == NULL) {
        fprintf(stderr,"Illegal argument, the queue is NULL.");
        exit(-4);
    }

    linkedListAddLast(queue->linkedList, item);

}




/** This function will take the queue address, the array address, and the array length as a parameter,
    then it will add all the items in the array to the queue in order.
 * @param queue the queue address
 * @param arr the array address that will be added to the queue
 * @param arrLength the length of the array
 */

void lLQueueEnqueueAll(LinkedListQueue *queue, void **arr, int arrLength) {
    if (queue == NULL) {
        fprintf(stderr,"Illegal argument, the queue is NULL.");
        exit(-4);
    }

    for (int i = 0; i < arrLength; i++)
        linkedListAddLast(queue->linkedList, arr[i]);

}





/** This  function will take the queue address as a parameter,
    then it will return the first item in the queue,
    then the item will be deleted from the queue.
 * Note: if the queue i empty the program will be terminated.
 * @param queue the queue address
 * @return it will return the (first in) item address as a void pointer
 */

void *lLQueueDequeue(LinkedListQueue *queue) {

    if (queue == NULL) {
        fprintf(stderr,"Illegal argument, the queue is NULL.");
        exit(-4);
    } else if (lLQueueIsEmpty(queue)) {
        fprintf(stderr,"Illegal state, the queue is empty.");
        exit(-4);
    }

    void *item = linkedListGetFirst(queue->linkedList);
    linkedListDeleteFirstWtoFr(queue->linkedList);

    return item;
}





/** This function will take the queue address as a parameter,
    then it will return the first item in the queue without removing the item from the queue.
 * Note: if the queue i empty the program will be terminated.
 * @param queue the queue address
 * @return it will return the (first in) item address as a void pointer
 */

void *lLQueuePeek(LinkedListQueue *queue) {

    if (queue == NULL) {
        fprintf(stderr,"Illegal argument, the queue is NULL.");
        exit(-4);
    } else if (lLQueueIsEmpty(queue)) {
        fprintf(stderr,"Illegal state, the queue is empty.");
        exit(-4);
    }

    void *item = linkedListGetFirst(queue->linkedList);

    return item;

}






/** This function will take the queue address as a parameter,
    then it will return the number of the elements in the array.
 * @param queue the queue  address
 * @return it will return the number of items in the queue
 */

int lLQueueGetLength(LinkedListQueue *queue) {
    if (queue == NULL) {
        fprintf(stderr,"Illegal argument, the queue is NULL.");
        exit(-4);
    }

    return linkedListGetLength(queue->linkedList);

}





/** This function will take the queue address as a parameter,
    then it will return one (1) if the queue is empty, other wise it will return zero (0).
 * @param queue the queue address
 * @return it will return one if the queue is empty other wise it will return zero
 */

int lLQueueIsEmpty(LinkedListQueue *queue) {

    if (queue == NULL) {
        fprintf(stderr,"Illegal argument, the queue is NULL.");
        exit(-4);
    }

    return linkedListIsEmpty(queue->linkedList);
}






/** This function will take the queue address as a parameter,
 * then it will return a void array that contains all the items in the queue.
 * @param queue the queue address
 * @return it will return a double void array that contains a copy of all the items in the queue
 */

void **lLQueueToArray(LinkedListQueue *queue) {

    if (queue == NULL) {
        fprintf(stderr,"Illegal argument, the queue is NULL.");
        exit(-4);
    }

    return linkedListToArray(queue->linkedList);

}

/** This function will take the queue address as a parameter,
 * then it will delete and free all the items in the queue without destroying the queue.
 * @param queue the queue address
 */

void clearLLQueue(LinkedListQueue *queue) {

    if (queue == NULL) {
        fprintf(stderr,"Illegal argument, the queue is NULL.");
        exit(-4);
    }

    linkedListClear(queue->linkedList);
}




/** This function will take the queue address as a parameter,
 * then it will destroy and free all the item in the queue then it will also free the queue.
 * @param queue the queue address
 */

void destroyLLQueue(LinkedListQueue *queue) {

    if (queue == NULL) {
        fprintf(stderr,"Illegal argument, the queue is NULL.");
        exit(-4);
    }

    destroyLinkedList(queue->linkedList);
    free(queue);
}
