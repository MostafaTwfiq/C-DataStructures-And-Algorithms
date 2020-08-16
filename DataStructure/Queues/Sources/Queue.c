#include  "../Headers/Queue.h"
#include "../../../System/Utils.h"
#include "../../../Unit Test/CuTest/CuTest.h"


/** Function Initializes Queue on Heap using malloc and returns pointer to it.
 *
 * @param size Size of the data to be stored by the Queue.
 * @return Return Pointer ot Queue on the Heap.
 */

Queue *queueInitialization(void (*freeFun)(void *)) {

    if (freeFun == NULL) {
#ifdef C_DATASTRUCTURES_ERRORSTESTSTRUCT_H
        ERROR_TEST->errorCode = INVALID_ARG;
        return NULL;
#else
        fprintf(stderr, INVALID_ARG_MESSAGE, "free function", "queue data structure");
        exit(INVALID_ARG);
#endif

    }

    Queue *queue = (Queue *) malloc(sizeof(*queue));

    if (queue == NULL) {
#ifdef C_DATASTRUCTURES_ERRORSTESTSTRUCT_H
        ERROR_TEST->errorCode = FAILED_ALLOCATION;
        return NULL;
#else
        fprintf(stderr, FAILED_ALLOCATION_MESSAGE, "data structure", "queue data structure");
        exit(FAILED_ALLOCATION);
#endif

    }

    queue->freeItem = freeFun;
    queue->allocated = 10;
    queue->memory = (void **) malloc(sizeof(void *) * queue->allocated);

    if (queue->memory == NULL) {
#ifdef C_DATASTRUCTURES_ERRORSTESTSTRUCT_H
        ERROR_TEST->errorCode = FAILED_ALLOCATION;
        return NULL;
#else
        fprintf(stderr, FAILED_ALLOCATION_MESSAGE, "items memory", "queue data structure");
        exit(FAILED_ALLOCATION);
#endif

    }

    queue->front = queue->rear = 0;

    return queue;

}


/** Function that takes a pointer to previously externally allocated object and enqueues it.
 *
 * @param arrayQueue Pointer to the Queue on the heap.
 * @param data Pointer to the data to be stored on the heap.
 */

void queueEnqueue(Queue *arrayQueue, void *data) {

    if (arrayQueue == NULL) {
#ifdef C_DATASTRUCTURES_ERRORSTESTSTRUCT_H
        ERROR_TEST->errorCode = NULL_POINTER;
        return;
#else
        fprintf(stderr, NULL_POINTER_MESSAGE, "queue", "queue data structure");
        exit(NULL_POINTER);
#endif

    } else if (data == NULL) {
#ifdef C_DATASTRUCTURES_ERRORSTESTSTRUCT_H
        ERROR_TEST->errorCode = INVALID_ARG;
        return;
#else
        fprintf(stderr, INVALID_ARG_MESSAGE, "data pointer", "queue data structure");
        exit(INVALID_ARG);
#endif

    }

    if (arrayQueue->allocated == arrayQueue->rear) {
        arrayQueue->allocated *= 2;
        void **tempArr = (void **) malloc(sizeof(void *) * arrayQueue->allocated);
        if (tempArr == NULL) {
#ifdef C_DATASTRUCTURES_ERRORSTESTSTRUCT_H
            ERROR_TEST->errorCode = FAILED_ALLOCATION;
            return;
#else
            fprintf(stderr, FAILED_ALLOCATION_MESSAGE, "items memory", "queue data structure");
            exit(FAILED_ALLOCATION);
#endif

        }

        memcpy(tempArr, arrayQueue->memory + arrayQueue->front,
               sizeof(void *) * (arrayQueue->rear - arrayQueue->front));

        free(arrayQueue->memory);
        arrayQueue->memory = tempArr;
        arrayQueue->rear -= arrayQueue->front;
        arrayQueue->front = 0;
    }

    arrayQueue->memory[arrayQueue->rear++] = data;

}


/** Function that returns a pointer to previously allocated objected and dequeue it from a queue.
 *
 * @param arrayQueue Pointer to the Queue on the heap.
 * @return Pointer to the previously queued data on the heap.
 */

void *queueDequeue(Queue *arrayQueue) {
    if (arrayQueue == NULL) {
#ifdef C_DATASTRUCTURES_ERRORSTESTSTRUCT_H
        ERROR_TEST->errorCode = NULL_POINTER;
        return NULL;
#else
        fprintf(stderr, NULL_POINTER_MESSAGE, "queue", "queue data structure");
        exit(NULL_POINTER);
#endif

    } else if (queueIsEmpty(arrayQueue)) {
#ifdef C_DATASTRUCTURES_ERRORSTESTSTRUCT_H
        ERROR_TEST->errorCode = EMPTY_DATA_STRUCTURE;
        return NULL;
#else
        fprintf(stderr, EMPTY_DATA_STRUCTURE_MESSAGE, "queue data structure");
        exit(EMPTY_DATA_STRUCTURE);
#endif

    }

    return arrayQueue->memory[arrayQueue->front++];

}


/** Destroys the Queue and its allocated objects.
 *
 * @param arrayQueue Pointer to the Queue on the heap.
 */

void destroyQueue(void *arrayQueue) {

    if (arrayQueue == NULL) {
#ifdef C_DATASTRUCTURES_ERRORSTESTSTRUCT_H
        ERROR_TEST->errorCode = NULL_POINTER;
        return;
#else
        fprintf(stderr, NULL_POINTER_MESSAGE, "queue", "queue data structure");
        exit(NULL_POINTER);
#endif

    }

    clearQueue(arrayQueue);

    free(((Queue *) arrayQueue)->memory);
    free(arrayQueue);

}


