#include "../Headers/BinaryMaxHeap.h"

/** Restores the heap property , by recursively traversing the heap. Moving elements up the maximum tree.
 *  @param binaryMaxHeap  Reference to maximum heap pointer allocated on the heap.
 *  @param index
**/
void MaxHeapifyUP(BinaryMaxHeap* binaryMaxHeap, int index){
    if (binaryMaxHeap == NULL) {
        fprintf(stderr, INVALID_ARG_MESSAGE, "binaryMaxHeap ", "MaxHeapifyUP");
        exit(INVALID_ARG);
    }
    if(!index) return;
    int p = PARENT(index);
    if (((binaryMaxHeap->cmpFn)(binaryMaxHeap->memory[p], binaryMaxHeap->memory[index])) < 0){
        void* temp = binaryMaxHeap->memory[p];
        binaryMaxHeap->memory[p] = binaryMaxHeap->memory[index];
        binaryMaxHeap->memory[index] = temp;
        MaxHeapifyUP(binaryMaxHeap, p);
    }

}

/** Function that ensures binaryMaxHeap property, by recursively traversing the binaryMaxHeap. Moving elements down the maximum tree.
 *  @param binaryMaxHeap  Reference to maximum binaryMaxHeap pointer allocated on the pMinHeap.
 *  @param index index to heapify at.
**/
void MaxHeapifyDown(BinaryMaxHeap *binaryMaxHeap, int index) {
    if (binaryMaxHeap == NULL) {
        fprintf(stderr, INVALID_ARG_MESSAGE, "binaryMaxHeap ", "MaxHeapifyDown");
        exit(INVALID_ARG);
    }

    if (index < 0) return;
    if(index > binaryMaxHeap->size) return;

    int LeftChildIndex = LCHILD(index);
    int RightChildIndex = RCHILD(index);
    int CurrentIndex = index;

    if (HAS_LEFT(binaryMaxHeap, index) &&
        binaryMaxHeap->cmpFn(binaryMaxHeap->memory[LeftChildIndex], binaryMaxHeap->memory[CurrentIndex]) > 0){
        CurrentIndex = LeftChildIndex;
    }
    if (HAS_RIGHT(binaryMaxHeap, index) &&
        binaryMaxHeap->cmpFn(binaryMaxHeap->memory[RightChildIndex], binaryMaxHeap->memory[CurrentIndex]) > 0 ){
        CurrentIndex = RightChildIndex;
    }

    if (CurrentIndex != index){
        //swap1(binaryMaxHeap->memory + index, binaryMaxHeap->memory + CurrentIndex);

        void* temp = binaryMaxHeap->memory[index];
        binaryMaxHeap->memory[index] = binaryMaxHeap->memory[CurrentIndex];
        binaryMaxHeap->memory[CurrentIndex] = temp;

        index = CurrentIndex;
    }
    else
        return;

    MaxHeapifyDown(binaryMaxHeap, index);
}

/** Allocates space for maximum heap on the heap. Setting the inital size to 0 and the initial allocated size to 10.
 *  @param cmp compare function for values stored in the heap.
 *  @return Returns pointer to the allocated maximum heap on the heap.
**/
BinaryMaxHeap *MaxHeapInitialize( int32_t (*cmp)(const void*, const void*),void  (*freeFn)(void*)) {

    if (cmp == NULL) {
        fprintf(stderr, INVALID_ARG_MESSAGE, "cmp", "MaxHeapInitialize");
        exit(INVALID_ARG);
    }
    if (freeFn == NULL) {
        fprintf(stderr, INVALID_ARG_MESSAGE, "freeFn", "MaxHeapInitialize");
        exit(INVALID_ARG);
    }

    BinaryMaxHeap *h = malloc(sizeof(*h));
    if(h==NULL){
        fprintf(stderr, FAILED_ALLOCATION_MESSAGE, "BinaryMaxHeap", "MaxHeapInitialize");
        exit(FAILED_ALLOCATION);
    }

    h->capacity      = 10;
    void **harr      = (void **)malloc(sizeof(void*)*h->capacity);

    if(harr==NULL){
        fprintf(stderr, FAILED_ALLOCATION_MESSAGE, "Heap Array", "MaxHeapInitialize");
        exit(FAILED_ALLOCATION);
    }

    h->memory        = harr;
    h->size          = 0;
    h->cmpFn         = cmp;
    h->freeFn        = freeFn;
    return h;
}

