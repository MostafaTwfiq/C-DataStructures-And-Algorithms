#include "../Headers/StackQueue.h"
#include "../../Stacks/Headers/Stack.h"
#include "../../../System/Utils.h"
#include "../../../Unit Test/CuTest/CuTest.h"


void transferItemsToSecondStack(Stack *fStack, Stack *sStack);


/** This function will take the size of the type that will be stored in the queue as a parameter,
 * then it will initialize the queue and set up it's field,
 * then it will return the queue address.
 *
 * @param freeItem the freeing item function address, that will be called to free the queue items
 * @return it will return the initialized queue address
 */

SQueue *stackQueueInitialization(void (*freeItem)(void *)) {
    if (freeItem == NULL) {
#ifdef C_DATASTRUCTURES_ERRORSTESTSTRUCT_H
        ERROR_TEST->errorCode = INVALID_ARG;
        return NULL;
#else
        fprintf(stderr, INVALID_ARG_MESSAGE, "free function pointer", "stack queue data structure");
        exit(INVALID_ARG);
#endif

    }

    SQueue *queue = (SQueue *) malloc(sizeof(SQueue));
    if (queue == NULL) {
#ifdef C_DATASTRUCTURES_ERRORSTESTSTRUCT_H
        ERROR_TEST->errorCode = FAILED_ALLOCATION;
        return NULL;
#else
        fprintf(stderr, FAILED_ALLOCATION_MESSAGE, "queue", "stack queue data structure");
        exit(FAILED_ALLOCATION);
#endif

    }

    queue->fStack = stackInitialization(freeItem);
    queue->sStack = stackInitialization(freeItem);

    return queue;

}


/** This function will take the queue address, and the item address as a parameters,
 * then it will push the item into the queue.
 *
 * @param queue the queue address
 * @param item the new item address
 */

void sQueueEnqueue(SQueue *queue, void *item) {
    if (queue == NULL) {
#ifdef C_DATASTRUCTURES_ERRORSTESTSTRUCT_H
        ERROR_TEST->errorCode = NULL_POINTER;
        return;
#else
        fprintf(stderr, NULL_POINTER_MESSAGE, "queue", "stack queue data structure");
        exit(NULL_POINTER);
#endif

    } else if (item == NULL) {
#ifdef C_DATASTRUCTURES_ERRORSTESTSTRUCT_H
        ERROR_TEST->errorCode = INVALID_ARG;
        return;
#else
        fprintf(stderr, INVALID_ARG_MESSAGE, "item pointer", "stack queue data structure");
        exit(INVALID_ARG);
#endif

    }

    stackPush(queue->fStack, item);

}


/** This function will take the queue address, the items array pointer, and the length of the array as a parameters,
 * then it will push all the items in the array into the queue.
 *
 * @param queue the queue address
 * @param items the items array address
 * @param itemsLength the length of the new items array
 */

void sQueueAddAll(SQueue *queue, void **items, int itemsLength) {
    if (queue == NULL) {
#ifdef C_DATASTRUCTURES_ERRORSTESTSTRUCT_H
        ERROR_TEST->errorCode = NULL_POINTER;
        return;
#else
        fprintf(stderr, NULL_POINTER_MESSAGE, "queue", "stack queue data structure");
        exit(NULL_POINTER);
#endif

    } else if (items == NULL) {
#ifdef C_DATASTRUCTURES_ERRORSTESTSTRUCT_H
        ERROR_TEST->errorCode = INVALID_ARG;
        return;
#else
        fprintf(stderr, INVALID_ARG_MESSAGE, "items array pointer", "stack queue data structure");
        exit(INVALID_ARG);
#endif

    }

    for (int i = 0; i < itemsLength; i++)
        stackPush(queue->fStack, items[i]);

}


/** This function will take the queue address as a parameter,
 * then it will return the top item in the queue.
 *
 * @param queue the queue address
 * @return it will return the (first in) item in the queue
 */

void *sQueueDequeue(SQueue *queue) {
    if (queue == NULL) {
#ifdef C_DATASTRUCTURES_ERRORSTESTSTRUCT_H
        ERROR_TEST->errorCode = NULL_POINTER;
        return NULL;
#else
        fprintf(stderr, NULL_POINTER_MESSAGE, "queue", "stack queue data structure");
        exit(NULL_POINTER);
#endif

    } else if (sQueueIsEmpty(queue)) {
#ifdef C_DATASTRUCTURES_ERRORSTESTSTRUCT_H
        ERROR_TEST->errorCode = EMPTY_DATA_STRUCTURE;
        return NULL;
#else
        fprintf(stderr, EMPTY_DATA_STRUCTURE_MESSAGE, "stack queue data structure");
        exit(EMPTY_DATA_STRUCTURE);
#endif

    }

    if (stackIsEmpty(queue->sStack))
        transferItemsToSecondStack(queue->fStack, queue->sStack);

    return stackPop(queue->sStack);

}


/** This function will two stack addresses as a parameters,
 * then it will pop the items in first stack and push it into the second stack.
 *
 * Note: this function should be called only from the queue functions.
 *
 * @param fStack the first stack address
 * @param sStack the second stack address
 */

void transferItemsToSecondStack(Stack *fStack, Stack *sStack) {
    while (!stackIsEmpty(fStack))
        stackPush(sStack, stackPop(fStack));

}


