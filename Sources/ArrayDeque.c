#include "../Headers/ArrayDeque.h"


/** Copies a source array from a beginning index to the destination array from the mentioned index. Number of arguments to be copied is decided by len argument.
 * @param source Reference to the source array to copy from.
 * @param sourceIndex index to start copying from in the source array.
 * @param destination Reference pointer to the destination array.
 * @param destinationIndex index to start copying into in the destination array.
 * @param len number of elements to copy from the source to the destination.
**/
void arrayCopy(void **source, int32_t sourceIndex, void **destination, int32_t destinationIndex, uint32_t len){
    int max = sourceIndex + len;
    while(sourceIndex < max)
        destination[destinationIndex++]=source[sourceIndex++];
}

/** Doubles the size of the ArrayDeque copying the contents of the previously allocated Deque to the new one.
** @param ad Reference pointer to the ArrayDeque.
**/
void doubleSize(ArrayDeque* ad){
    //THe length of the Deque
    uint32_t n = ArrayDequeLength(ad);
    // The number of elements after the front
    uint32_t k = n-ad->front-1;
    //the number of elements after the rear and including the starting point which is index Zero
    uint32_t r = ad->rear+1;

    ad->size = n * 2;
    void ** a = calloc(ad->size,sizeof(*ad->memory));

    //Copy elements from the front to the end of the array
    arrayCopy(ad->memory,ad->front,a,ad->size-k-1,k+1);
    //Copy elements from the start of the circular array to the rear's index
    arrayCopy(ad->memory,0,a,0,r);
    
    free(ad->memory);

    ad->memory = a;
    //setting the new front with respect to the new size of the circular array
    ad->front = ad->size-k-1;
    // the rear remains the same since it always increments from the start index zero.
}

/** Determines if a an Array Dequeue is full or not.
 * @param  arrayDeque Reference to preallocated Deque.
 * @return Return short int 1 if full else 0.
**/
uint16_t  ArrayDequeIsFull(ArrayDeque* arrayDeque){
    return ((arrayDeque->front == 0 && arrayDeque->rear == arrayDeque->size-1)
            ||arrayDeque->front == arrayDeque->rear+1);
}

/** Allocates space for a deque with an array of size set by the initialSize param on the heap and ret
urns a pointer to the deque structure.
 * @param initialSize Size of the intial deque array.
 * @return Pointer to the newly allocated deque on the heap.
 **/
ArrayDeque* ArrayDequeInitialize(uint32_t initialSize,void(*freeFn)(void*)){
    ArrayDeque* ad =  (ArrayDeque*) malloc(sizeof(*ad));
    ad->size       =  initialSize;
    ad->front      = -1;
    ad->rear       =  0;
    ad->memory     =  calloc(sizeof(*ad->memory), ad->size);
    ad->freeFn     = freeFn;
    return ad;
}

/**
 * @param arrayDeque Reference to preallocated Deque.
 * @param key  Pointer to key to stored in the deque.
 **/
void ArrayDequeInsertFront(ArrayDeque* arrayDeque,void* key ) {
    if (ArrayDequeIsFull(arrayDeque)) {
        doubleSize(arrayDeque);
    }

    if (ArrayDequeIsEmpty(arrayDeque)) {
        arrayDeque->front = 0;
        arrayDeque->rear = 0;
    }

    else if (arrayDeque->front == 0)
        arrayDeque->front = arrayDeque->size - 1 ;

    else
        arrayDeque->front--;

    arrayDeque->memory[arrayDeque->front] = key ;
}

/** Inserts At the Rear of the deque.
 * @param arrayDeque Reference to preallocated Deque. Reference to preallocated Deque.
 * @param key Pointer to key to stored in the deque.
 **/
void ArrayDequeInsertRear(ArrayDeque* arrayDeque,void* key ) {
    if (ArrayDequeIsFull(arrayDeque)) {
        doubleSize(arrayDeque);
    }
    
    if (ArrayDequeIsEmpty(arrayDeque)){
        arrayDeque->front = 0;
        arrayDeque->rear  = 0;
    }
    
    else if (arrayDeque->rear == arrayDeque->size-1)
        arrayDeque->rear = 0;
    else
        arrayDeque->rear++;

    arrayDeque->memory[arrayDeque->rear] = key ;
}

/**  Decrements the Front pointer to the object.
 * @param arrayDeque Reference to preallocated Deque.
 **/
void ArrayDequeDeleteFrontWithFree(ArrayDeque* arrayDeque ) {
    if (ArrayDequeIsEmpty(arrayDeque)){
        fprintf(stderr, "Queue Underflow\n");
        return ;
    }
    if ( arrayDeque->front ==  arrayDeque->rear) {
        arrayDeque->freeFn(arrayDeque->memory[0]);
        arrayDeque->memory[0]=NULL;
        arrayDeque->front = -1;
        arrayDeque->rear = -1;
    }
    else {
        arrayDeque->freeFn(arrayDeque->memory[arrayDeque->front]);
        arrayDeque->memory[arrayDeque->front]=NULL;
        if (arrayDeque->front == arrayDeque->size - 1)
            arrayDeque->front = 0;
        else
            arrayDeque->front++;
    }
}
void ArrayDequeDeleteFrontWithoutFree(ArrayDeque* arrayDeque ) {
    if (ArrayDequeIsEmpty(arrayDeque)){
        fprintf(stderr, "Queue Underflow\n");
        return ;
    }
    if ( arrayDeque->front ==  arrayDeque->rear) {
        arrayDeque->front = -1;
        arrayDeque->rear = -1;
    }
    else {
        if (arrayDeque->front ==  arrayDeque->size - 1)
            arrayDeque->front = 0;

        else
            arrayDeque->front++;
    }
}

