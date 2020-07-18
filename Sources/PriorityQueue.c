#include "../Headers/PriorityQueue.h"
#include "../Headers/Utils.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>



void swapItems(void **arr, int index1, int index2);





/** This function will take the freeing function address, and the compare function address as a parameters,
    then it will initialize a new priority queue in the memory,
    then the function will return the queue address.
 * @param freeItem the freeing item function address, that will be called to free the queue items
 * @param comp the comparing function address
 * @return it will return the initialized queue address
 */

PriorityQueue *priorityQueueInitialization(void (*freeItem)(void *), int (*comp)(const void *, const void *)) {
    if (freeItem == NULL) {
        fprintf(stderr, INVALID_ARG_MESSAGE, "free function pointer", "priority queue data structure");
        exit(INVALID_ARG);
    } else if (comp == NULL) {
        fprintf(stderr, INVALID_ARG_MESSAGE, "comparator function pointer", "priority queue data structure");
        exit(INVALID_ARG);
    }

    PriorityQueue *queue = (PriorityQueue *) malloc(sizeof(PriorityQueue));
    if (queue == NULL) {
        fprintf(stderr, FAILED_ALLOCATION_MESSAGE, "queue", "priority queue data structure");
        exit(FAILED_ALLOCATION);
    }

    queue->length = 10;
    queue->arr = (void **) malloc(sizeof(void *) * queue->length);
    if (queue->arr == NULL) {
        fprintf(stderr, FAILED_ALLOCATION_MESSAGE, "queue array", "priority queue data structure");
        exit(FAILED_ALLOCATION);
    }

    queue->count = queue->fPointer = 0;
    queue->freeItem = freeItem;
    queue->comp = comp;

    return queue;

}






/** This  function will take the queue address, and the item address as a parameters,
    then it will push the new item in it's right place in the queue.
 * Note: if the compare function returned a positive number, that means to swap.
 * @param queue the queue address
 * @param item the new item address
 */

