#include "../Headers/BinaryMinHeap.h"

void swap(void** x, void** y) {
    void* temp = *x;
    *x = *y;
    *y = temp;
}

BinaryMinHeap *MinHeapInitialize(uint16_t size, int16_t (*cmp)(const void*, const void*)){
    BinaryMinHeap *h = malloc(sizeof(*h));
    h->capacity = 50;
    void **harr = (void **)malloc(sizeof(void*)*h->capacity);
    h->memory = harr;
    h->size = 0;
    h->cmpFn = cmp;
    return h;
};

void MinHeapDelete(BinaryMinHeap* heap, void ** res) {
    *res = heap->memory[0];
    heap->memory[0] = heap->memory[heap->size - 1];
    heap->memory[heap->size - 1] = NULL;
    heap->size--;
    MinHeapifyDown(heap, 0);
}

void MinHeapifyUP(BinaryMinHeap* h, int index) {
    if(index){
        int p = PARENT(index);
        if (((h->cmpFn)(h->memory[p], h->memory[index])) >0) {
            swap(&h->memory[p], &h->memory[index]);
        }
        MinHeapifyUP(h, p);
    }
}

void insertInMinHeap(BinaryMinHeap* h, void* value){
    if(h->size == h->capacity){
        h->capacity *= 2;
        h->memory = realloc(h->memory, sizeof(void*) * h->capacity);
    }
    h->memory[h->size] = value;
    MinHeapifyUP(h,h->size++);
}

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
        swap(heap->memory + index, heap->memory + CurrentIndex);

        index = CurrentIndex;
    }
    else
        return;
    MinHeapifyDown(heap,index);
}


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

void printMinHeap(BinaryMinHeap *h, void (*printfn)(void *)){
    for (int i = 0; i < h->size; ++i) {
        (printfn)(h->memory[i]);
    }
    puts("\n");
}

void * MinHeapAddAll(BinaryMinHeap *binaryMaxHeap,void **arr, uint16_t size){
    for(int i=0;i<size;i++){
        insertInMinHeap(binaryMaxHeap,arr[i]);
    }
}


void destroyMinHeap(BinaryMinHeap * h) {
    free(h->memory);
    free(h);
}