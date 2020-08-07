#include "../Headers/BinaryHeap.h"
#include "../../../System/Utils.h"



int binaryHeapContainsR(void **arr, int currentIndex, int length, void *item, int (*cmp)(const void *, const void *));

void *binaryHeapGetR(void **arr, int currentIndex, int length, void *item, int (*cmp)(const void *, const void *));



int binaryHeapGetParentIndex(int childIndex) {

    return (childIndex - 1) / 2;

}


int binaryHeapGetFChildIndex(int parentIndex) {
    return parentIndex * 2 + 1;
}


int binaryHeapGetSChildIndex(int parentIndex) {
    return parentIndex * 2 + 2;
}



void binaryHeapSwap(void **arr, int fIndex, int sIndex) {

    void *tempItem = arr[sIndex];
    arr[sIndex] = arr[fIndex];
    arr[fIndex] = tempItem;

}



void binaryHeapUp(void **arr, int currentIndex, int (*cmp)(const void *, const void *)) {

    if (currentIndex <= 0)
        return;

    int parentIndex = binaryHeapGetParentIndex(currentIndex);
    if ( cmp(arr[currentIndex], arr[parentIndex]) > 0 ) {
        binaryHeapSwap(arr, currentIndex, parentIndex);
        binaryHeapUp(arr, parentIndex, cmp);
    }

}





void binaryHeapDown(void **arr, int currentIndex, int length, int (*cmp)(const void *, const void *)) {

    if (currentIndex >= length)
        return;

    int fChildIndex = binaryHeapGetFChildIndex(currentIndex);
    int sChildIndex = binaryHeapGetSChildIndex(currentIndex);

    fChildIndex = fChildIndex >= length ? currentIndex : fChildIndex;
    sChildIndex = sChildIndex >= length ? currentIndex : sChildIndex;

    if ( cmp(arr[currentIndex], arr[fChildIndex]) < 0 && cmp(arr[currentIndex], arr[sChildIndex]) < 0 ) {

        int biggestChildIndex = cmp(arr[fChildIndex], arr[sChildIndex]) < 0 ? sChildIndex : fChildIndex;
        binaryHeapSwap(arr, currentIndex, biggestChildIndex);
        binaryHeapDown(arr, biggestChildIndex, length, cmp);

    } else if ( cmp(arr[currentIndex], arr[fChildIndex]) < 0 ) {

        binaryHeapSwap(arr, currentIndex, fChildIndex);
        binaryHeapDown(arr, fChildIndex, length, cmp);

    } else if ( cmp(arr[currentIndex], arr[sChildIndex]) < 0 ) {

        binaryHeapSwap(arr, currentIndex, sChildIndex);
        binaryHeapDown(arr, sChildIndex, length, cmp);

    }

}




BinaryHeap *binaryHeapInitialization(void (*freeFun)(void *), int (*cmp)(const void *, const void *)) {

    if (freeFun == NULL) {

    } else if (cmp == NULL) {

    }


    BinaryHeap *heap = (BinaryHeap *) malloc(sizeof(BinaryHeap));

    heap->freeFun = freeFun;
    heap->cmp = cmp;
    heap->count = 0;
    heap->length = 10;
    heap->arr = (void **) malloc(sizeof(void *) * heap->length);

    if (heap->arr == NULL) {
    }


    return heap;

}





void binaryHeapInsert(BinaryHeap *heap, void *item) {

    if (heap->count == heap->length) {
        heap->length *= 2;

        heap->arr = realloc(heap->arr, sizeof(void *) * heap->length);
        if (heap->arr == NULL) {

        }

    }

    heap->arr[heap->count++] = item;
    binaryHeapUp(heap->arr, heap->count - 1, heap->cmp);

}





void binaryHeapInsertAll(BinaryHeap *heap, void **items, int length) {


    for (int i = 0; i < length; i++)
        binaryHeapInsert(heap, items[i]);

}




void binaryHeapDeleteRoot(BinaryHeap *heap) {


    if (binaryHeapIsEmpty(heap)) {

    }

    heap->freeFun(heap->arr[0]);
    heap->arr[0] = heap->arr[--heap->count];

    binaryHeapDown(heap->arr, 0, heap->count, heap->cmp);

}



void binaryHeapDeleteRootWtoFr(BinaryHeap *heap) {


    if (binaryHeapIsEmpty(heap)) {

    }

    heap->arr[0] = heap->arr[--heap->count];

    binaryHeapDown(heap->arr, 0, heap->count, heap->cmp);

}




int binaryHeapContains(BinaryHeap *heap, void *item) {


   return binaryHeapContainsR(heap->arr, 0, heap->count, item, heap->cmp);

}




int binaryHeapContainsR(void **arr, int currentIndex, int length, void *item, int (*cmp)(const void *, const void *)) {

    if (currentIndex >= length)
        return 0;


    if ( cmp(item, arr[currentIndex]) == 0 )
        return 1;
    else if ( cmp(item, arr[currentIndex]) > 0 )
        return 0;


    return
    binaryHeapContainsR(arr, binaryHeapGetFChildIndex(currentIndex), length, item, cmp)
    || binaryHeapContainsR(arr, binaryHeapGetSChildIndex(currentIndex), length, item, cmp);

}






void *binaryHeapGet(BinaryHeap *heap, void *item) {


    return binaryHeapGetR(heap->arr, 0, heap->count, item, heap->cmp);

}




void *binaryHeapGetR(void **arr, int currentIndex, int length, void *item, int (*cmp)(const void *, const void *)) {

    if (currentIndex >= length)
        return NULL;


    if ( cmp(item, arr[currentIndex]) == 0 )
        return arr[currentIndex];
    else if ( cmp(item, arr[currentIndex]) > 0 )
        return NULL;


    void *fVal = binaryHeapGetR(arr, binaryHeapGetFChildIndex(currentIndex), length, item, cmp);
    void *sVal = binaryHeapGetR(arr, binaryHeapGetSChildIndex(currentIndex), length, item, cmp);

    return fVal != NULL ? fVal : sVal;

}





int binaryHeapGetSize(BinaryHeap *heap) {

    return heap->count;

}


int binaryHeapIsEmpty(BinaryHeap *heap) {

    return heap->count == 0;

}



void **binaryHeapToArray(BinaryHeap *heap) {


    void **arr = (void **) malloc(sizeof(void *) * heap->count);

    memcpy(arr, heap->arr, sizeof(void *) * heap->count);

    return arr;

}




void clearBinaryHeap(BinaryHeap *heap) {

    for (int i = 0; i < heap->count; i++)
        heap->freeFun(heap->arr[i]);


    heap->count = 0;

}




void destroyBinaryHeap(BinaryHeap *heap) {

    clearBinaryHeap(heap);

    free(heap->arr);
    free(heap);

}