#include "../Headers/ArrayDeque.h"

void arrayCopy(void **source, int sourcePos, void **destination, int destinationPos,int len){
    int max = sourcePos+len;
    while(sourcePos<max)
        destination[destinationPos++]=source[sourcePos++];
}

void doubleSize(ArrayDeque* ad){
    int n = ArrayDequeLength(ad);
    int k = n-ad->front-1;
    int r = ad->rear+1;

    ad->size = n * 2;
    void ** a = calloc(ad->size,sizeof(*ad->memory));

    arrayCopy(ad->memory,ad->front,a,ad->size-k-1,k+1);
    arrayCopy(ad->memory,0,a,0,r);
    
    free(ad->memory);

    ad->memory = a;
    ad->front = ad->size-k-1;
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
ArrayDeque* ArrayDequeInitialize(uint32_t initialSize ) {
    ArrayDeque* ad =  (ArrayDeque*) malloc(sizeof(*ad));
    ad->size       =  initialSize;
    ad->front      = -1;
    ad->rear       =  0;
    ad->memory     =  calloc(sizeof(*ad->memory), ad->size);
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
void ArrayDequeDeleteFront(ArrayDeque* arrayDeque ) {
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
void ArrayDequeDeleteRear(ArrayDeque* arrayDeque ) {
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
        if( arrayDeque->memory[i]) (printFn)( arrayDeque->memory[i] );
    }
    for(int i=arrayDeque->front;i<arrayDeque->size;i++)
        if(  arrayDeque->memory[i]) (printFn)( arrayDeque->memory[i] );
}

/* Clears the array Items and sets them to null.
 * @param arrayDeque Reference to preallocated Deque.
 **/
void ArrayDequeClear(ArrayDeque* arrayDeque){
    for(int i=0;i<arrayDeque->rear+1;i++){
        free(arrayDeque->memory[i] );
        arrayDeque->memory[i]=NULL;
    }
    for(int i=1;i<arrayDeque->front+1;i++){
        free( arrayDeque->memory[arrayDeque->size-i] );
        arrayDeque->memory[arrayDeque->size-i]=NULL;
    }
}

int ArrayDequeLength(ArrayDeque* ad){
    int size = ad->front > ad->rear?ad->size-ad->front+ad->rear+1:ad->rear - ad->front + 1;
    return size>ad->size?0:size;
}
