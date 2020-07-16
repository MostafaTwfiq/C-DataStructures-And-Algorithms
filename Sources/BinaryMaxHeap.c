#include "../Headers/BinaryMaxHeap.h"

/** Restores the heap property , by recursively traversing the heap. Moving elements up the maximum tree.
 *  @param h  Reference to maximum heap pointer allocated on the heap.
 *  @param index
**/
void MaxHeapifyUP(BinaryMaxHeap* h, int index){
    if(!index) return;
    int p = PARENT(index);
    if (((h->cmpFn)(h->memory[p], h->memory[index])) < 0){
        void* temp = h->memory[p];
        h->memory[p] = h->memory[index];
        h->memory[index] = temp;
        MaxHeapifyUP(h,p);
    }

}

/** Function that ensures heap property, by recursively traversing the heap. Moving elements down the maximum tree.
 *  @param heap  Reference to maximum heap pointer allocated on the pMinHeap.
 *  @param index index to heapify at.
**/
void MaxHeapifyDown(BinaryMaxHeap *heap, int index) {
    if (index < 0) return;
    if(index > heap->size) return;

    int LeftChildIndex = LCHILD(index);
    int RightChildIndex = RCHILD(index);
    int CurrentIndex = index;

    if (HAS_LEFT(heap,index) &&
        heap->cmpFn(heap->memory[LeftChildIndex], heap->memory[CurrentIndex]) > 0){
        CurrentIndex = LeftChildIndex;
    }
    if (HAS_RIGHT(heap,index)&&
        heap->cmpFn(heap->memory[RightChildIndex], heap->memory[CurrentIndex]) > 0 ){
        CurrentIndex = RightChildIndex;
    }

    if (CurrentIndex != index){
        //swap1(heap->memory + index, heap->memory + CurrentIndex);

        void* temp = heap->memory[index];
        heap->memory[index] = heap->memory[CurrentIndex];
        heap->memory[CurrentIndex] = temp;

        index = CurrentIndex;
    }
    else
        return;

    MaxHeapifyDown(heap,index);
}

/** Allocates space for maximum heap on the heap. Setting the inital size to 0 and the initial allocated size to 10.
 *  @param cmp compare function for values stored in the heap.
 *  @return Returns pointer to the allocated maximum heap on the heap.
**/
BinaryMaxHeap *MaxHeapInitialize( int32_t (*cmp)(const void*, const void*),void  (*freeFn)(void*)) {
    BinaryMaxHeap *h = malloc(sizeof(*h));
    h->capacity      = 10;
    void **harr      = (void **)malloc(sizeof(void*)*h->capacity);
    h->memory        = harr;
    h->size          = 0;
    h->cmpFn         = cmp;
    h->freeFn        = freeFn;
    return h;
}

/** Inserts at the bottom of the tree then moves the element up the tree by calling @link MaxHeapifyUP @endlink
 *  @param h  Reference to maximum heap pointer allocated on the heap.
 *  @param value item to insert in the tree.
**/
void MaxHeapInsert(BinaryMaxHeap* h, void* value) {
    if(h->size == h->capacity){
        h->capacity *=2;
        h->memory = realloc(h->memory, sizeof(void*)*h->capacity);
    }
    h->memory[h->size] = value;
    MaxHeapifyUP(h,h->size++);
}

/** Deletes the root element of the heap and restores the heap property of the heap.
 *  @param heap Reference to maximum heap pointer allocated on the heap.
 *  @param res pointer to store the root if needed.
**/
void MaxHeapDelete(BinaryMaxHeap* heap, void ** res) {
    *res = heap->memory[0];
    heap->memory[0] = heap->memory[heap->size - 1];
    heap->memory[heap->size - 1] = NULL;
    heap->size--;
    MaxHeapifyDown(heap,0);
}

/** Given an array containing preallocated pointer to objects, this function creates a new heap with the objects in it.
 *  @param arr Array to add elements from into the heap.
 *  @param size Size of the array to be inserted into the heap.
 *  @param cmp  compare function for values stored in the heap.
 *  @return Reference to maximum heap pointer allocated on the pMinHeap.
 **/
BinaryMaxHeap *MaxHeapify(void **arr, uint32_t size,int32_t (*cmp)(const void*, const void*)) {
    BinaryMaxHeap *h = malloc(sizeof(*h));
    h->capacity = 10;
    void **harr = (void **)malloc(sizeof(void*)*h->capacity);
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
    for(int i=0;i<size;i++){
        MaxHeapInsert(binaryMaxHeap,arr[i]);
    }
}

/** Given a reference to heap prints it's elements.
 *  @param h  Reference to maximum heap pointer allocated on the heap.
 *  @param printfn pointer to the print funtion to be used.
**/
void printMaxHeap(BinaryMaxHeap *h, void (*printfn)(void *)) {
    for (int i = 0; i < h->size; ++i) {
        (printfn)(h->memory[i]);
    }
    puts("\n");
}

/** Given a heap it frees its memory container and the allocated pointer within it,
  setting them null as well as the memory container and frees the heap pointer.
 *  @param heap  Reference to maximum heap pointer allocated on the heap.
**/
void destroyMaxHeap(BinaryMaxHeap * heap) {
    MaxHeapClear(heap);
    free(heap->memory);
    heap->memory = NULL;
    free(heap);
}

/** Given a heap pointer it frees it's memory container contents. But not the memory container of the heap.
 * @param pMaxHeap Reference to maximum heap pointer allocated on the heap.
 * */
void MaxHeapClear(BinaryMaxHeap * pMaxHeap){
    for(int i =0; i < pMaxHeap->size; i++){
        pMaxHeap->freeFn(pMaxHeap->memory[i]);
        pMaxHeap->memory[i] =NULL;
    }
}


















