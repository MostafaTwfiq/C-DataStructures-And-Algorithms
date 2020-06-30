#include "../Headers/MinHeap.h"

void swap(void** x, void** y) {
    void* temp = *x;
    *x = *y;
    *y = temp;
}

MinHeap *MinHeapInitialize(uint8_t type, uint16_t size,int16_t (*cmp)(const void*,const void*)){
    MinHeap *h = malloc(sizeof(*h));
    h->capacity = 10;
    void **harr = (void **)malloc(sizeof(void*)*h->capacity);
    h->memory = harr;
    h->size = 0;
    h->cmpFn = cmp;
    return h;
};


void MinHeapifyUP(MinHeap* h, int index){
    if(index){
        int p = PARENT(index);
/*       if (h->type == MAX_MinHeap){
            if (((h->cmpFn)(h->memory[p], h->memory[index])) < 0){
                swap(h->memory + p, h->memory + index);
                MinHeapifyUP(h,p);
            }*/
            if (((h->cmpFn)(h->memory[p], h->memory[index])) == 1) {
                swap(&h->memory[p], &h->memory[index]);
                MinHeapifyUP(h, p);
            }
    }
}

void insertInMinHeap(MinHeap* h,void* value){
    if(h->size == h->capacity){
        h->capacity *=2;
        h->memory = realloc(h->memory, sizeof(void*)*h->capacity);
    }
    h->memory[h->size] = value;
    MinHeapifyUP(h,h->size++);
}


void MinHeapifyDown(MinHeap* h, int index){
    if(index){
        if( !HAS_RIGHT(h,index) && !HAS_LEFT(h,index) )
            return;

        if( HAS_LEFT(h,index) && ((h->cmpFn)(h->memory[index], h->memory[LCHILD(index)])<0
            && ( ( HAS_RIGHT(h,index) && ((h->cmpFn)(h->memory[index], h->memory[LCHILD(index)]))<0
            || !   HAS_RIGHT(h,index) ) )))
            return;

        unsigned int smaller;
        if( HAS_RIGHT(h,index) &&((h->cmpFn)(h->memory[RCHILD(index)], h->memory[LCHILD(index)]))<0)
            smaller = RCHILD(index);
        else
            smaller = LCHILD(index);
        swap( &h->memory[index], &h->memory[smaller] );
        MinHeapifyDown( h, smaller );
    }
}

MinHeap *MinHeapify(void *arr,uint16_t size, uint8_t type){
    MinHeap *h = malloc(sizeof(MinHeap));
    h->capacity = size;
    void **harr = malloc(sizeof(void*)*h->capacity);
    h->memory = harr;
    h->type = type;
    h->size = 0;
    for (int i = 0; i < h->capacity; ++i) {
        insertInMinHeap(h,arr+i);
    }
    return h;
}

void printMinHeap(MinHeap *h, void (*printfn)(void *)){
    for (int i = 0; i < h->size; ++i) {
        (printfn)(h->memory[i]);
    }
    puts("\n");
}

void destroyMinHeap(MinHeap * h) {
    free(h->memory);
    free(h);
}