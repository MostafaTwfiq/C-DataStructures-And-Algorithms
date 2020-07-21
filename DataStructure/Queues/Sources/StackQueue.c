#include "../Headers/StackQueue.h"
#include "../../Stacks/Headers/Stack.h"
#include "../../../System/Utils.h"




void transferItemsToSecondStack(Stack *fStack, Stack *sStack);




/** This function will take the size of the type that will be stored in the queue as a parameter,
    then it will initialize the queue and set up it's field,
    then it will return the queue address.
 * @param freeItem the freeing item function address, that will be called to free the queue items
 * @return it will return the initialized queue address
 */

SQueue *stackQueueInitialization(void (*freeItem)(void *)) {
    if (freeItem == NULL) {
        fprintf(stderr, INVALID_ARG_MESSAGE, "free function pointer", "stack queue data structure");
        exit(INVALID_ARG);
    }

    SQueue *queue = (SQueue *) malloc(sizeof(SQueue));
    if (queue == NULL) {
        fprintf(stderr, FAILED_ALLOCATION_MESSAGE, "queue", "stack queue data structure");
        exit(FAILED_ALLOCATION);
    }

    queue->fStack = stackInitialization(freeItem);
    queue->sStack = stackInitialization(freeItem);

    return queue;

}




/** This function will take the queue address, and the item address as a parameters,
    then it will push the item into the queue.
 * @param queue the queue address
 * @param item the new item address
 */

void sQueueEnqueue(SQueue *queue, void *item) {
    if(queue == NULL) {
        fprintf(stderr , NULL_POINTER_MESSAGE, "queue", "stack queue data structure");
        exit(NULL_POINTER);
    } else if (item == NULL) {
        fprintf(stderr, INVALID_ARG_MESSAGE, "item pointer", "stack queue data structure");
        exit(INVALID_ARG);
    }

    pushStack(queue->fStack, item);

}





/** This function will take the queue address, the items array pointer, and the length of the array as a parameters,
    then it will push all the items in the array into the queue.
 * @param queue the queue address
 * @param items the items array address
 * @param itemsLength the length of the new items array
 */

void sQueueAddAll(SQueue *queue, void **items, int itemsLength) {
    if(queue == NULL) {
        fprintf(stderr , NULL_POINTER_MESSAGE, "queue", "stack queue data structure");
        exit(NULL_POINTER);
    } else if (items == NULL) {
        fprintf(stderr, INVALID_ARG_MESSAGE, "items array pointer", "stack queue data structure");
        exit(INVALID_ARG);
    }

    for (int i = 0; i < itemsLength; i++)
        pushStack(queue->fStack, items[i]);

}





/** This function will take the queue address as a parameter,
 * then it will return the top item in the queue.
 * @param queue the queue address
 * @return it will return the (first in) item in the queue
 */

void *sQueueDequeue(SQueue *queue) {
    if(queue == NULL) {
        fprintf(stderr , NULL_POINTER_MESSAGE, "queue", "stack queue data structure");
        exit(NULL_POINTER);
    } else if (sQueueIsEmpty(queue)) {
        fprintf(stderr, EMPTY_DATA_STRUCTURE_MESSAGE, "stack queue data structure");
        exit(EMPTY_DATA_STRUCTURE);
    }

    if (isEmptyStack(queue->sStack))
        transferItemsToSecondStack(queue->fStack, queue->sStack);

    return popStack(queue->sStack);

}




/** This function will two stack addresses as a parameters,
    then it will pop the items in first stack and push it into the second stack.
 * Note: this function should be called only from the queue functions.
 * @param fStack the first stack address
 * @param sStack the second stack address
 */

void transferItemsToSecondStack(Stack *fStack, Stack *sStack) {
    while (!isEmptyStack(fStack))
        pushStack(sStack, popStack(fStack));

}





/** This function will take the queue address as a parameter,
    then it will return the top of the queue with out removing the item from the queue.
 * @param queue the queue address
 * @return it will return the (first in) item in the queue
 */

void *sQueuePeek(SQueue *queue) {
    if(queue == NULL) {
        fprintf(stderr , NULL_POINTER_MESSAGE, "queue", "stack queue data structure");
        exit(NULL_POINTER);
    } else if (sQueueIsEmpty(queue)) {
        fprintf(stderr, EMPTY_DATA_STRUCTURE_MESSAGE, "stack queue data structure");
        exit(EMPTY_DATA_STRUCTURE);
    }

    if (isEmptyStack(queue->sStack))
        transferItemsToSecondStack(queue->fStack, queue->sStack);

    return peekStack(queue->sStack);

}




/** This function will take the queue address as a parameter,
    then it will return the number of items in the queue.
 * @param queue the queue address
 * @return it will return the number of items in the queue
 */

int sQueueGetLength(SQueue *queue) {

    if(queue == NULL) {
        fprintf(stderr , NULL_POINTER_MESSAGE, "queue", "stack queue data structure");
        exit(NULL_POINTER);
    }

    return getStackLength(queue->fStack) + getStackLength(queue->sStack);
}





/** This function will take the queue address as a parameter,
    then it will return one (1) if the queue is empty,
    other wise it will return zero (0).
 * @param queue the queue address
 * @return it will return one if the queue is empty, other wise it will return zero
 */

int sQueueIsEmpty(SQueue *queue) {

    if(queue == NULL) {
        fprintf(stderr , NULL_POINTER_MESSAGE, "queue", "stack queue data structure");
        exit(NULL_POINTER);
    }

    return sQueueGetLength(queue) == 0;
}





/** This function will take the queue address as a parameter,
 * then it will copy all the items of the queue in order into a void array,
 * then it will return the array address.
 * @param queue the queue address
 * @return it will return a double void array pointer that contains the queue items
 */

void **sQueueToArray(SQueue *queue) {

    if(queue == NULL) {
        fprintf(stderr , NULL_POINTER_MESSAGE, "queue", "stack queue data structure");
        exit(NULL_POINTER);
    }

    int length = sQueueGetLength(queue);
    void **arr = (void **) malloc(sizeof(void *) * length);
    if (arr == NULL) {
        fprintf(stderr, FAILED_ALLOCATION_MESSAGE, "to array", "stack queue data structure");
        exit(FAILED_ALLOCATION);
    }

    for (int i = 0; i < length; i++) {

        if (isEmptyStack(queue->sStack))
            transferItemsToSecondStack(queue->fStack, queue->sStack);

        void *item = popStack(queue->sStack);

        arr[i] = item;
        sQueueEnqueue(queue, item);

    }

    return arr;

}




/** This function will take the address of the queue as a parameter,
    then it will destroy and remove all the items from the queue,
    without destroying the queue.
 * @param queue the queue address
 */

void clearSQueue(SQueue *queue) {

    if(queue == NULL) {
        fprintf(stderr , NULL_POINTER_MESSAGE, "queue", "stack queue data structure");
        exit(NULL_POINTER);
    }

    StackClear(queue->fStack);
    StackClear(queue->sStack);

}





/** This function will take the queue address as a parameter,
 * then it will destroy and free the queue and all it's items.
 * @param queue the queue address
 */

void destroySQueue(SQueue *queue) {

    clearSQueue(queue);
    free(queue);

}