#include "../Headers/BinaryMaxHeap.h"

/** Restores the heap property , by recursively traversing the heap. Moving elements up the maximum tree.
 *  @param binaryMaxHeap  Reference to maximum heap pointer allocated on the heap.
 *  @param index
**/
void MaxHeapifyUP(BinaryMaxHeap* binaryMaxHeap, int index){
    if (binaryMaxHeap == NULL) {
        fprintf(stderr, INVALID_ARG_MESSAGE, "binaryMaxHeap ", "MaxHeapifyUP");
        #ifdef CU_TEST_H
     		DUMMY_TEST_DATASTRUCTURE->errorCode = INVALID_ARG;
     	#else
     		exit(INVALID_ARG);
     	#endif

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
        #ifdef CU_TEST_H
     		DUMMY_TEST_DATASTRUCTURE->errorCode = INVALID_ARG;
     	#else
     		exit(INVALID_ARG);
     	#endif

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
        #ifdef CU_TEST_H
     		DUMMY_TEST_DATASTRUCTURE->errorCode = INVALID_ARG;
     	#else
     		exit(INVALID_ARG);
     	#endif

    }
    if (freeFn == NULL) {
        fprintf(stderr, INVALID_ARG_MESSAGE, "freeFn", "MaxHeapInitialize");
        #ifdef CU_TEST_H
     		DUMMY_TEST_DATASTRUCTURE->errorCode = INVALID_ARG;
     	#else
     		exit(INVALID_ARG);
     	#endif

    }

    BinaryMaxHeap *h = malloc(sizeof(*h));
    if(h==NULL){
        fprintf(stderr, FAILED_ALLOCATION_MESSAGE, "BinaryMaxHeap", "MaxHeapInitialize");
        #ifdef CU_TEST_H
     		DUMMY_TEST_DATASTRUCTURE->errorCode = FAILED_ALLOCATION;
     	#else
     		exit(FAILED_ALLOCATION);
     	#endif

    }

    h->capacity      = 10;
    void **harr      = (void **)malloc(sizeof(void*)*h->capacity);

    if(harr==NULL){
        fprintf(stderr, FAILED_ALLOCATION_MESSAGE, "Heap Array", "MaxHeapInitialize");
        #ifdef CU_TEST_H
     		DUMMY_TEST_DATASTRUCTURE->errorCode = FAILED_ALLOCATION;
     	#else
     		exit(FAILED_ALLOCATION);
     	#endif

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
        #ifdef CU_TEST_H
     		DUMMY_TEST_DATASTRUCTURE->errorCode = INVALID_ARG;
     	#else
     		exit(INVALID_ARG);
     	#endif

    }
    if (value == NULL) {
        fprintf(stderr, INVALID_ARG_MESSAGE, "value", "MaxHeapInsert");
        #ifdef CU_TEST_H
     		DUMMY_TEST_DATASTRUCTURE->errorCode = INVALID_ARG;
     	#else
     		exit(INVALID_ARG);
     	#endif

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
        #ifdef CU_TEST_H
     		DUMMY_TEST_DATASTRUCTURE->errorCode = INVALID_ARG;
     	#else
     		exit(INVALID_ARG);
     	#endif

    }
    if (res == NULL) {
        fprintf(stderr, INVALID_ARG_MESSAGE, "res", "MaxHeapDelete");
        #ifdef CU_TEST_H
     		DUMMY_TEST_DATASTRUCTURE->errorCode = INVALID_ARG;
     	#else
     		exit(INVALID_ARG);
     	#endif

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
        #ifdef CU_TEST_H
     		DUMMY_TEST_DATASTRUCTURE->errorCode = INVALID_ARG;
     	#else
     		exit(INVALID_ARG);
     	#endif

    }
    if (size == 0 || size < 0) {
        fprintf(stderr, INVALID_ARG_MESSAGE, "size", "MaxHeapify");
        #ifdef CU_TEST_H
     		DUMMY_TEST_DATASTRUCTURE->errorCode = INVALID_ARG;
     	#else
     		exit(INVALID_ARG);
     	#endif

    }

    if (cmp == NULL) {
        fprintf(stderr, INVALID_ARG_MESSAGE, "cmp", "MaxHeapify");
        #ifdef CU_TEST_H
     		DUMMY_TEST_DATASTRUCTURE->errorCode = INVALID_ARG;
     	#else
     		exit(INVALID_ARG);
     	#endif

    }

    BinaryMaxHeap *h = malloc(sizeof(*h));

    if(h==NULL){
        fprintf(stderr, FAILED_ALLOCATION_MESSAGE, "BinaryMaxHeap", "MaxHeapInitialize");
        #ifdef CU_TEST_H
     		DUMMY_TEST_DATASTRUCTURE->errorCode = FAILED_ALLOCATION;
     	#else
     		exit(FAILED_ALLOCATION);
     	#endif

    }

    h->capacity = 10;
    void **harr = (void **)malloc(sizeof(void*)*h->capacity);

    if(harr==NULL){
        fprintf(stderr, FAILED_ALLOCATION_MESSAGE, "Heap Array", "MaxHeapInitialize");
        #ifdef CU_TEST_H
     		DUMMY_TEST_DATASTRUCTURE->errorCode = FAILED_ALLOCATION;
     	#else
     		exit(FAILED_ALLOCATION);
     	#endif

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
        #ifdef CU_TEST_H
     		DUMMY_TEST_DATASTRUCTURE->errorCode = INVALID_ARG;
     	#else
     		exit(INVALID_ARG);
     	#endif

    }
    if (size == 0|| size < 0) {
        fprintf(stderr, INVALID_ARG_MESSAGE, "size", "MaxHeapAddAll");
        #ifdef CU_TEST_H
     		DUMMY_TEST_DATASTRUCTURE->errorCode = INVALID_ARG;
     	#else
     		exit(INVALID_ARG);
     	#endif

    }

    if (arr == NULL) {
        fprintf(stderr, INVALID_ARG_MESSAGE, "arr", "MaxHeapAddAll");
        #ifdef CU_TEST_H
     		DUMMY_TEST_DATASTRUCTURE->errorCode = INVALID_ARG;
     	#else
     		exit(INVALID_ARG);
     	#endif

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
        #ifdef CU_TEST_H
     		DUMMY_TEST_DATASTRUCTURE->errorCode = INVALID_ARG;
     	#else
     		exit(INVALID_ARG);
     	#endif

    }
    if (printfn == NULL) {
        fprintf(stderr, INVALID_ARG_MESSAGE, "printfn", "printMaxHeap");
        #ifdef CU_TEST_H
     		DUMMY_TEST_DATASTRUCTURE->errorCode = INVALID_ARG;
     	#else
     		exit(INVALID_ARG);
     	#endif

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
        #ifdef CU_TEST_H
     		DUMMY_TEST_DATASTRUCTURE->errorCode = INVALID_ARG;
     	#else
     		exit(INVALID_ARG);
     	#endif

    }

    if (binaryMaxHeap->freeFn == NULL) {
        fprintf(stderr, NULL_POINTER_MESSAGE, "free function ", "destroyMaxHeap");
        #ifdef CU_TEST_H
     		DUMMY_TEST_DATASTRUCTURE->errorCode = NULL_POINTER;
     	#else
     		exit(NULL_POINTER);
     	#endif

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
        #ifdef CU_TEST_H
     		DUMMY_TEST_DATASTRUCTURE->errorCode = INVALID_ARG;
     	#else
     		exit(INVALID_ARG);
     	#endif

    }

    if (binaryMaxHeap->freeFn == NULL) {
        fprintf(stderr, NULL_POINTER_MESSAGE, "free function ", "MaxHeapClear");
        #ifdef CU_TEST_H
     		DUMMY_TEST_DATASTRUCTURE->errorCode = NULL_POINTER;
     	#else
     		exit(NULL_POINTER);
     	#endif

    }

    for(int i =0; i < binaryMaxHeap->size; i++){
        binaryMaxHeap->freeFn(binaryMaxHeap->memory[i]);
        binaryMaxHeap->memory[i] =NULL;
    }
}


