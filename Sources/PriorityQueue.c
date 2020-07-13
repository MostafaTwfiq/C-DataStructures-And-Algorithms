#include "../Headers/PriorityQueue.h"



typedef struct PQueueItem {
    void *value;
    int sizeOfItem;
} PQueueItem;



void swapItems(PQueueItem **arr, int index1, int index2);





/** This function will take the freeing function address, and the compare function address as a parameters,
    then it will initialize a new priority queue in the memory,
    then the function will return the queue address.
 * @param freeItem the freeing item function address, that will be called to free the queue items
 * @param comp the comparing function address
 * @return it will return the initialized queue address
 */

PriorityQueue *priorityQueueInitialization(void (*freeItem)(void *item), int (*comp)(const void *, int, const void *, int)) {
    PriorityQueue *queue = (PriorityQueue *) malloc(sizeof(PriorityQueue));

    queue->length = 10;
    queue->arr = (PQueueItem **) malloc(sizeof(PQueueItem *) * queue->length);
    queue->count = queue->fPointer = 0;
    queue->freeItem = freeItem;
    queue->comp = comp;

    return queue;

}






/** This  function will take the queue address, the item address, and the size of the item as a parameters,
    then it will push the new item in it's right place in the queue.
 * Note: if the compare function returned a positive number, that means to swap.
 * @param queue the queue address
 * @param item the new item address
 * @param sizeOfItem the size of the new item
 */

void pQueueEnqueue(PriorityQueue *queue, void *item, int sizeOfItem) {
    if (queue->count == queue->length) {
        queue->length *= 2;
        PQueueItem **tempArr = (PQueueItem **) malloc(sizeof(PQueueItem *) * queue->length);
        memcpy(tempArr, queue->arr + queue->fPointer, sizeof(PQueueItem *) * (queue->count - queue->fPointer));
        free(queue->arr);
        queue->arr = tempArr;
        queue->count -= queue->fPointer;
        queue->fPointer = 0;
    }

    PQueueItem *newItem = (PQueueItem *) malloc(sizeof(PQueueItem));
    newItem->value = item;
    newItem->sizeOfItem = sizeOfItem;
    queue->arr[queue->count++] = newItem;
    int index = queue->count - 1;

    while (index > queue->fPointer) {
        if (    queue->comp(    queue->arr[index - 1]->value,
                                queue->arr[index - 1]->sizeOfItem,
                                queue->arr[index]->value,
                                queue->arr[index]->sizeOfItem   ) > 0   ) {

            swapItems(queue->arr, index, index - 1);

        } else
            break;

        index--;
    }

}






/** This function will take the queue address, the items array of pointers, and the length of the array as a parameters,
    then it will push all the items in the array to the queue.
 * @param queue the queue address
 * @param items the items array pointer
 * @param arrLength the items array length
 * @param sizeOfItem the size of items in the array in bytes
 */

void pQueueEnqueueAll(PriorityQueue *queue, void **items, int arrLength, int sizeOfItem) {

    for (int i = 0; i < arrLength; i++)
        pQueueEnqueue(queue, items[i], sizeOfItem);


}






/** This function will take the queue address as a parameter,
 * then it will return the rear item address in the queue.
 * @param queue the queue address
 * @return it will return the front item of the queue
 */

void *pQueueDequeue(PriorityQueue *queue) {
    if (pQueueIsEmpty(queue)) {
        fprintf(stderr, "Illegal statement, queue is empty.");
        exit(-3);
    }

    void *returnItem = queue->arr[queue->fPointer]->value;
    free(queue->arr[queue->fPointer++]);

    return returnItem;

}






/** This function will take the queue address as a parameter,
    then it will return the rear  item address in the queue,
    without removing the item from the queue.
 * @param queue the queue address
 * @return it will return the front item of the queue
 */

void *pQueuePeek(PriorityQueue *queue) {
    if (pQueueIsEmpty(queue)) {
        fprintf(stderr, "Illegal statement, queue is empty.");
        exit(-3);
    }

    return queue->arr[queue->fPointer]->value;

}







/** This function will take the queue address as a parameter,
    then it will return the number of the items in the queue.
 * @param queue the queue address
 * @return it will return the number of items in the queue
 */

int pQueueGetLength(PriorityQueue *queue) {
    return queue->count - queue->fPointer;
}







/** This function will take the queue address as a parameter,
    then it will return one (1) if the queue is empty,
    other wise it will return zero (0).
 * @param queue the queue address
 * @return it will return one if the queue is empty, other wise it will return zero
 */

int pQueueIsEmpty(PriorityQueue *queue) {
    return queue->count == queue->fPointer;
}







/** This function will take the queue address as a parameter,
    then it will return a double void pointer array that contains a copy of all the queue items.
 * @param queue the queue address
 * @return it will return a double void pointer array consisting of the queue items
 */

void **pQueueToArray(PriorityQueue *queue) {

    void **arr = (void **) malloc(sizeof(void *) * pQueueGetLength(queue));

    for (int i = queue->fPointer; i < queue->count; i++) {
        arr[i - queue->fPointer] = (void *) malloc(queue->arr[i]->sizeOfItem);
        memcpy(arr[i - queue->fPointer], queue->arr[i]->value, queue->arr[i]->sizeOfItem);
    }

    return arr;

}






/** This function will take the queue address as a parameter,
    then it will destroy and free all the items in the queue,
    without destroying the queue it self.
 * @param queue the queue address
 */

void clearPQueue(PriorityQueue *queue) {
    while (queue->count != queue->fPointer) {
        queue->freeItem(queue->arr[queue->fPointer]->value);
        free(queue->arr[queue->fPointer++]);
    }

    queue->fPointer = queue->count = 0;

}







/** This function will take the queue address as a parameter,
    then it will destroy and free the queue and all it's items.
 * @param queue the queue address
 */

void destroyPQueue(PriorityQueue *queue) {
    clearPQueue(queue);
    free(queue->arr);
    free(queue);

}






/** This function takes a double void array pointer, index one, and index two as a parameters,
    then it will swap the two indices in the array.
 * Note: this function should be only called by the priority queue functions.
 * @param arr the PQueue items array address
 * @param index1 the first index
 * @param index2 the second index
 */

void swapItems(PQueueItem **arr, int index1, int index2) {
    PQueueItem *temp = arr[index1];
    arr[index1] = arr[index2];
    arr[index2] = temp;
}