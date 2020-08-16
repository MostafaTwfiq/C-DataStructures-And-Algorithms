#include "HPriorityQueue.h"
#include "../../System/Utils.h"
#include "../../Unit Test/CuTest/CuTest.h"
#include "../Trees/Headers/BinaryHeap.h"
#include "../Trees/Sources/BinaryHeap.c"



HPriorityQueue *hPriorityQueueInitialization(void (*freeFn)(void *), int (*cmp)(const void *, const void *)) {

    HPriorityQueue *queue = (HPriorityQueue *) malloc(sizeof(HPriorityQueue));

    queue->heap = binaryHeapInitialization(freeFn, cmp);

    return queue;

}



void hpQueueEnqueue(HPriorityQueue *queue, void *item) {

    if (queue == NULL) {

    } else if (item == NULL) {

    }

    binaryHeapInsert(queue->heap, item);

}


void hpQueueEnqueueAll(HPriorityQueue *queue, void *items, int length) {

    if (queue == NULL) {

    } else if (items == NULL) {

    }

    binaryHeapInsertAll(queue->heap, items, length);

}



void *hpQueueDequeue(HPriorityQueue *queue) {

    if (queue == NULL) {

    } else if (hpQueueIsEmpty(queue)) {

    }

    return binaryHeapDeleteRootWtoFr(queue->heap);

}



void *hpQueuePeek(HPriorityQueue *queue) {

    if (queue == NULL) {

    } else if (hpQueueIsEmpty(queue)) {

    }

    return *queue->heap->arr;

}



int hpQueueGetLength(HPriorityQueue *queue) {
    return binaryHeapGetSize(queue->heap);
}


int hpQueueIsEmpty(HPriorityQueue *queue) {
    return binaryHeapIsEmpty(queue->heap);
}


void **hpQueueToArray(HPriorityQueue *queue) {
    void **arr =  binaryHeapToArray(queue->heap);

    int length = hpQueueGetLength(queue);

    while (length-- > 0) {
        binaryHeapSwap(arr, 0, length);
        binaryHeapDown(arr, 0, length, queue->heap->cmp);
    }

    return arr;

}

void clearHPQueue(HPriorityQueue *queue) {

    clearBinaryHeap(queue->heap);

}

void destroyHPQueue(HPriorityQueue *queue) {

    destroyBinaryHeap(queue->heap);

    free(queue);

}