uint32_t isEqual(BinaryMaxHeap *binaryMaxHeap,BinaryMaxHeap *binaryMaxHeap2){
    if (binaryMaxHeap == NULL) {
        fprintf(stderr, INVALID_ARG_MESSAGE, "binaryMaxHeap", "isEqual");
        #ifdef CU_TEST_H
                DUMMY_TEST_DATASTRUCTURE->errorCode = INVALID_ARG;
        #else
                exit(INVALID_ARG);
        #endif

    }

    if (binaryMaxHeap2 == NULL) {
        fprintf(stderr, INVALID_ARG_MESSAGE, "binaryMaxHeap2", "isEqual");
        #ifdef CU_TEST_H
                DUMMY_TEST_DATASTRUCTURE->errorCode = INVALID_ARG;
        #else
                exit(INVALID_ARG);
        #endif
    }

    if(binaryMaxHeap->size < binaryMaxHeap2->size) return -1;
    if(binaryMaxHeap->size > binaryMaxHeap2->size) return  1;
    else {
        for(int i = binaryMaxHeap->size;i>=0;--i){
            if(binaryMaxHeap->cmpFn(binaryMaxHeap->memory[i],binaryMaxHeap2->memory[i])){
                return 1;
            }
        }
        return 0;
    }
}

///
/// \param tree
/// \param item
/// \return
uint32_t BinaryMaxHeapContains(BinaryMaxHeap * binaryMaxHeap, void *item){

    if (binaryMaxHeap == NULL) {
        fprintf(stderr, NULL_POINTER_MESSAGE, "binaryMaxHeap", "BinaryMaxHeapContains");
        #ifdef CU_TEST_H
                DUMMY_TEST_DATASTRUCTURE->errorCode = NULL_POINTER;
        #else
                exit(NULL_POINTER);
        #endif

    } else if (item == NULL) {
        fprintf(stderr, INVALID_ARG_MESSAGE, "item", "BinaryMaxHeapContains");
        #ifdef CU_TEST_H
                DUMMY_TEST_DATASTRUCTURE->errorCode = INVALID_ARG;
        #else
                exit(INVALID_ARG);
        #endif
    }

    for(int i = binaryMaxHeap->size-1;i>=0;--i){
        if(binaryMaxHeap->cmpFn(binaryMaxHeap->memory[i],item))
            continue;
        else
            return 1;
    }
}
