void pQueueEnqueue(PriorityQueue *queue, void *item) {
    if (queue == NULL) {
        fprintf(stderr, NULL_POINTER_MESSAGE, "queue pointer", "priority queue data structure");
        exit(NULL_POINTER);
    } else if (item == NULL) {
        fprintf(stderr, INVALID_ARG_MESSAGE, "item pointer", "priority queue data structure");
        exit(INVALID_ARG);
    }

    if (queue->count == queue->length) {
        queue->length *= 2;
        void **tempArr = (void **) malloc(sizeof(void *) * queue->length);
        if (tempArr == NULL) {
            fprintf(stderr, FAILED_ALLOCATION_MESSAGE, "queue array", "priority queue data structure");
            exit(FAILED_ALLOCATION);
        }

        if (!memcpy(tempArr, queue->arr + sizeof(void *) * queue->fPointer, sizeof(void *) * (queue->count - queue->fPointer))) {
            fprintf(stderr, FAILED_COPY_MESSAGE, "new queue array", "priority queue data structure");
            exit(FAILED_COPY);
        }

        free(queue->arr);
        queue->arr = tempArr;
        queue->count -= queue->fPointer;
        queue->fPointer = 0;
    }

    queue->arr[queue->count++] = item;
    int index = queue->count - 1;

    while (index > queue->fPointer) {
        if (queue->comp(queue->arr[index - 1], queue->arr[index]) > 0) {

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
 */

void pQueueEnqueueAll(PriorityQueue *queue, void **items, int arrLength) {

    if (queue == NULL) {
        fprintf(stderr, NULL_POINTER_MESSAGE, "queue pointer", "priority queue data structure");
        exit(NULL_POINTER);
    } else if (items == NULL) {
        fprintf(stderr, INVALID_ARG_MESSAGE, "items array pointer", "priority queue data structure");
        exit(INVALID_ARG);
    }

    for (int i = 0; i < arrLength; i++)
        pQueueEnqueue(queue, items[i]);


}






/** This function will take the queue address as a parameter,
 * then it will return the rear item address in the queue.
 * @param queue the queue address
 * @return it will return the front item of the queue
 */

void *pQueueDequeue(PriorityQueue *queue) {

    if (queue == NULL) {
        fprintf(stderr, NULL_POINTER_MESSAGE, "queue pointer", "priority queue data structure");
        exit(NULL_POINTER);
    } else if (pQueueIsEmpty(queue)) {
        fprintf(stderr, EMPTY_DATA_STRUCTURE_MESSAGE, "priority queue data structure");
        exit(EMPTY_DATA_STRUCTURE);
    }

    return queue->arr[queue->fPointer++];

}






/** This function will take the queue address as a parameter,
    then it will return the rear  item address in the queue,
    without removing the item from the queue.
 * @param queue the queue address
 * @return it will return the front item of the queue
 */

void *pQueuePeek(PriorityQueue *queue) {
    if (queue == NULL) {
        fprintf(stderr, NULL_POINTER_MESSAGE, "queue pointer", "priority queue data structure");
        exit(NULL_POINTER);
    } else if (pQueueIsEmpty(queue)) {
        fprintf(stderr, EMPTY_DATA_STRUCTURE_MESSAGE, "priority queue data structure");
        exit(EMPTY_DATA_STRUCTURE);
    }

    return queue->arr[queue->fPointer];

}







/** This function will take the queue address as a parameter,
    then it will return the number of the items in the queue.
 * @param queue the queue address
 * @return it will return the number of items in the queue
 */

int pQueueGetLength(PriorityQueue *queue) {

    if (queue == NULL) {
        fprintf(stderr, NULL_POINTER_MESSAGE, "queue pointer", "priority queue data structure");
        exit(NULL_POINTER);
    }

    return queue->count - queue->fPointer;
}







/** This function will take the queue address as a parameter,
    then it will return one (1) if the queue is empty,
    other wise it will return zero (0).
 * @param queue the queue address
 * @return it will return one if the queue is empty, other wise it will return zero
 */

int pQueueIsEmpty(PriorityQueue *queue) {

    if (queue == NULL) {
        fprintf(stderr, NULL_POINTER_MESSAGE, "queue pointer", "priority queue data structure");
        exit(NULL_POINTER);
    }

    return queue->count == queue->fPointer;
}







/** This function will take the queue address as a parameter,
    then it will return a double void pointer array that contains a copy of all the queue items.
 * @param queue the queue address
 * @return it will return a double void pointer array consisting of the queue items
 */

void **pQueueToArray(PriorityQueue *queue) {

    if (queue == NULL) {
        fprintf(stderr, NULL_POINTER_MESSAGE, "queue pointer", "priority queue data structure");
        exit(NULL_POINTER);
    }

    void **arr = (void **) malloc(sizeof(void *) * pQueueGetLength(queue));
    if (arr == NULL) {
        fprintf(stderr, FAILED_ALLOCATION_MESSAGE, "to array", "priority queue data structure");
        exit(FAILED_ALLOCATION);
    }

    for (int i = queue->fPointer; i < queue->count; i++)
        arr[i - queue->fPointer] = queue->arr[i];

    return arr;

}






/** This function will take the queue address as a parameter,
    then it will destroy and free all the items in the queue,
    without destroying the queue it self.
 * @param queue the queue address
 */

void clearPQueue(PriorityQueue *queue) {

    if (queue == NULL) {
        fprintf(stderr, NULL_POINTER_MESSAGE, "queue pointer", "priority queue data structure");
        exit(NULL_POINTER);
    }

    while (queue->count != queue->fPointer)
        queue->freeItem(pQueueDequeue(queue));

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

void swapItems(void **arr, int index1, int index2) {
    void *temp = arr[index1];
    arr[index1] = arr[index2];
    arr[index2] = temp;
}