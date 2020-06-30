#include "../Headers/BinaryMaxHeap.h"



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



BinaryMaxHeap *MaxHeapInitialize(uint16_t size, int16_t (*cmp)(const void*, const void*)) {
    BinaryMaxHeap *h = malloc(sizeof(*h));
    h->capacity = 10;
    void **harr = (void **)malloc(sizeof(void*)*h->capacity);
    h->memory = harr;
    h->size = 0;
    h->cmpFn = cmp;
    return h;
}

void MaxHeapInsert(BinaryMaxHeap* h, void* value) {
    if(h->size == h->capacity){
        h->capacity *=2;
        h->memory = realloc(h->memory, sizeof(void*)*h->capacity);
    }
    h->memory[h->size] = value;
    MaxHeapifyUP(h,h->size++);
}

void MaxHeapDelete(BinaryMaxHeap* heap, void ** res) {
    *res = heap->memory[0];
    heap->memory[0] = heap->memory[heap->size - 1];
    heap->memory[heap->size - 1] = NULL;
    heap->size--;
    MaxHeapifyDown(heap,0);
    //MaxHeapFloatDown(heap,0);
}

BinaryMaxHeap *MaxHeapify(void **arr, uint16_t size,int16_t (*cmp)(const void*, const void*)) {
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

void * MaxHeapAddAll(BinaryMaxHeap *binaryMaxHeap,void **arr, uint16_t size){
    for(int i=0;i<size;i++){
        MaxHeapInsert(binaryMaxHeap,arr[i]);
    }
}

void destroyMaxHeap(BinaryMaxHeap * heap) {
    free(heap->memory);
    free(heap);
}

void printMaxHeap(BinaryMaxHeap *h, void (*printfn)(void *)) {
    for (int i = 0; i < h->size; ++i) {
        (printfn)(h->memory[i]);
    }
    puts("\n");
}