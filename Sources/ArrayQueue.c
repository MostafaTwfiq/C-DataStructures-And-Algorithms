#include  "../Headers/ArrayQueue.h"



typedef struct ArrayQueueItem {
    void *value;
    int sizeOfItem;
} ArrayQueueItem;






/** Function Initializes Queue on Heap using malloc and returns pointer to it.
 * @param size Size of the data to be stored by the Queue.
 * @return Return Pointer ot Queue on the Heap.
 * */

ArrayQueue* QueueInitialize(void (*freeItem)(void *item)) {
    ArrayQueue* q =(ArrayQueue *) malloc(sizeof ( *q ));

    if(q == NULL){
        fprintf(stderr,"Was Unable to Allocate Queue");
        exit(NULL_POINTER);
    }

    q->freeItem =  freeItem;
    q->allocated = 10;
    q->memory = (ArrayQueueItem **) malloc( sizeof(ArrayQueueItem *) * q->allocated);

    if(!q->memory){
        fprintf(stderr,"Was Unable to Allocate Memory for Queue.\n");
        exit(NULL_POINTER);
    }

    q->front = q->rear = 0;

    return q;
}







/** Function that takes a pointer to previously externally allocated object and enqueues it.
 * @param arrayQueue Pointer to the Queue on the heap.
 * @param data Pointer to the data to be stored on the heap.
 * @param dataSize the provided data size in bytes
 * */

void ArrayQueueEnqueue(ArrayQueue* arrayQueue, void *data, int dataSize) {
    if(arrayQueue ==NULL || data == NULL) {
        fprintf(stderr,"Invalid Params, Nor Data  OR Queue Can be NULL.\n");
        exit(INVALID_ARG);
    }

    if(arrayQueue->allocated ==  arrayQueue->rear){
        arrayQueue->allocated *= 2;
        ArrayQueueItem **tempArr = (ArrayQueueItem **) malloc(sizeof(ArrayQueueItem *) * arrayQueue->allocated);
        memcpy(tempArr, arrayQueue->memory + arrayQueue->front, sizeof(ArrayQueueItem *) * (arrayQueue->rear - arrayQueue->front) );
        free(arrayQueue->memory);
        arrayQueue->memory = tempArr;
    }

    if ( !arrayQueue->memory ) {
        fprintf( stderr , "Failed at reallocating the Queue.\n" );
        exit( FAILED_REALLOCATION );
    }

    ArrayQueueItem *newItem = (ArrayQueueItem *) malloc(sizeof(ArrayQueueItem));
    newItem->value = data;
    newItem->sizeOfItem = dataSize;
    arrayQueue->memory[arrayQueue->rear++] = newItem;

}










/** Function that returns a pointer to previously allocated objected and dequeue it.
 * from a queue.
 * @param arrayQueue Pointer to the Queue on the heap.
 * @return Pointer to the previously queued data on the heap.
 * */

void* ArrayQueueDequeue(ArrayQueue* arrayQueue) {
    if(arrayQueue ==NULL ) {
        fprintf(stderr,"Invalid Params, Queue Cannot be NULL.\n");
        exit(INVALID_ARG);
    }

    if (arrayQueue->front == arrayQueue->rear) {
        fprintf(stderr,"Queue is empty\n");
        exit( NULL_POINTER );
    }
    else {
        void *returnItem = arrayQueue->memory[arrayQueue->front]->value;
        free(arrayQueue->memory[arrayQueue->front++]);
        return returnItem;
    }

}









/** Takes a reference pointer to print function and prints data in the queue.
 * @param arrayQueue Pointer to the Queue on the heap.
 * @param fptr pointer to an externally defined print function.
 * */
void ArrayQueueDisplay(ArrayQueue* arrayQueue, void (*fptr)(void *)) {
    if(arrayQueue == NULL || fptr == NULL) {
        fprintf(stderr,"Invalid Params, Function Pointer or Queue cannot be NULL.\n");
        exit(INVALID_ARG);
    }

    if (arrayQueue->front == arrayQueue->rear) {
        fprintf( stderr , "Queue is empty\n" );
        exit( NULL_POINTER );
    }

    for (int i = arrayQueue->front; i < arrayQueue->rear; i++) {
        (*fptr)(arrayQueue->memory[i]->value);
    }

}







