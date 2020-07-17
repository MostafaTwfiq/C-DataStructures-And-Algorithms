#include  "../Headers/ArrayQueue.h"
#include "../Headers/Utils.h"









/** Function Initializes Queue on Heap using malloc and returns pointer to it.
 * @param size Size of the data to be stored by the Queue.
 * @return Return Pointer ot Queue on the Heap.
 */

ArrayQueue* arrayQueueInitialization(void (*freeItem)(void *)) {

    if (freeItem == NULL) {
        fprintf(stderr, INVALID_ARG_MESSAGE, "free function", "array queue data structure");
        exit(INVALID_ARG);
    }

    ArrayQueue* queue =(ArrayQueue *) malloc(sizeof ( *queue ));

    if (queue == NULL) {
        fprintf(stderr, FAILED_ALLOCATION_MESSAGE, "data structure", "array queue data structure");
        exit(FAILED_ALLOCATION);
    }

    queue->freeItem =  freeItem;
    queue->allocated = 10;
    queue->memory = (void **) malloc(sizeof(void *) * queue->allocated);

    if (queue->memory == NULL) {
        fprintf(stderr, FAILED_ALLOCATION_MESSAGE, "items memory", "array queue data structure");
        exit(FAILED_ALLOCATION);
    }

    queue->front = queue->rear = 0;

    return queue;
}







/** Function that takes a pointer to previously externally allocated object and enqueues it.
 * @param arrayQueue Pointer to the Queue on the heap.
 * @param data Pointer to the data to be stored on the heap.
 */

void arrayQueueEnqueue(ArrayQueue* arrayQueue, void *data) {

    if (arrayQueue == NULL) {
        fprintf(stderr, INVALID_ARG_MESSAGE, "queue pointer", "array queue data structure");
        exit(INVALID_ARG);
    } else if (data == NULL) {
        fprintf(stderr, INVALID_ARG_MESSAGE, "data pointer", "array queue data structure");
        exit(INVALID_ARG);
    }

    if(arrayQueue->allocated ==  arrayQueue->rear){
        arrayQueue->allocated *= 2;
        void **tempArr = (void **) malloc(sizeof(void *) * arrayQueue->allocated);
        if (tempArr == NULL) {
            fprintf(stderr, FAILED_ALLOCATION_MESSAGE, "items memory", "array queue data structure");
            exit(FAILED_ALLOCATION);
        }

        memcpy(tempArr, arrayQueue->memory + sizeof(void *) * arrayQueue->front, sizeof(void *) * (arrayQueue->rear - arrayQueue->front) );
        free(arrayQueue->memory);
        arrayQueue->memory = tempArr;
        arrayQueue->rear -= arrayQueue->front;
        arrayQueue->front = 0;
    }

    arrayQueue->memory[arrayQueue->rear++] = data;

}








/** Function that returns a pointer to previously allocated objected and dequeue it.
 * from a queue.
 * @param arrayQueue Pointer to the Queue on the heap.
 * @return Pointer to the previously queued data on the heap.
 */

void* arrayQueueDequeue(ArrayQueue* arrayQueue) {
    if (arrayQueue == NULL) {
        fprintf(stderr, INVALID_ARG_MESSAGE, "queue pointer", "array queue data structure");
        exit(INVALID_ARG);
    } else if (arrayQueueIsEmpty(arrayQueue)) {
        fprintf(stderr, EMPTY_DATA_STRUCTURE_MESSAGE, "array queue data structure");
        exit(EMPTY_DATA_STRUCTURE);
    }

    return arrayQueue->memory[arrayQueue->front++];

}








/** Takes a reference pointer to print function and prints data in the queue.
 * @param arrayQueue Pointer to the Queue on the heap.
 * @param fptr pointer to an externally defined print function.
 */

void arrayQueueDisplay(ArrayQueue* arrayQueue, void (*fptr)(void *)) {
    if (arrayQueue == NULL) {
        fprintf(stderr, INVALID_ARG_MESSAGE, "queue pointer", "array queue data structure");
        exit(INVALID_ARG);
    } else if (fptr) {
        fprintf(stderr, INVALID_ARG_MESSAGE, "printf function pointer", "array queue data structure");
        exit(INVALID_ARG);
    }

    for (int i = arrayQueue->front; i < arrayQueue->rear; i++)
        fptr(arrayQueue->memory[i]);

}








