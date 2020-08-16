#include "../Headers/LinkedListQueue.h"
#include "../../../System/Utils.h"
#include "../../LinkedLists/Headers/LinkedList.h"
#include "../../../Unit Test/CuTest/CuTest.h"


/** This function will take the size of the items type as a parameter,
 * then it will initialize a new linked list queue, and return it's address.
 *
 * @param freeFun the free function address that will be called to free the queue items
 */

LinkedListQueue *linkedListQueueInitialization(void (*freeFun)(void *)) {
    if (freeFun == NULL) {
#ifdef C_DATASTRUCTURES_ERRORSTESTSTRUCT_H
        ERROR_TEST->errorCode = INVALID_ARG;
        return NULL;
#else
        fprintf(stderr, INVALID_ARG_MESSAGE, "free function pointer", "linked list queue data structure");
        exit(INVALID_ARG);
#endif

    }

    LinkedListQueue *queue = (LinkedListQueue *) malloc(sizeof(LinkedListQueue));
    if (queue == NULL) {
#ifdef C_DATASTRUCTURES_ERRORSTESTSTRUCT_H
        ERROR_TEST->errorCode = FAILED_ALLOCATION;
        return NULL;
#else
        fprintf(stderr, FAILED_ALLOCATION_MESSAGE, "queue", "linked list queue data structure");
        exit(FAILED_ALLOCATION);
#endif
    }

    queue->linkedList = linkedListInitialization(freeFun, NULL);

    return queue;
}


/** This function will take the queue address, and the item address as a parameter,
 * then it will push the item into the queue.
 *
 * @param queue the queue address
 * @param item the new item address
 */

void lLQueueEnqueue(LinkedListQueue *queue, void *item) {

    if (queue == NULL) {
#ifdef C_DATASTRUCTURES_ERRORSTESTSTRUCT_H
        ERROR_TEST->errorCode = NULL_POINTER;
        return;
#else
        fprintf(stderr, NULL_POINTER_MESSAGE, "queue", "linked list queue data structure");
        exit(NULL_POINTER);
#endif

    } else if (item == NULL) {
#ifdef C_DATASTRUCTURES_ERRORSTESTSTRUCT_H
        ERROR_TEST->errorCode = INVALID_ARG;
        return;
#else
        fprintf(stderr, INVALID_ARG_MESSAGE, "item pointer", "linked list queue data structure");
        exit(INVALID_ARG);
#endif

    }

    linkedListAddLast(queue->linkedList, item);

}


/** This function will take the queue address, the array address, and the array length as a parameter,
 * then it will add all the items in the array to the queue in order.
 *
 * @param queue the queue address
 * @param arr the array address that will be added to the queue
 * @param arrLength the length of the array
 */

void lLQueueEnqueueAll(LinkedListQueue *queue, void **arr, int arrLength) {
    if (queue == NULL) {
#ifdef C_DATASTRUCTURES_ERRORSTESTSTRUCT_H
        ERROR_TEST->errorCode = NULL_POINTER;
        return;
#else
        fprintf(stderr, NULL_POINTER_MESSAGE, "queue", "linked list queue data structure");
        exit(NULL_POINTER);
#endif

    } else if (arr == NULL) {
#ifdef C_DATASTRUCTURES_ERRORSTESTSTRUCT_H
        ERROR_TEST->errorCode = INVALID_ARG;
        return;
#else
        fprintf(stderr, INVALID_ARG_MESSAGE, "items array pointer", "linked list queue data structure");
        exit(INVALID_ARG);
#endif

    }

    for (int i = 0; i < arrLength; i++)
        linkedListAddLast(queue->linkedList, arr[i]);

}


/** This  function will take the queue address as a parameter,
 * then it will return the first item in the queue,
 * then the item will be deleted from the queue.
 *
 * Note: if the queue i empty the program will be terminated.
 *
 * @param queue the queue address
 * @return it will return the (first in) item address as a void pointer
 */

void *lLQueueDequeue(LinkedListQueue *queue) {

    if (queue == NULL) {
#ifdef C_DATASTRUCTURES_ERRORSTESTSTRUCT_H
        ERROR_TEST->errorCode = NULL_POINTER;
        return NULL;
#else
        fprintf(stderr, NULL_POINTER_MESSAGE, "queue", "linked list queue data structure");
        exit(NULL_POINTER);
#endif

    } else if (lLQueueIsEmpty(queue)) {
#ifdef C_DATASTRUCTURES_ERRORSTESTSTRUCT_H
        ERROR_TEST->errorCode = EMPTY_DATA_STRUCTURE;
        return NULL;
#else
        fprintf(stderr, EMPTY_DATA_STRUCTURE_MESSAGE, "linked list queue data structure");
        exit(EMPTY_DATA_STRUCTURE);
#endif

    }

    void *item = linkedListGetFirst(queue->linkedList);
    linkedListDeleteFirstWtoFr(queue->linkedList);

    return item;

}


