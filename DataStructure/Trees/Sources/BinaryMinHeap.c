#include "../Headers/BinaryMinHeap.h"

/** Allocates space for minimum heap on the heap. Setting the inital size to 0 and the initial allocated size to 10.
 *  @param cmp compare function for values stored in the heap.
 *  @return Returns pointer to the allocated minimum heap on the heap.
**/
BinaryMinHeap *MinHeapInitialize(int32_t (*cmp)(const void*, const void*),void (*freeFn)(void*) ){
    BinaryMinHeap *h = malloc(sizeof(*h));
    h->capacity      = 10;
    void **harr      = (void **)malloc(sizeof(void*)*h->capacity);
    h->memory        = harr;
    h->size          = 0;
    h->cmpFn         = cmp;
    h->freeFn        = freeFn;
    return h;
};

/** Deletes the root element of the heap and restores the heap property of the heap.
 *  @param pMinHeap Reference to minimum heap pointer allocated on the heap.
 *  @param res pointer to store the root if needed.
**/
void MinHeapDelete(BinaryMinHeap* pMinHeap, void ** res) {
    *res = pMinHeap->memory[0];
    pMinHeap->memory[0] = pMinHeap->memory[pMinHeap->size - 1];
    pMinHeap->memory[pMinHeap->size - 1] = NULL;
    pMinHeap->size--;
    MinHeapifyDown(pMinHeap, 0);
}

/** Restores the heap property , by recursively traversing the heap. Moving elements up the minimum tree.
 *  @param pMinHeap  Reference to minimum heap pointer allocated on the heap.
 *  @param index
**/
void MinHeapifyUP(BinaryMinHeap* pMinHeap, int index) {
    if(index){
        int p = PARENT(index);
        if (((pMinHeap->cmpFn)(pMinHeap->memory[p], pMinHeap->memory[index])) > 0) {
            void* temp = pMinHeap->memory[p];
            pMinHeap->memory[p] = pMinHeap->memory[index];
            pMinHeap->memory[index]= temp;
        }
        MinHeapifyUP(pMinHeap, p);
    }
}

/** Inserts at the bottom of the tree then moves the element up the tree by calling @link MinHeapifyUP @endlink
 *  @param pMinHeap  Reference to minimum heap pointer allocated on the heap.
 *  @param value item to insert in the tree.
**/
void MinHeapInsert(BinaryMinHeap* pMinHeap, void* value){
    if(pMinHeap->size == pMinHeap->capacity){
        pMinHeap->capacity *= 2;
        pMinHeap->memory = realloc(pMinHeap->memory, sizeof(void*) * pMinHeap->capacity);
    }
    pMinHeap->memory[pMinHeap->size] = value;
    MinHeapifyUP(pMinHeap, pMinHeap->size++);
}

/** Function that ensures heap property, by recursively traversing the heap. Moving elements down the minimum tree.
 *  @param pMinHeap  Reference to minimum heap pointer allocated on the pMinHeap.
 *  @param index index ot heapify at.
**/
void MinHeapifyDown(BinaryMinHeap *pMinHeap, int index) {
    if (index < 0) return;
    if(index > pMinHeap->size) return;
    int LeftChildIndex = LCHILD(index);
    int RightChildIndex = RCHILD(index);
    int CurrentIndex = index;

    if (HAS_LEFT(pMinHeap, index) &&
        (pMinHeap->cmpFn)(pMinHeap->memory[LeftChildIndex], pMinHeap->memory[CurrentIndex]) < 0){
        CurrentIndex = LeftChildIndex;
    }

    if (HAS_RIGHT(pMinHeap, index) &&
        (pMinHeap->cmpFn)(pMinHeap->memory[RightChildIndex], pMinHeap->memory[CurrentIndex]) < 0 ){
        CurrentIndex = RightChildIndex;
    }

    if (CurrentIndex != index){
        void* temp  = pMinHeap->memory[index];
        pMinHeap->memory[index]=pMinHeap->memory[CurrentIndex];
        pMinHeap->memory[CurrentIndex] = temp;
        index = CurrentIndex;
    }
    else
        return;
    MinHeapifyDown(pMinHeap, index);
}

/** Given an array containing preallocated pointer to objects, this function creates a new heap with the objects in it.
 *  @param arr Array to add elements from into the heap.
 *  @param size Size of the array to be inserted into the heap.
 *  @param cmp  compare function for values stored in the heap.
 *  @return Reference to minimum heap pointer allocated on the pMinHeap.
**/
BinaryMinHeap *MinHeapify(void *arr, uint32_t size,int32_t (*cmp)(const void*, const void*)){
    BinaryMinHeap *h = malloc(sizeof(BinaryMinHeap));
    h->capacity = size;
    void **harr = malloc(sizeof(void*)*h->capacity);
    h->memory = harr;
    h->size = 0;
    h->cmpFn = cmp;
    for (int i = 0; i < h->capacity; ++i) {
        MinHeapInsert(h, arr + i);
    }
    return h;
}

/** Given a reference to heap prints it's elements.
 *  @param pMinHeap  Reference to minimum heap pointer allocated on the heap.
 *  @param printfn pointer to the print funtion to be used.
**/
void printMinHeap(BinaryMinHeap *pMinHeap, void (*printfn)(void *)){
    for (int i = 0; i < pMinHeap->size; ++i) {
        (printfn)(pMinHeap->memory[i]);
    }
    puts("\n");
}

/** Given an array of void pointers to pre-allocated objects, it inserts them in a maximum heap.
 *  @param pMinHeap  Reference to minimum heap pointer allocated on the heap.
 *  @param arr array to add elements from into the heap.
 *  @param size Size of the array to be inserted into the heap.
**/
void MinHeapAddAll(BinaryMinHeap *pMinHeap, void **arr, uint32_t size){
    for(int i=0;i<size;i++){
        MinHeapInsert(pMinHeap, arr[i]);
    }
}

/** Given a heap it frees its memory container and the allocated pointer within it,
  setting them null as well as the memory container and frees the heap pointer.
 *  @param pMinHeap  Reference to minimum heap pointer allocated on the heap.
**/
void MinHeapDestroy(BinaryMinHeap * pMinHeap) {
    MinHeapClear(pMinHeap);
    free(pMinHeap->memory);
    pMinHeap->memory = NULL;
    free(pMinHeap);
}

/** Given a heap pointer it frees it's memory container contents. But not the memory container of the heap.
 * @param pMinHeap Reference to minimum heap pointer allocated on the heap.
 * */
void MinHeapClear(BinaryMinHeap * pMinHeap){
    for(int i =0; i < pMinHeap->size; i++){
        pMinHeap->freeFn(pMinHeap->memory[i]);
        pMinHeap->memory[i] =NULL;
    }
}