/** Decrements the Rear pointer to the object.
 * @param arrayDeque Reference to preallocated Deque.
 **/
void ArrayDequeDeleteRearWithFree(ArrayDeque* arrayDeque ) {
    if (ArrayDequeIsEmpty(arrayDeque)){
        fprintf(stderr, "Queue Underflow\n");
        return ;
    }
    if (arrayDeque->front == arrayDeque->rear){
        arrayDeque->freeFn(arrayDeque->memory[0]);
        arrayDeque->memory[0]=NULL;
        arrayDeque->front = -1;
        arrayDeque->rear = -1;
    }
    else if (arrayDeque->rear == 0) {
        arrayDeque->rear = arrayDeque->size - 1;
    }else{
        arrayDeque->freeFn(arrayDeque->memory[arrayDeque->rear]);
        arrayDeque->memory[arrayDeque->rear]=NULL;
        arrayDeque->rear--;
    }
}

void ArrayDequeDeleteRearWithoutFree(ArrayDeque* arrayDeque ) {
    if (ArrayDequeIsEmpty(arrayDeque)){
        fprintf(stderr, "Queue Underflow\n");
        return ;
    }
    if (arrayDeque->front == arrayDeque->rear){
        arrayDeque->front = -1;
        arrayDeque->rear = -1;
    }
    else if (arrayDeque->rear == 0)
        arrayDeque->rear = arrayDeque->size-1;
    else
        arrayDeque->rear--;
}

/** If array Deque is emtpy then return 1 else returns 0.
 * @param arrayDeque Reference to preallocated Deque.
 * @return  Return 1 if empty else return 0.
 **/
uint16_t ArrayDequeIsEmpty(ArrayDeque* arrayDeque ) {
    return (arrayDeque->front == -1);
}

/**  Returns stored reference pointer to the previously added element. Does Not decrement the front.
 * @param arrayDeque Reference to preallocated Deque.
 * @return Returns pointer to the data in front.
 **/
void* ArrayDequeGetFront(ArrayDeque* arrayDeque ) {
    if (ArrayDequeIsEmpty(arrayDeque)){
        fprintf(stderr, "Queue Underflow\n");
        return NULL;
    }
    return arrayDeque->memory[arrayDeque->front];
}

/** Returns stored reference pointer to the previously added element. Does Not decrement the rear.
 * @param arrayDeque Reference to preallocated Deque.
 * @return Returns pointer to the data in rear.
 **/
void* ArrayDequeGetRear(ArrayDeque* arrayDeque ) {
    if (ArrayDequeIsEmpty(arrayDeque)){
        fprintf(stderr, "Queue Underflow\n");
        return NULL;
    }
    return arrayDeque->memory[arrayDeque->rear];
}

/** Function that print the deque. First the head then the tail then the head.
 * @param arrayDeque Reference to preallocated Deque.
 * @param printFn Function pointer used for printing the deque.
 **/
void ArrayDequePrint(ArrayDeque* arrayDeque, void (*printFn)(void *)){
    for(int i=0;i<arrayDeque->rear+1;i++){
        (printFn)( arrayDeque->memory[i] );
    }
    for(int i=arrayDeque->front;i<arrayDeque->size;i++)
         (printFn)( arrayDeque->memory[i] );
}

/** Clears the array Items and sets them to null.
 * @param arrayDeque Reference to preallocated Deque.
 **/
void ArrayDequeClear(ArrayDeque* arrayDeque){
    for(int i=0;i<arrayDeque->rear+1;i++){
        arrayDeque->freeFn(arrayDeque->memory[i] );
        arrayDeque->memory[i]=NULL;
    }
    for(int i=arrayDeque->front;i<arrayDeque->size;i++){
        arrayDeque->freeFn( arrayDeque->memory[i] );
        arrayDeque->memory[arrayDeque->size-i]=NULL;
    }
}

/** Clears and frees the contents of the array Deque
* @param arrayDeque Reference pointer to the ArrayDeque.
**/
void ArrayDequeFree(ArrayDeque* arrayDeque){
    ArrayDequeClear(arrayDeque);
    free(arrayDeque->memory);
    arrayDeque->memory = NULL;
    free(arrayDeque);
}

/** Given an arrya deque it returns the length of the array Deque.
 * @param ad  Reference pointer to the ArrayDeque.
 * @return returns the length of the Array Deque i.e the number of elements stored in the Deque
 **/
uint32_t ArrayDequeLength(ArrayDeque* ad){
    uint32_t size = ad->front > ad->rear?ad->size-ad->front+ad->rear+1:ad->rear - ad->front + 1;
    return size>ad->size?0:size;
}

/** Converts the Deque into an array in the order the items where inserted in.
 * @param ad Reference pointer to the ArrayDeque.
 * @return Pointer to the newly allocated array with ArrayDeque's Data.
 **/
void** ArrayDequeToArray(ArrayDeque * ad){
    void ** arr = malloc(ArrayDequeLength(ad)*sizeof(*arr));
    uint32_t index = 0 ;
    arr[index++] = ad->memory[0];
    for(int i=ad->size-1;i>=ad->front;i--)
        arr[index++] =ad->memory[i];
    for(int i=1;i<ad->rear+1;i++)
        arr[index++] =ad->memory[i];
    return arr;
}