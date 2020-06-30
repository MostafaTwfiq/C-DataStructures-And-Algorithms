#include "../Headers/StackQueue.h"




void transferItemsToSecondStack(Stack *fStack, Stack *sStack);




/** This function will take the size of the type that will be stored in the queue as a parameter,
    then it will initialize the queue and set up it's field,
    then it will return the queue address.
 * @param sizeOfType
 * @return
 */

SQueue *stackQueueInitialization(int sizeOfType) {
    SQueue *queue = (SQueue *) malloc(sizeof(SQueue));

    queue->fStack = stackInitialization(sizeOfType);
    queue->sStack = stackInitialization(sizeOfType);

    return queue;

}




/** This function will take the queue address, and the item address as a parameters,
    then it will push the item into the queue.
 * @param queue
 * @param item
 */

void sQueueEnqueue(SQueue *queue, void *item) {
    if(queue == NULL) {
        fprintf( stderr , "Illegal argument, queue is null." );
        exit( NULL_POINTER );
    }

    pushStack(queue->fStack, item);

}





/** This function will take the queue address, the items array pointer, and the length of the array as a parameters,
    then it will push all the items in the array into the queue.
 * @param queue
 * @param items
 * @param itemsLength
 */

void sQueueAddAll(SQueue *queue, void **items, int itemsLength) {
    if(queue == NULL) {
        fprintf( stderr , "Illegal argument, queue is null." );
        exit( NULL_POINTER );
    } else if (items == NULL)
        return;

    for (int i = 0; i < itemsLength; i++) {
        pushStack(queue->fStack, items[i]);
    }

}





/** This function will take the queue address as a parameter,
 * then it will return the top item in the queue.
 * @param queue
 * @return
 */

void *sQueueDequeue(SQueue *queue) {
    if(queue == NULL) {
        fprintf( stderr , "Illegal argument, queue is null." );
        exit( NULL_POINTER );
    } else if (sQueueIsEmpty(queue)) {
        fprintf( stderr , "queue is empty." );
        exit(-3);
    }

    if (isEmptyStack(queue->sStack))
        transferItemsToSecondStack(queue->fStack, queue->sStack);

    return popStack(queue->sStack);
}




/** This function will two stack addresses as a parameters,
    then it will pop the items in first stack and push it into the second stack.
 * Note: this function should be called only from the queue functions.
 * @param fStack
 * @param sStack
 */

void transferItemsToSecondStack(Stack *fStack, Stack *sStack) {
    while (!isEmptyStack(fStack))
        pushStack(sStack, popStack(fStack));

}





/** This function will take the queue address as a parameter,
    then it will return the top of the queue with out removing the item from the queue.
 * @param queue
 * @return
 */

void *sQueuePeek(SQueue *queue) {
    if(queue == NULL) {
        fprintf( stderr , "Illegal argument, queue is null." );
        exit( NULL_POINTER );
    } else if (sQueueIsEmpty(queue)) {
        fprintf( stderr , "queue is empty." );
        exit(-3);
    }

    if (isEmptyStack(queue->sStack))
        transferItemsToSecondStack(queue->fStack, queue->sStack);

    return peekStack(queue->sStack);

}




/** This function will take the queue address as a parameter,
    then it will return the number of items in the queue.
 * @param queue
 * @return
 */

int sQueueGetLength(SQueue *queue) {

    if(queue == NULL) {
        fprintf( stderr , "Illegal argument, queue is null." );
        exit( NULL_POINTER );
    }

    return getStackLength(queue->fStack) + getStackLength(queue->sStack);
}





/** This function will take the queue address as a parameter,
    then it will return one (1) if the queue is empty,
    other wise it will return zero (0).
 * @param queue
 * @return
 */

int sQueueIsEmpty(SQueue *queue) {

    if(queue == NULL) {
        fprintf( stderr , "Illegal argument, queue is null." );
        exit( NULL_POINTER );
    }

    return sQueueGetLength(queue) == 0;
}





/** This function will take the queue address as a parameter,
 * then it will copy all the items of the queue in order into a void array,
 * then it will return the array address.
 * @param queue
 * @return
 */

void **sQueueToArray(SQueue *queue) {

    if(queue == NULL) {
        fprintf( stderr , "Illegal argument, queue is null." );
        exit( NULL_POINTER );
    }

    int length = sQueueGetLength(queue);
    void **arr = (void **) malloc(sizeof(void *) * length);

    for (int i = 0; i < length; i++) {
        void *item = sQueueDequeue(queue);
        arr[i] = (void *) malloc(queue->fStack->sizeOfType);
        memcpy(arr[i], item, queue->fStack->sizeOfType);
        sQueueEnqueue(queue, item);
    }

    return arr;

}




/** This function will take the address of the queue as a parameter,
    then it will destroy and remove all the items from the queue,
    without destroying the queue.
 * @param queue
 */

void clearSQueue(SQueue *queue) {

    if(queue == NULL) {
        fprintf( stderr , "Illegal argument, queue is null." );
        exit( NULL_POINTER );
    }

    StackClear(queue->fStack);
    StackClear(queue->sStack);

}





/** This function will take the queue address as a parameter,
 * then it will destroy and free the queue and all it's items.
 * @param queue
 */

void destroySQueue(SQueue *queue) {

    if(queue == NULL) {
        fprintf( stderr , "Illegal argument, queue is null." );
        exit( NULL_POINTER );
    }

    StackDestroy(queue->fStack);
    StackDestroy(queue->sStack);
    free(queue);

}