/** Destroys the Queue and its allocated objects.
 * @param arrayQueue Pointer to the Queue on the heap.
 * */
void ArrayQueueDestroy(ArrayQueue* arrayQueue) {
    if(arrayQueue ==NULL ) {
        fprintf(stderr,"Invalid Param, Queue Cannot be NULL.\n");
        exit(INVALID_ARG);
    }

    ArrayQueueClear(arrayQueue);

    free(arrayQueue->memory);
    free(arrayQueue);

}






/** Clear the elements stored on the Queue.
 * @param arrayQueue Pointer to the Queue on the heap.
 * */

void ArrayQueueClear(ArrayQueue* arrayQueue) {
    if(arrayQueue ==NULL ) {
        fprintf(stderr,"Invalid Param, Queue Cannot be NULL.\n");
        exit(INVALID_ARG);
    }


    for (int i = arrayQueue->front; i < arrayQueue->rear; i++) {
        arrayQueue->freeItem(arrayQueue->memory[i]->value);
        free(arrayQueue->memory[i]);
    }

    arrayQueue->front = arrayQueue->rear = 0;

}






/** Returns whether Queue is Empty or Not.
 * @param arrayQueue Pointer to the Queue on the heap.
 * @return returns short integer 1 if Empty else 0.
 **/
short isArrayQueueEmpty(ArrayQueue * arrayQueue) {
    if(arrayQueue ==NULL ) {
        fprintf(stderr,"Invalid Param, Queue Cannot be NULL.\n");
        exit(INVALID_ARG);
    }

    return (short ) (arrayQueue->rear == arrayQueue->front);
}









/** Returns the number of elements currently stored in the Queue.
 * @param arrayQueue Pointer to the Queue on the heap.
 * @return integer length of array.
 * */

int ArrayQueueLength(ArrayQueue * arrayQueue){
    if(arrayQueue ==NULL ) {
        fprintf(stderr,"Invalid Param, Queue Cannot be NULL.\n");
        exit(INVALID_ARG);
    }

    return arrayQueue->rear - arrayQueue->front;
}







/**
* @param arrayQueue Pointer to the Queue on the heap.
* @param arr Pointer to an Externally defined array on the heap.
* @param arrLength Number of elements of the Externally Defined Array.
* @param the size of the array items
**/

void ArrayQueueEnqueueAll(ArrayQueue * arrayQueue, void **arr, int arrLength, int sizeOfItem) {
    if(arrayQueue ==NULL ) {
        fprintf(stderr,"Invalid Param, Queue Cannot be NULL.\n");
        exit(INVALID_ARG);
    }

    if(arr ==NULL ) {
        fprintf(stderr,"Invalid Param, arr Cannot be NULL.\n");
        exit(INVALID_ARG);
    }

    if(arrLength == 0 ) {
        fprintf(stderr,"Invalid Param, Queue arrLength be NULL or Zero(0).\n");
        exit(INVALID_ARG);
    }

    for(int i = 0; i<arrLength; i++ ){
        ArrayQueueEnqueue(arrayQueue, arr[i], sizeOfItem);
    }

}







/** Returns the first item that was enqueued at the
* @param arrayQueue Pointer to the Queue on the heap.
* @return Pointer the first enqueued Object.
**/

void *ArrayQueuePeek(ArrayQueue * arrayQueue) {
    if(arrayQueue ==NULL ) {
        fprintf(stderr,"Invalid Param, Queue Cannot be NULL.\n");
        exit(INVALID_ARG);
    }

    return arrayQueue->memory[arrayQueue->front]->value;

}







/** Converts a queue to an Array.
* @param arrayQueue Pointer to the Queue on the heap.
* @return Pointer to an allocated array on the heap.
 * */

void **ArrayQueueToArray(ArrayQueue * arrayQueue){
    void **array = (void **) malloc(sizeof(void *) * ArrayQueueLength(arrayQueue));

    for (int i = arrayQueue->front; i < arrayQueue->rear; i++) {
        array[i] = (void *) malloc(arrayQueue->memory[i]->sizeOfItem);
        memcpy(array[i], arrayQueue->memory[i]->value, arrayQueue->memory[i]->sizeOfItem);
    }

    return array;

}
