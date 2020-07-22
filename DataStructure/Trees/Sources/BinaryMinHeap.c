#include "../Headers/BinaryMinHeap.h"

/** Allocates space for minimum heap on the heap. Setting the inital size to 0 and the initial allocated size to 10.
 *  @param cmp compare function for values stored in the heap.
 *  @return Returns pointer to the allocated minimum heap on the heap.
**/
BinaryMinHeap *MinHeapInitialize(int32_t (*cmp)(const void*, const void*),void (*freeFn)(void*) ){
    if (cmp == NULL) {
        fprintf(stderr, INVALID_ARG_MESSAGE, "cmp", "MinHeapInitialize");
        exit(INVALID_ARG);
    }
    if (freeFn == NULL) {
        fprintf(stderr, INVALID_ARG_MESSAGE, "freeFn", "MinHeapInitialize");
        exit(INVALID_ARG);
    }

    BinaryMinHeap *h = malloc(sizeof(*h));
    h->capacity      = 10;
    if(h==NULL){
        fprintf(stderr, FAILED_ALLOCATION_MESSAGE, "BinaryMinHeap", "MinHeapInitialize");
        exit(FAILED_ALLOCATION);
    }
    void **harr      = (void **)malloc(sizeof(void*)*h->capacity);

    if(harr==NULL){
        fprintf(stderr, FAILED_ALLOCATION_MESSAGE, "Heap Array", "MinHeapInitialize");
        exit(FAILED_ALLOCATION);
    }

    h->memory        = harr;
    h->size          = 0;
    h->cmpFn         = cmp;
    h->freeFn        = freeFn;
    return h;
};

/** Deletes the root element of the heap and restores the heap property of the heap.
 *  @param binaryMinHeap Reference to minimum heap pointer allocated on the heap.
 *  @param res pointer to store the root if needed.
**/
void MinHeapDelete(BinaryMinHeap* binaryMinHeap, void ** res) {
    if (binaryMinHeap == NULL) {
        fprintf(stderr, INVALID_ARG_MESSAGE, "binaryMinHeap ", "MinHeapDelete");
        exit(INVALID_ARG);
    }
    if (res == NULL) {
        fprintf(stderr, INVALID_ARG_MESSAGE, "res", "MinHeapDelete");
        exit(INVALID_ARG);
    }
    *res = binaryMinHeap->memory[0];
    binaryMinHeap->memory[0] = binaryMinHeap->memory[binaryMinHeap->size - 1];
    binaryMinHeap->memory[binaryMinHeap->size - 1] = NULL;
    binaryMinHeap->size--;
    MinHeapifyDown(binaryMinHeap, 0);
}

/** Restores the heap property , by recursively traversing the heap. Moving elements up the minimum tree.
 *  @param binaryMinHeap  Reference to minimum heap pointer allocated on the heap.
 *  @param index
**/
void MinHeapifyUP(BinaryMinHeap* binaryMinHeap, int index) {
    if (binaryMinHeap == NULL) {
        fprintf(stderr, INVALID_ARG_MESSAGE, "binaryMinHeap ", "MinHeapifyUP");
        exit(INVALID_ARG);
    }
    if(!index) return;
    int p = PARENT(index);
    if (((binaryMinHeap->cmpFn)(binaryMinHeap->memory[p], binaryMinHeap->memory[index])) > 0) {
        void* temp = binaryMinHeap->memory[p];
        binaryMinHeap->memory[p] = binaryMinHeap->memory[index];
        binaryMinHeap->memory[index]= temp;
    }
    MinHeapifyUP(binaryMinHeap, p);
}

