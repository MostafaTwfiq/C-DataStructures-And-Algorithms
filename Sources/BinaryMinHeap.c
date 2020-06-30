#include "../Headers/BinaryMinHeap.h"

///
/// \param size
/// \param cmp
/// \return
BinaryMinHeap *MinHeapInitialize(uint16_t size, int16_t (*cmp)(const void*, const void*)){
    BinaryMinHeap *h = malloc(sizeof(*h));
    h->capacity = 50;
    void **harr = (void **)malloc(sizeof(void*)*h->capacity);
    h->memory = harr;
    h->size = 0;
    h->cmpFn = cmp;
    return h;
};

///
/// \param heap
/// \param res
void MinHeapDelete(BinaryMinHeap* heap, void ** res) {
    *res = heap->memory[0];
    heap->memory[0] = heap->memory[heap->size - 1];
    heap->memory[heap->size - 1] = NULL;
    heap->size--;
    MinHeapifyDown(heap, 0);
}

///
/// \param h
/// \param index
void MinHeapifyUP(BinaryMinHeap* h, int index) {
    if(index){
        int p = PARENT(index);
        if (((h->cmpFn)(h->memory[p], h->memory[index])) >0) {
            void* temp = h->memory[p];
            h->memory[p] = h->memory[index];
            h->memory[index]= temp;
        }
        MinHeapifyUP(h, p);
    }
}

///
/// \param h
/// \param value
void insertInMinHeap(BinaryMinHeap* h, void* value){
    if(h->size == h->capacity){
        h->capacity *= 2;
        h->memory = realloc(h->memory, sizeof(void*) * h->capacity);
    }
    h->memory[h->size] = value;
    MinHeapifyUP(h,h->size++);
}

///
/// \param heap
/// \param index
void MinHeapifyDown(BinaryMinHeap *heap, int index) {
    if (index < 0) return;
    if(index > heap->size) return;
    int LeftChildIndex = LCHILD(index);
    int RightChildIndex = RCHILD(index);
    int CurrentIndex = index;

    if (HAS_LEFT(heap,index) &&
        (heap->cmpFn)(heap->memory[LeftChildIndex], heap->memory[CurrentIndex]) < 0){
        CurrentIndex = LeftChildIndex;
    }

    if (HAS_RIGHT(heap,index)&&
        (heap->cmpFn)(heap->memory[RightChildIndex], heap->memory[CurrentIndex]) < 0 ){
        CurrentIndex = RightChildIndex;
    }

    if (CurrentIndex != index){
        void* temp  = heap->memory[index];
        heap->memory[index]=heap->memory[CurrentIndex];
        heap->memory[CurrentIndex] = temp;
        index = CurrentIndex;
    }
    else
        return;
    MinHeapifyDown(heap,index);
}

///
/// \param arr
/// \param size
/// \param type
/// \return
BinaryMinHeap *MinHeapify(void *arr, uint16_t size, uint8_t type){
    BinaryMinHeap *h = malloc(sizeof(BinaryMinHeap));
    h->capacity = size;
    void **harr = malloc(sizeof(void*)*h->capacity);
    h->memory = harr;
    h->size = 0;
    for (int i = 0; i < h->capacity; ++i) {
        insertInMinHeap(h,arr+i);
    }
    return h;
}

///
/// \param h
/// \param printfn
void printMinHeap(BinaryMinHeap *h, void (*printfn)(void *)){
    for (int i = 0; i < h->size; ++i) {
        (printfn)(h->memory[i]);
    }
    puts("\n");
}

///
/// \param binaryMaxHeap
/// \param arr
/// \param size
/// \return
void * MinHeapAddAll(BinaryMinHeap *binaryMaxHeap,void **arr, uint16_t size){
    for(int i=0;i<size;i++){
        insertInMinHeap(binaryMaxHeap,arr[i]);
    }
}

///
/// \param h
void destroyMinHeap(BinaryMinHeap * h) {
    free(h->memory);
    free(h);
}