/** This function will take the queue address as a parameter,
 * then it will return the top of the queue with out removing the item from the queue.
 *
 * @param queue the queue address
 * @return it will return the (first in) item in the queue
 */

void *sQueuePeek(SQueue *queue) {
    if (queue == NULL) {
#ifdef C_DATASTRUCTURES_ERRORSTESTSTRUCT_H
        ERROR_TEST->errorCode = NULL_POINTER;
        return NULL;
#else
        fprintf(stderr, NULL_POINTER_MESSAGE, "queue", "stack queue data structure");
        exit(NULL_POINTER);
#endif

    } else if (sQueueIsEmpty(queue)) {
#ifdef C_DATASTRUCTURES_ERRORSTESTSTRUCT_H
        ERROR_TEST->errorCode = EMPTY_DATA_STRUCTURE;
        return NULL;
#else
        fprintf(stderr, EMPTY_DATA_STRUCTURE_MESSAGE, "stack queue data structure");
        exit(EMPTY_DATA_STRUCTURE);
#endif

    }

    if (stackIsEmpty(queue->sStack))
        transferItemsToSecondStack(queue->fStack, queue->sStack);

    return stackPeek(queue->sStack);

}


/** This function will take the queue address as a parameter,
 * then it will return the number of items in the queue.
 *
 * @param queue the queue address
 * @return it will return the number of items in the queue
 */

int sQueueGetLength(SQueue *queue) {

    if (queue == NULL) {
#ifdef C_DATASTRUCTURES_ERRORSTESTSTRUCT_H
        ERROR_TEST->errorCode = NULL_POINTER;
        return -1;
#else
        fprintf(stderr, NULL_POINTER_MESSAGE, "queue", "stack queue data structure");
        exit(NULL_POINTER);
#endif

    }

    return stackGetLength(queue->fStack) + stackGetLength(queue->sStack);

}


/** This function will take the queue address as a parameter,
 * then it will return one (1) if the queue is empty,
 * other wise it will return zero (0).
 *
 * @param queue the queue address
 * @return it will return one if the queue is empty, other wise it will return zero
 */

int sQueueIsEmpty(SQueue *queue) {

    if (queue == NULL) {
#ifdef C_DATASTRUCTURES_ERRORSTESTSTRUCT_H
        ERROR_TEST->errorCode = NULL_POINTER;
        return -1;
#else
        fprintf(stderr, NULL_POINTER_MESSAGE, "queue", "stack queue data structure");
        exit(NULL_POINTER);
#endif

    }

    return sQueueGetLength(queue) == 0;

}


/** This function will take the queue address as a parameter,
 * then it will copy all the items of the queue in order into a void array,
 * then it will return the array address.
 *
 * @param queue the queue address
 * @return it will return a double void array pointer that contains the queue items
 */

void **sQueueToArray(SQueue *queue) {

    if (queue == NULL) {
#ifdef C_DATASTRUCTURES_ERRORSTESTSTRUCT_H
        ERROR_TEST->errorCode = NULL_POINTER;
        return NULL;
#else
        fprintf(stderr, NULL_POINTER_MESSAGE, "queue", "stack queue data structure");
        exit(NULL_POINTER);
#endif

    }

    int length = sQueueGetLength(queue);
    void **arr = (void **) malloc(sizeof(void *) * length);
    if (arr == NULL) {
#ifdef C_DATASTRUCTURES_ERRORSTESTSTRUCT_H
        ERROR_TEST->errorCode = FAILED_ALLOCATION;
        return NULL;
#else
        fprintf(stderr, FAILED_ALLOCATION_MESSAGE, "to array", "stack queue data structure");
        exit(FAILED_ALLOCATION);
#endif

    }

    for (int i = 0; i < length; i++) {

        if (stackIsEmpty(queue->sStack))
            transferItemsToSecondStack(queue->fStack, queue->sStack);

        void *item = stackPop(queue->sStack);

        arr[i] = item;
        sQueueEnqueue(queue, item);

    }

    return arr;

}


/** This function will take the address of the queue as a parameter,
 * then it will destroy and remove all the items from the queue,
 * without destroying the queue.
 *
 * @param queue the queue address
 */

void clearSQueue(SQueue *queue) {

    if (queue == NULL) {
#ifdef C_DATASTRUCTURES_ERRORSTESTSTRUCT_H
        ERROR_TEST->errorCode = NULL_POINTER;
        return;
#else
        fprintf(stderr, NULL_POINTER_MESSAGE, "queue", "stack queue data structure");
        exit(NULL_POINTER);
#endif

    }

    clearStack(queue->fStack);
    clearStack(queue->sStack);

}


/** This function will take the queue address as a parameter,
 * then it will destroy and free the queue and all it's items.
 *
 * @param queue the queue address
 */

void destroySQueue(void *queue) {

    if (queue == NULL) {
#ifdef C_DATASTRUCTURES_ERRORSTESTSTRUCT_H
        ERROR_TEST->errorCode = NULL_POINTER;
        return;
#else
        fprintf(stderr, NULL_POINTER_MESSAGE, "queue", "stack queue data structure");
        exit(NULL_POINTER);
#endif

    }

    clearSQueue(queue);
    free(queue);

}