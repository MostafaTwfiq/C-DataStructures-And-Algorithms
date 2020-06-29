#include "../Headers/Heap.h"

void swap(void** x, void** y) {
    void* temp = *x;
    *x = *y;
    *y = temp;
}

Heap *HeapInitialize(uint8_t type, uint16_t size,int16_t (*cmp)(void*,void*)){
    Heap *h = malloc(sizeof(Heap));
    h->capacity = 10;
    void **harr = (void **)malloc(sizeof(void*)*h->capacity);
    h->memory = harr;
    h->type = type;
    h->size = 0;
    h->cmpFn = cmp;
    return h;
};

void heapifyUP(Heap* h, int index){
    if(index){
        int p = PARENT(index);
        if (h->type == MAX_HEAP){
            if (((h->cmpFn)(h->memory[p], h->memory[index])) == -1){
                swap(&h->memory[p], &h->memory[index]);
                heapifyUP(h,p);
            }
        } else if (h->type == MIN_HEAP) {
            if (((h->cmpFn)(h->memory[p], h->memory[index])) == 1) {
                swap(&h->memory[p], &h->memory[index]);
                heapifyUP(h, p);
            }
        }
    }
}



void heapifyDown(Heap* h, int index){
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
        heapifyDown( h, smaller );
    }
}

void insertInHeap(Heap* h,void* value){
    h->memory[h->size] = value;
    //heapifyDown(h,h->size++);
    heapifyUP(h,h->size++);
}

Heap *heapify(void *arr,uint16_t size, uint8_t type){
    Heap *h = malloc(sizeof(Heap));
    h->capacity = size;
    void **harr = malloc(sizeof(void*)*h->capacity);
    h->memory = harr;
    h->type = type;
    h->size = 0;
    for (int i = 0; i < h->capacity; ++i) {
        insertInHeap(h,arr+i);
    }
    return h;
}

void printHeap(Heap *h, void (*printfn)(void *)){
    puts("------------------------------------------------");
    puts("Stored Values:");
    for (int i = 0; i < h->size; ++i) {
        (printfn)(h->memory[i]);
    }
    puts("\n");
    printf("Number of nodes: %d\n",h->size);
    printf("Heap capacity: %d\n",h->capacity);
    printf("Type of heap: %s heap.\n",(h->type == MIN_HEAP)?"MIN":"MAX");
    puts("------------------------------------------------");
}

void destroyHeap(Heap * h) {
    free(h->memory);
    free(h);
}