/** Inserts at the bottom of the tree then moves the element up the tree by calling @link MaxHeapifyUP @endlink
 *  @param binaryMaxHeap  Reference to maximum heap pointer allocated on the heap.
 *  @param value item to insert in the tree.
**/
void MaxHeapInsert(BinaryMaxHeap* binaryMaxHeap, void* value) {

    if (binaryMaxHeap == NULL) {
        fprintf(stderr, INVALID_ARG_MESSAGE, "binaryMaxHeap ", "MaxHeapInsert");
        exit(INVALID_ARG);
    }
    if (value == NULL) {
        fprintf(stderr, INVALID_ARG_MESSAGE, "value", "MaxHeapInsert");
        exit(INVALID_ARG);
    }

    if(binaryMaxHeap->size == binaryMaxHeap->capacity){
        binaryMaxHeap->capacity *=2;
        binaryMaxHeap->memory = realloc(binaryMaxHeap->memory, sizeof(void*) * binaryMaxHeap->capacity);
    }
    binaryMaxHeap->memory[binaryMaxHeap->size] = value;
    MaxHeapifyUP(binaryMaxHeap, binaryMaxHeap->size++);
}

/** Deletes the root element of the binaryMaxHeap and restores the binaryMaxHeap property of the binaryMaxHeap.
 *  @param binaryMaxHeap Reference to maximum binaryMaxHeap pointer allocated on the binaryMaxHeap.
 *  @param res pointer to store the root if needed.
**/
void MaxHeapDelete(BinaryMaxHeap* binaryMaxHeap, void ** res) {
    if (binaryMaxHeap == NULL) {
        fprintf(stderr, INVALID_ARG_MESSAGE, "binaryMaxHeap ", "MaxHeapDelete");
        exit(INVALID_ARG);
    }
    if (res == NULL) {
        fprintf(stderr, INVALID_ARG_MESSAGE, "res", "MaxHeapDelete");
        exit(INVALID_ARG);
    }

    *res = binaryMaxHeap->memory[0];
    binaryMaxHeap->memory[0] = binaryMaxHeap->memory[binaryMaxHeap->size - 1];
    binaryMaxHeap->memory[binaryMaxHeap->size - 1] = NULL;
    binaryMaxHeap->size--;
    MaxHeapifyDown(binaryMaxHeap, 0);
}

/** Given an array containing preallocated pointer to objects, this function creates a new heap with the objects in it.
 *  @param arr Array to add elements from into the heap.
 *  @param size Size of the array to be inserted into the heap.
 *  @param cmp  compare function for values stored in the heap.
 *  @return Reference to maximum heap pointer allocated on the pMinHeap.
 **/
BinaryMaxHeap *MaxHeapify(void **arr, uint32_t size,int32_t (*cmp)(const void*, const void*)) {

    if (arr == NULL) {
        fprintf(stderr, INVALID_ARG_MESSAGE, "arr ", "MaxHeapify");
        exit(INVALID_ARG);
    }
    if (size == 0 || size < 0) {
        fprintf(stderr, INVALID_ARG_MESSAGE, "size", "MaxHeapify");
        exit(INVALID_ARG);
    }

    if (cmp == NULL) {
        fprintf(stderr, INVALID_ARG_MESSAGE, "cmp", "MaxHeapify");
        exit(INVALID_ARG);
    }

    BinaryMaxHeap *h = malloc(sizeof(*h));

    if(h==NULL){
        fprintf(stderr, FAILED_ALLOCATION_MESSAGE, "BinaryMaxHeap", "MaxHeapInitialize");
        exit(FAILED_ALLOCATION);
    }

    h->capacity = 10;
    void **harr = (void **)malloc(sizeof(void*)*h->capacity);

    if(harr==NULL){
        fprintf(stderr, FAILED_ALLOCATION_MESSAGE, "Heap Array", "MaxHeapInitialize");
        exit(FAILED_ALLOCATION);
    }

    h->memory = harr;
    h->size = size;
    h->cmpFn = cmp;
    for(int i=0;i<size;i++){
        MaxHeapInsert(h,arr[i]);
    }
    return h;
}