/** This function will take the queue address as a parameter,
 * then it will return the first item in the queue without removing the item from the queue.
 *
 * Note: if the queue i empty the program will be terminated.
 *
 * @param queue the queue address
 * @return it will return the (first in) item address as a void pointer
 */

void *lLQueuePeek(LinkedListQueue *queue) {

    if (queue == NULL) {
#ifdef C_DATASTRUCTURES_ERRORSTESTSTRUCT_H
        ERROR_TEST->errorCode = NULL_POINTER;
        return NULL;
#else
        fprintf(stderr, NULL_POINTER_MESSAGE, "queue", "linked list queue data structure");
        exit(NULL_POINTER);
#endif

    } else if (lLQueueIsEmpty(queue)) {
#ifdef C_DATASTRUCTURES_ERRORSTESTSTRUCT_H
        ERROR_TEST->errorCode = EMPTY_DATA_STRUCTURE;
        return NULL;
#else
        fprintf(stderr, EMPTY_DATA_STRUCTURE_MESSAGE, "linked list queue data structure");
        exit(EMPTY_DATA_STRUCTURE);
#endif

    }

    void *item = linkedListGetFirst(queue->linkedList);

    return item;

}


/** This function will take the queue address as a parameter,
 * then it will return the number of the elements in the array.
 *
 * @param queue the queue  address
 * @return it will return the number of items in the queue
 */

int lLQueueGetLength(LinkedListQueue *queue) {
    if (queue == NULL) {
#ifdef C_DATASTRUCTURES_ERRORSTESTSTRUCT_H
        ERROR_TEST->errorCode = NULL_POINTER;
        return -1;
#else
        fprintf(stderr, NULL_POINTER_MESSAGE, "queue", "linked list queue data structure");
        exit(NULL_POINTER);
#endif

    }

    return linkedListGetLength(queue->linkedList);

}


/** This function will take the queue address as a parameter,
 * then it will return one (1) if the queue is empty, other wise it will return zero (0).
 *
 * @param queue the queue address
 * @return it will return one if the queue is empty other wise it will return zero
 */

int lLQueueIsEmpty(LinkedListQueue *queue) {

    if (queue == NULL) {
#ifdef C_DATASTRUCTURES_ERRORSTESTSTRUCT_H
        ERROR_TEST->errorCode = NULL_POINTER;
        return -1;
#else
        fprintf(stderr, NULL_POINTER_MESSAGE, "queue", "linked list queue data structure");
        exit(NULL_POINTER);
#endif

    }

    return linkedListIsEmpty(queue->linkedList);

}


/** This function will take the queue address as a parameter,
 * then it will return a void array that contains all the items in the queue.
 *
 * @param queue the queue address
 * @return it will return a double void array that contains a copy of all the items in the queue
 */

void **lLQueueToArray(LinkedListQueue *queue) {

    if (queue == NULL) {
#ifdef C_DATASTRUCTURES_ERRORSTESTSTRUCT_H
        ERROR_TEST->errorCode = NULL_POINTER;
        return NULL;
#else
        fprintf(stderr, NULL_POINTER_MESSAGE, "queue", "linked list queue data structure");
        exit(NULL_POINTER);
#endif

    }

    return linkedListToArray(queue->linkedList);

}


/** This function will take the queue address as a parameter,
 * then it will delete and free all the items in the queue without destroying the queue.
 *
 * @param queue the queue address
 */

void clearLLQueue(LinkedListQueue *queue) {

    if (queue == NULL) {
#ifdef C_DATASTRUCTURES_ERRORSTESTSTRUCT_H
        ERROR_TEST->errorCode = NULL_POINTER;
        return;
#else
        fprintf(stderr, NULL_POINTER_MESSAGE, "queue", "linked list queue data structure");
        exit(NULL_POINTER);
#endif

    }

    linkedListClear(queue->linkedList);
}


/** This function will take the queue address as a parameter,
 * then it will destroy and free all the item in the queue then it will also free the queue.
 *
 * @param queue the queue address
 */

void destroyLLQueue(void *queue) {

    if (queue == NULL) {
#ifdef C_DATASTRUCTURES_ERRORSTESTSTRUCT_H
        ERROR_TEST->errorCode = NULL_POINTER;
        return;
#else
        fprintf(stderr, NULL_POINTER_MESSAGE, "queue", "linked list queue data structure");
        exit(NULL_POINTER);
#endif

    }

    destroyLinkedList(((LinkedListQueue *) queue)->linkedList);
    free(queue);

}