/** Inserts at the bottom of the tree then moves the element up the tree by calling @link MinHeapifyUP @endlink
 *  @param binaryMinHeap  Reference to minimum heap pointer allocated on the heap.
 *  @param value item to insert in the tree.
**/
void MinHeapInsert(BinaryMinHeap* binaryMinHeap, void* value){
    if (binaryMinHeap == NULL) {
        fprintf(stderr, INVALID_ARG_MESSAGE, "binaryMinHeap ", "MinHeapInsert");
        exit(INVALID_ARG);
    }
    if (value == NULL) {
        fprintf(stderr, INVALID_ARG_MESSAGE, "value", "MinHeapInsert");
        exit(INVALID_ARG);
    }

    if(binaryMinHeap->size == binaryMinHeap->capacity){
        binaryMinHeap->capacity *= 2;
        binaryMinHeap->memory = realloc(binaryMinHeap->memory, sizeof(void*) * binaryMinHeap->capacity);
    }
    binaryMinHeap->memory[binaryMinHeap->size] = value;
    MinHeapifyUP(binaryMinHeap, binaryMinHeap->size++);
}

/** Function that ensures heap property, by recursively traversing the heap. Moving elements down the minimum tree.
 *  @param binaryMinHeap  Reference to minimum heap pointer allocated on the binaryMinHeap.
 *  @param index index ot heapify at.
**/
void MinHeapifyDown(BinaryMinHeap *binaryMinHeap, int index) {

    if (binaryMinHeap == NULL) {
        fprintf(stderr, INVALID_ARG_MESSAGE, "binaryMinHeap ", "MinHeapifyDown");
        exit(INVALID_ARG);
    }

    if (index < 0) return;
    if(index > binaryMinHeap->size) return;
    int LeftChildIndex = LCHILD(index);
    int RightChildIndex = RCHILD(index);
    int CurrentIndex = index;

    if (HAS_LEFT(binaryMinHeap, index) &&
        (binaryMinHeap->cmpFn)(binaryMinHeap->memory[LeftChildIndex], binaryMinHeap->memory[CurrentIndex]) < 0){
        CurrentIndex = LeftChildIndex;
    }

    if (HAS_RIGHT(binaryMinHeap, index) &&
        (binaryMinHeap->cmpFn)(binaryMinHeap->memory[RightChildIndex], binaryMinHeap->memory[CurrentIndex]) < 0 ){
        CurrentIndex = RightChildIndex;
    }

    if (CurrentIndex != index){
        void* temp  = binaryMinHeap->memory[index];
        binaryMinHeap->memory[index]=binaryMinHeap->memory[CurrentIndex];
        binaryMinHeap->memory[CurrentIndex] = temp;
        index = CurrentIndex;
    }
    else
        return;
    MinHeapifyDown(binaryMinHeap, index);
}

/** Given an array containing preallocated pointer to objects, this function creates a new heap with the objects in it.
 *  @param arr Array to add elements from into the heap.
 *  @param size Size of the array to be inserted into the heap.
 *  @param cmp  compare function for values stored in the heap.
 *  @return Reference to minimum heap pointer allocated on the pMinHeap.
**/
BinaryMinHeap *MinHeapify(void *arr, uint32_t size,int32_t (*cmp)(const void*, const void*)){
    if (arr == NULL) {
        fprintf(stderr, INVALID_ARG_MESSAGE, "arr ", "MinHeapify");
        exit(INVALID_ARG);
    }
    if (size == 0 || size < 0) {
        fprintf(stderr, INVALID_ARG_MESSAGE, "size", "MinHeapify");
        exit(INVALID_ARG);
    }

    if (cmp == NULL) {
        fprintf(stderr, INVALID_ARG_MESSAGE, "cmp", "MinHeapify");
        exit(INVALID_ARG);
    }

    BinaryMinHeap *h = malloc(sizeof(BinaryMinHeap));
    if(h==NULL){
        fprintf(stderr, FAILED_ALLOCATION_MESSAGE, "BinaryMinHeap", "MinHeapInitialize");
        exit(FAILED_ALLOCATION);
    }
    h->capacity = size;
    void **harr = malloc(sizeof(void*)*h->capacity);

    if(harr==NULL){
        fprintf(stderr, FAILED_ALLOCATION_MESSAGE, "Heap Array", "MinHeapInitialize");
        exit(FAILED_ALLOCATION);
    }

    h->memory = harr;
    h->size = 0;
    h->cmpFn = cmp;
    for (int i = 0; i < h->capacity; ++i) {
        MinHeapInsert(h, arr + i);
    }
    return h;
}

