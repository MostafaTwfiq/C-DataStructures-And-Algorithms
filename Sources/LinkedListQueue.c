#include "../Headers/LinkedListQueue.h"





/** This function will take the size of the items type as a parameter,
    then it will initialize a new linked list queue, and return it's address.
 * @param sizeOfType
 */

LinkedListQueue *linkedListQueueInitialization(int sizeOfType) {

    LinkedListQueue *queue = (LinkedListQueue *) malloc(sizeof(LinkedListQueue));

    queue->linkedList = linkedListInitialization(sizeOfType);

    return queue;
}




/** This function will take the queue address, and the item address as a parameter,
    then it will push the item into the queue.
 * @param queue
 * @param item
 */

void lLQueueEnqueue(LinkedListQueue *queue, void *item) {

    if (queue == NULL) {
        printf("Illegal argument, the queue is NULL.");
        exit(-4);
    }

    linkedListAddLast(queue->linkedList, item);

}




/** This  function will take the queue address as a parameter,
    then it will return the first item in the queue,
    then the item will be deleted from the queue.
 * Note: if the queue i empty the program will be terminated.
 * @param queue
 * @return
 */

void *lLQueueDequeue(LinkedListQueue *queue) {

    if (queue == NULL) {
        printf("Illegal argument, the queue is NULL.");
        exit(-4);
    } else if (lLQueueIsEmpty(queue)) {
        printf("Illegal state, the queue is empty.");
        exit(-4);
    }

    void *item = linkedListGetFirst(queue->linkedList);
    linkedListDeleteFirstWtFr(queue->linkedList);

    return item;
}




/** This function will take the queue address as a parameter,
    then it will return the first item in the queue without removing the item from the queue.
 * Note: if the queue i empty the program will be terminated.
 * @param queue
 * @return
 */

void *lLQueuePeek(LinkedListQueue *queue) {

    if (queue == NULL) {
        printf("Illegal argument, the queue is NULL.");
        exit(-4);
    } else if (lLQueueIsEmpty(queue)) {
        printf("Illegal state, the queue is empty.");
        exit(-4);
    }

    void *item = linkedListGetFirst(queue->linkedList);

    return item;

}




/** This function will take the queue address as a parameter,
    then it will return one (1) if the queue is empty, other wise it will return zero (0).
 * @param queue
 * @return
 */

int lLQueueIsEmpty(LinkedListQueue *queue) {

    if (queue == NULL) {
        printf("Illegal argument, the queue is NULL.");
        exit(-4);
    }

    return linkedListIsEmpty(queue->linkedList);
}




/** This function will take the queue address as a parameter,
 * then it will delete and free all the items in the queue without destroying the queue.
 * @param queue
 */

void clearLLQueue(LinkedListQueue *queue) {

    if (queue == NULL) {
        printf("Illegal argument, the queue is NULL.");
        exit(-4);
    }

    linkedListClear(queue->linkedList);
}




/** This function will take the queue address as a parameter,
 * then it will destroy and free all the item in the queue then it will also free the queue.
 * @param queue
 */

void destroyLLQueue(LinkedListQueue *queue) {

    if (queue == NULL) {
        printf("Illegal argument, the queue is NULL.");
        exit(-4);
    }

    destroyLinkedList(queue->linkedList);
    free(queue);
}
