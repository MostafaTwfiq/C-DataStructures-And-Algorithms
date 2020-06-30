#include "../Headers/PriorityQueue.h"




void swapItems(void **arr, int index1, int index2);





/** This function will take the size of the type, and the compare function address as a parameters,
    then it will initialize a new priority queue in the memory,
    then the function will return the queue address.
 * @param sizeOfType
 * @param comp
 * @return
 */

PriorityQueue *priorityQueueInitialization(int sizeOfType, int (*comp)(const void *, const void *)) {
    PriorityQueue *queue = (PriorityQueue *) malloc(sizeof(PriorityQueue));

    queue->length = 10;
    queue->arr = (void  *) malloc(sizeof(void *) * queue->length);
    queue->count = queue->fPointer = 0;
    queue->sizeOfType = sizeOfType;
    queue->comp = comp;

    return queue;

}






/** This  function will take the queue address, and the item address as a parameters,
    then it will push the new item in it's right place in the queue.
 * Note: if the compare function returned a positive number, that means to swap.
 * @param queue
 * @param item
 */

void pQueueEnqueue(PriorityQueue *queue, void *item) {
    if (queue->count == queue->length) {
        queue->length *= 2;
        void **tempArr = (void *) malloc(sizeof(void *) * queue->length);
        memcpy(tempArr, queue->arr + queue->fPointer, sizeof(void *) * (queue->count - queue->fPointer));
        free(queue->arr);
        queue->arr = tempArr;
        queue->count -= queue->fPointer;
        queue->fPointer = 0;
    }

    queue->arr[queue->count++] = item;
    int index = queue->count - 1;
    while (index > queue->fPointer) {
        if (queue->comp(queue->arr[index], queue->arr[index - 1]) > 0)
            swapItems(queue->arr, index, index - 1);
        else
            break;

        index--;
    }

}






/** This function will take the queue address, the items array of pointers, and the length of the array as a parameters,
    then it will push all the items in the array to the queue.
 * @param queue
 * @param items
 * @param arrLength
 */

void pQueueEnqueueAll(PriorityQueue *queue, void **items, int arrLength) {

    for (int i = 0; i < arrLength; i++)
        pQueueEnqueue(queue, items[i]);


}






/** This function will take the queue address as a parameter,
 * then it will return the rear item address in the queue.
 * @param queue
 * @return
 */

void *pQueueDequeue(PriorityQueue *queue) {
    if (pQueueIsEmpty(queue)) {
        fprintf(stderr, "Illegal statement, queue is empty.");
        exit(-3);
    }

    return queue->arr[queue->fPointer++];

}






/** This function will take the queue address as a parameter,
    then it will return the rear  item address in the queue,
    without removing the item from the queue.
 * @param queue
 * @return
 */

void *pQueuePeek(PriorityQueue *queue) {
    if (pQueueIsEmpty(queue)) {
        fprintf(stderr, "Illegal statement, queue is empty.");
        exit(-3);
    }

    return queue->arr[queue->fPointer];

}







/** This function will take the queue address as a parameter,
    then it will return the number of the items in the queue.
 * @param queue
 * @return
 */

int pQueueGetLength(PriorityQueue *queue) {
    return queue->count - queue->fPointer;
}







/** This function will take the queue address as a parameter,
    then it will return one (1) if the queue is empty,
    other wise it will return zero (0).
 * @param queue
 * @return
 */
int pQueueIsEmpty(PriorityQueue *queue) {
    return queue->count == queue->fPointer;
}







/** This function will take the queue address as a parameter,
    then it will return a double void pointer array that contains a copy of all the queue items.
 * @param queue
 * @return
 */

void **pQueueToArray(PriorityQueue *queue) {

    void **arr = (void **) malloc(sizeof(void *) * pQueueGetLength(queue));
    for (int i = queue->fPointer; i < queue->count; i++) {
        arr[i - queue->fPointer] = (void *) malloc(queue->sizeOfType);
        memcpy(arr[i - queue->fPointer], queue->arr[i], queue->sizeOfType);
    }

    return arr;

}






/** This function will take the queue address as a parameter,
    then it will destroy and free all the items in the queue,
    without destroying the queue it self.
 * @param queue
 */

void clearPQueue(PriorityQueue *queue) {
    while (queue->count != queue->fPointer)
        free(queue->arr[queue->fPointer++]);

    queue->fPointer = queue->count = 0;

}







/** This function will take the queue address as a parameter,
    then it will destroy and free the queue and all it's items.
 * @param queue
 */

void destroyPQueue(PriorityQueue *queue) {
    clearPQueue(queue);
    free(queue->arr);
    free(queue);

}






/** This function takes a double void array pointer, index one, and index two as a parameters,
    then it will swap the two indices in the array.
 * Note: this function should be only called by the priority queue functions.
 * @param arr
 * @param index1
 * @param index2
 */

void swapItems(void **arr, int index1, int index2) {
    void *temp = arr[index1];
    arr[index1] = arr[index2];
    arr[index2] = temp;
}