/** Clear the elements stored on the Queue.
 *
 * @param arrayQueue Pointer to the Queue on the heap.
 */

void clearQueue(Queue *arrayQueue) {
    if (arrayQueue == NULL) {
#ifdef C_DATASTRUCTURES_ERRORSTESTSTRUCT_H
        ERROR_TEST->errorCode = NULL_POINTER;
        return;
#else
        fprintf(stderr, NULL_POINTER_MESSAGE, "queue", "queue data structure");
        exit(NULL_POINTER);
#endif

    }


    for (int i = arrayQueue->front; i < arrayQueue->rear; i++)
        arrayQueue->freeItem(arrayQueue->memory[i]);

    arrayQueue->front = arrayQueue->rear = 0;

}


/** Returns whether queue is empty or not.
 *
 * @param arrayQueue Pointer to the Queue on the heap.
 * @return returns short integer 1 if Empty else 0.
 */

int queueIsEmpty(Queue *arrayQueue) {
    if (arrayQueue == NULL) {
#ifdef C_DATASTRUCTURES_ERRORSTESTSTRUCT_H
        ERROR_TEST->errorCode = NULL_POINTER;
        return -1;
#else
        fprintf(stderr, NULL_POINTER_MESSAGE, "queue", "queue data structure");
        exit(NULL_POINTER);
#endif

    }

    return (short) (arrayQueue->rear == arrayQueue->front);

}


/** Returns the number of elements currently stored in the Queue.
 *
 * @param arrayQueue Pointer to the Queue on the heap.
 * @return integer length of array.
 */

int queueGetLength(Queue *arrayQueue) {
    if (arrayQueue == NULL) {
#ifdef C_DATASTRUCTURES_ERRORSTESTSTRUCT_H
        ERROR_TEST->errorCode = NULL_POINTER;
        return -1;
#else
        fprintf(stderr, NULL_POINTER_MESSAGE, "queue", "queue data structure");
        exit(NULL_POINTER);
#endif

    }

    return arrayQueue->rear - arrayQueue->front;

}


/** This function will take an array of items pointers, then it will enqueue all the array items.
 *
 * @param arrayQueue Pointer to the Queue on the heap.
 * @param arr Pointer to an Externally defined array on the heap.
 * @param arrLength Number of elements of the Externally Defined Array.
 */

void queueEnqueueAll(Queue *arrayQueue, void **arr, int arrLength) {

    if (arrayQueue == NULL) {
#ifdef C_DATASTRUCTURES_ERRORSTESTSTRUCT_H
        ERROR_TEST->errorCode = NULL_POINTER;
        return;
#else
        fprintf(stderr, NULL_POINTER_MESSAGE, "queue", "queue data structure");
        exit(NULL_POINTER);
#endif

    } else if (arr == NULL) {
#ifdef C_DATASTRUCTURES_ERRORSTESTSTRUCT_H
        ERROR_TEST->errorCode = INVALID_ARG;
        return;
#else
        fprintf(stderr, INVALID_ARG_MESSAGE, "items array", "queue data structure");
        exit(INVALID_ARG);
#endif

    }

    for (int i = 0; i < arrLength; i++)
        queueEnqueue(arrayQueue, arr[i]);

}


/** Returns the first item that was enqueued at the queue.
 *
* @param arrayQueue Pointer to the Queue on the heap
* @return Pointer the first enqueued Object
*/

void *queuePeek(Queue *arrayQueue) {
    if (arrayQueue == NULL) {
#ifdef C_DATASTRUCTURES_ERRORSTESTSTRUCT_H
        ERROR_TEST->errorCode = NULL_POINTER;
        return NULL;
#else
        fprintf(stderr, NULL_POINTER_MESSAGE, "queue", "queue data structure");
        exit(NULL_POINTER);
#endif

    } else if (queueIsEmpty(arrayQueue)) {
#ifdef C_DATASTRUCTURES_ERRORSTESTSTRUCT_H
        ERROR_TEST->errorCode = EMPTY_DATA_STRUCTURE;
        return NULL;
#else
        fprintf(stderr, EMPTY_DATA_STRUCTURE_MESSAGE, "queue data structure");
        exit(EMPTY_DATA_STRUCTURE);
#endif
    }

    return arrayQueue->memory[arrayQueue->front];

}


/** Converts a queue to an Array.
 *
 * @param arrayQueue Pointer to the Queue on the heap.
 * @return Pointer to an allocated array on the heap.
 */

void **queueToArray(Queue *arrayQueue) {
    if (arrayQueue == NULL) {
#ifdef C_DATASTRUCTURES_ERRORSTESTSTRUCT_H
        ERROR_TEST->errorCode = NULL_POINTER;
        return NULL;
#else
        fprintf(stderr, NULL_POINTER_MESSAGE, "queue", "queue data structure");
        exit(NULL_POINTER);
#endif

    }

    void **array = (void **) malloc(sizeof(void *) * queueGetLength(arrayQueue));
    if (array == NULL) {
#ifdef C_DATASTRUCTURES_ERRORSTESTSTRUCT_H
        ERROR_TEST->errorCode = FAILED_ALLOCATION;
        return NULL;
#else
        fprintf(stderr, FAILED_ALLOCATION_MESSAGE, "to array", "queue data structure");
        exit(FAILED_ALLOCATION);
#endif

    }

    for (int i = arrayQueue->front; i < arrayQueue->rear; i++)
        array[i] = arrayQueue->memory[i];

    return array;

}