/** Destroys the Queue and its allocated objects.
 * @param arrayQueue Pointer to the Queue on the heap.
 */

void arrayQueueDestroy(ArrayQueue* arrayQueue) {
    arrayQueueClear(arrayQueue);

    free(arrayQueue->memory);
    free(arrayQueue);

}









/** Clear the elements stored on the Queue.
 * @param arrayQueue Pointer to the Queue on the heap.
 */

void arrayQueueClear(ArrayQueue* arrayQueue) {
    if (arrayQueue == NULL) {
        fprintf(stderr, INVALID_ARG_MESSAGE, "queue pointer", "array queue data structure");
        exit(INVALID_ARG);
    }


    for (int i = arrayQueue->front; i < arrayQueue->rear; i++)
        arrayQueue->freeItem(arrayQueue->memory[i]);

    arrayQueue->front = arrayQueue->rear = 0;

}










/** Returns whether Queue is Empty or Not.
 * @param arrayQueue Pointer to the Queue on the heap.
 * @return returns short integer 1 if Empty else 0.
 */

 short arrayQueueIsEmpty(ArrayQueue * arrayQueue) {
    if (arrayQueue == NULL) {
        fprintf(stderr, INVALID_ARG_MESSAGE, "queue pointer", "array queue data structure");
        exit(INVALID_ARG);
    }

    return (short ) (arrayQueue->rear == arrayQueue->front);
}









/** Returns the number of elements currently stored in the Queue.
 * @param arrayQueue Pointer to the Queue on the heap.
 * @return integer length of array.
 */

uint32_t arrayQueueGetLength(ArrayQueue * arrayQueue){
    if (arrayQueue == NULL) {
        fprintf(stderr, INVALID_ARG_MESSAGE, "queue pointer", "array queue data structure");
        exit(INVALID_ARG);
    }

    return arrayQueue->rear - arrayQueue->front;
}









/** This function will take an array of items pointers, then it will enqueue all the array items.
 * @param arrayQueue Pointer to the Queue on the heap.
 * @param arr Pointer to an Externally defined array on the heap.
 * @param arrLength Number of elements of the Externally Defined Array.
 */

void arrayQueueEnqueueAll(ArrayQueue * arrayQueue, void **arr, int arrLength) {

    if (arrayQueue == NULL) {
        fprintf(stderr, INVALID_ARG_MESSAGE, "queue pointer", "array queue data structure");
        exit(INVALID_ARG);
    } else if (arr == NULL) {
        fprintf(stderr, INVALID_ARG_MESSAGE, "items array", "array queue data structure");
        exit(INVALID_ARG);
    }

    for(int i = 0; i < arrLength; i++ )
        arrayQueueEnqueue(arrayQueue, arr[i]);

}









/** Returns the first item that was enqueued at the
* @param arrayQueue Pointer to the Queue on the heap.
* @return Pointer the first enqueued Object.
*/

void *arrayQueuePeek(ArrayQueue * arrayQueue) {
    if (arrayQueue == NULL) {
        fprintf(stderr, INVALID_ARG_MESSAGE, "queue pointer", "array queue data structure");
        exit(INVALID_ARG);
    }

    return arrayQueue->memory[arrayQueue->front];

}








/** Converts a queue to an Array.
 * @param arrayQueue Pointer to the Queue on the heap.
 * @return Pointer to an allocated array on the heap.
 */

void **arrayQueueToArray(ArrayQueue * arrayQueue){
    if (arrayQueue == NULL) {
        fprintf(stderr, INVALID_ARG_MESSAGE, "queue pointer", "array queue data structure");
        exit(INVALID_ARG);
    }

    void **array = (void **) malloc(sizeof(void *) * arrayQueueGetLength(arrayQueue));
    if (array == NULL) {
        fprintf(stderr, FAILED_ALLOCATION_MESSAGE, "to array", "array queue data structure");
        exit(FAILED_ALLOCATION);
    }

    for (int i = arrayQueue->front; i < arrayQueue->rear; i++)
        array[i] = arrayQueue->memory[i];

    return array;

}