/** Given a reference to heap prints it's elements.
 *  @param binaryMinHeap  Reference to minimum heap pointer allocated on the heap.
 *  @param printfn pointer to the print funtion to be used.
**/
void printMinHeap(BinaryMinHeap *binaryMinHeap, void (*printfn)(void *)){
    if (binaryMinHeap == NULL) {
        fprintf(stderr, INVALID_ARG_MESSAGE, "binaryMinHeap ", "printMinHeap");
        exit(INVALID_ARG);
    }
    if (printfn == NULL) {
        fprintf(stderr, INVALID_ARG_MESSAGE, "printfn", "printMinHeap");
        exit(INVALID_ARG);
    }

    for (int i = 0; i < binaryMinHeap->size; ++i) {
        (printfn)(binaryMinHeap->memory[i]);
    }
    puts("\n");
}

/** Given an array of void pointers to pre-allocated objects, it inserts them in a minimum heap.
 *  @param binaryMinHeap  Reference to minimum heap pointer allocated on the heap.
 *  @param arr array to add elements from into the heap.
 *  @param size Size of the array to be inserted into the heap.
**/
void MinHeapAddAll(BinaryMinHeap *binaryMinHeap, void **arr, uint32_t size){
    if (binaryMinHeap == NULL) {
        fprintf(stderr, INVALID_ARG_MESSAGE, "binaryMinHeap ", "MinHeapAddAll");
        exit(INVALID_ARG);
    }
    if (size == 0|| size < 0) {
        fprintf(stderr, INVALID_ARG_MESSAGE, "size", "MinHeapAddAll");
        exit(INVALID_ARG);
    }

    if (arr == NULL) {
        fprintf(stderr, INVALID_ARG_MESSAGE, "arr", "MinHeapAddAll");
        exit(INVALID_ARG);
    }

    for(int i=0;i<size;i++){
        MinHeapInsert(binaryMinHeap, arr[i]);
    }
}

/** Given a heap it frees its memory container and the allocated pointer within it,
  setting them null as well as the memory container and frees the heap pointer.
 *  @param binaryMinHeap  Reference to minimum heap pointer allocated on the heap.
**/
void MinHeapDestroy(BinaryMinHeap * binaryMinHeap) {
    if (binaryMinHeap == NULL) {
        fprintf(stderr, INVALID_ARG_MESSAGE, "binaryMinHeap ", "MinHeapDestroy");
        exit(INVALID_ARG);
    }

    if (binaryMinHeap->freeFn == NULL) {
        fprintf(stderr, NULL_POINTER_MESSAGE, "free function ", "MinHeapDestroy");
        exit(NULL_POINTER);
    }
    MinHeapClear(binaryMinHeap);
    free(binaryMinHeap->memory);
    binaryMinHeap->memory = NULL;
    free(binaryMinHeap);
}

/** Given a heap pointer it frees it's memory container contents. But not the memory container of the heap.
 * @param binaryMinHeap Reference to minimum heap pointer allocated on the heap.
 * */
void MinHeapClear(BinaryMinHeap * binaryMinHeap){
    if (binaryMinHeap == NULL) {
        fprintf(stderr, INVALID_ARG_MESSAGE, "binaryMinHeap ", "MinHeapClear");
        exit(INVALID_ARG);
    }

    if (binaryMinHeap->freeFn == NULL) {
        fprintf(stderr, NULL_POINTER_MESSAGE, "free function ", "MinHeapClear");
        exit(NULL_POINTER);
    }
    for(int i =0; i < binaryMinHeap->size; i++){
        binaryMinHeap->freeFn(binaryMinHeap->memory[i]);
        binaryMinHeap->memory[i] =NULL;
    }
}