/** Given an array of void pointers to pre-allocated objects, it inserts them in a maximum heap.
 *  @param binaryMaxHeap  Reference to maximum heap pointer allocated on the heap.
 *  @param arr array to add elements from into the heap.
 *  @param size Size of the array to be inserted into the heap.
**/
void  MaxHeapAddAll(BinaryMaxHeap *binaryMaxHeap,void **arr, uint32_t size){
    if (binaryMaxHeap == NULL) {
        fprintf(stderr, INVALID_ARG_MESSAGE, "binaryMaxHeap ", "MaxHeapAddAll");
        exit(INVALID_ARG);
    }
    if (size == 0|| size < 0) {
        fprintf(stderr, INVALID_ARG_MESSAGE, "size", "MaxHeapAddAll");
        exit(INVALID_ARG);
    }

    if (arr == NULL) {
        fprintf(stderr, INVALID_ARG_MESSAGE, "arr", "MaxHeapAddAll");
        exit(INVALID_ARG);
    }

    for(int i=0;i<size;i++){
        MaxHeapInsert(binaryMaxHeap,arr[i]);
    }
}

/** Given a reference to heap prints it's elements.
 *  @param binaryMaxHeap  Reference to maximum heap pointer allocated on the heap.
 *  @param printfn pointer to the print funtion to be used.
**/
void printMaxHeap(BinaryMaxHeap *binaryMaxHeap, void (*printfn)(void *)) {
    if (binaryMaxHeap == NULL) {
        fprintf(stderr, INVALID_ARG_MESSAGE, "binaryMaxHeap ", "printMaxHeap");
        exit(INVALID_ARG);
    }
    if (printfn == NULL) {
        fprintf(stderr, INVALID_ARG_MESSAGE, "printfn", "printMaxHeap");
        exit(INVALID_ARG);
    }


    for (int i = 0; i < binaryMaxHeap->size; ++i) {
        (printfn)(binaryMaxHeap->memory[i]);
    }
    puts("\n");
}

/** Given a binaryMaxHeap it frees its memory container and the allocated pointer within it,
  setting them null as well as the memory container and frees the binaryMaxHeap pointer.
 *  @param binaryMaxHeap  Reference to maximum binaryMaxHeap pointer allocated on the binaryMaxHeap.
**/
void destroyMaxHeap(BinaryMaxHeap * binaryMaxHeap) {
    if (binaryMaxHeap == NULL) {
        fprintf(stderr, INVALID_ARG_MESSAGE, "binaryMaxHeap ", "destroyMaxHeap");
        exit(INVALID_ARG);
    }

    if (binaryMaxHeap->freeFn == NULL) {
        fprintf(stderr, NULL_POINTER_MESSAGE, "free function ", "destroyMaxHeap");
        exit(NULL_POINTER);
    }

    MaxHeapClear(binaryMaxHeap);
    free(binaryMaxHeap->memory);
    binaryMaxHeap->memory = NULL;
    free(binaryMaxHeap);
}

/** Given a heap pointer it frees it's memory container contents. But not the memory container of the heap.
 * @param binaryMaxHeap Reference to maximum heap pointer allocated on the heap.
 * */
void MaxHeapClear(BinaryMaxHeap * binaryMaxHeap){
    if (binaryMaxHeap == NULL) {
        fprintf(stderr, INVALID_ARG_MESSAGE, "binaryMaxHeap ", "MaxHeapClear");
        exit(INVALID_ARG);
    }

    if (binaryMaxHeap->freeFn == NULL) {
        fprintf(stderr, NULL_POINTER_MESSAGE, "free function ", "MaxHeapClear");
        exit(NULL_POINTER);
    }

    for(int i =0; i < binaryMaxHeap->size; i++){
        binaryMaxHeap->freeFn(binaryMaxHeap->memory[i]);
        binaryMaxHeap->memory[i] =NULL;
    }
}


















