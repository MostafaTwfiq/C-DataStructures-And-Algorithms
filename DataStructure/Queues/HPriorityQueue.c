#include "HPriorityQueue.h"
#include "../../System/Utils.h"
#include "../../Unit Test/CuTest/CuTest.h"
#include "../Trees/Headers/BinaryHeap.h"
#include "../Trees/Sources/BinaryHeap.c"




/** This function will allocate a new heap priority queue then it will return its pointer.
 *
 * @param freeFn the free function pointer, that will be called to free the queue items
 * @param cmp the comparator function pointer, that will be called to compare the queue items
 * @return it will return the new allocated queue pointer
 */

HPriorityQueue *hPriorityQueueInitialization(void (*freeFn)(void *), int (*cmp)(const void *, const void *)) {

    HPriorityQueue *queue = (HPriorityQueue *) malloc(sizeof(HPriorityQueue));

    queue->heap = binaryHeapInitialization(freeFn, cmp);

    return queue;

}





/** This function will insert the passed item in the queue.
 *
 * @param queue the queue pointer
 * @param item the new item pointer
 */

void hpQueueEnqueue(HPriorityQueue *queue, void *item) {

    if (queue == NULL) {

    } else if (item == NULL) {

    }

    binaryHeapInsert(queue->heap, item);

}




/** This function will insert all the passed array items in the queue.
 *
 * @param queue the queue pointer
 * @param items the new items array pointer
 * @param length the length of the new items array
 */
void hpQueueEnqueueAll(HPriorityQueue *queue, void *items, int length) {

    if (queue == NULL) {

    } else if (items == NULL) {

    }

    binaryHeapInsertAll(queue->heap, items, length);

}




/** This function will remove the first item from the queue,
 * then it will return it.
 *
 * @param queue the queue pointer
 * @return it will return the first item in the queue
 */

void *hpQueueDequeue(HPriorityQueue *queue) {

    if (queue == NULL) {

    } else if (hpQueueIsEmpty(queue)) {

    }

    return binaryHeapDeleteRootWtoFr(queue->heap);

}




/** This function will return the first item in the queue without removing it from the queue.
 *
 * @param queue the queue pointer
 * @return it will return the first item in the queue
 */

void *hpQueuePeek(HPriorityQueue *queue) {

    if (queue == NULL) {

    } else if (hpQueueIsEmpty(queue)) {

    }

    return *queue->heap->arr;

}




/** This function will return the number of items in the queue.
 *
 * @param queue the queue pointer
 * @return it will return the number of items in the queue
 */

int hpQueueGetLength(HPriorityQueue *queue) {
    return binaryHeapGetSize(queue->heap);
}




/** This function will check if the queue is empty or not,
 * and if it was the function will return one (1),
 * other wise it will return zero (0).
 *
 * @param queue the queue pointer
 * @return it will return 1 if the queue was empty, other wise it will return 0
 */

int hpQueueIsEmpty(HPriorityQueue *queue) {
    return binaryHeapIsEmpty(queue->heap);
}




/** This function will return a double void array that contains the queue items.
 *
 * Note: the array will be sorted.
 *
 * @param queue the queue pointer
 * @return it will return a double void array pointer, that contains the queue items
 */

void **hpQueueToArray(HPriorityQueue *queue) {
    void **arr =  binaryHeapToArray(queue->heap);

    int length = hpQueueGetLength(queue);

    while (length-- > 0) {
        binaryHeapSwap(arr, 0, length);
        binaryHeapDown(arr, 0, length, queue->heap->cmp);
    }

    return arr;

}




/** This function will clear the queue and free all it's items,
 * without freeing the queue itself.
 *
 * @param queue the queue pointer
 */

void clearHPQueue(HPriorityQueue *queue) {

    clearBinaryHeap(queue->heap);

}




/** This function will destroy and free the queue and it's items.
 *
 * @param queue the queue pointer
 */

void destroyHPQueue(HPriorityQueue *queue) {

    destroyBinaryHeap(queue->heap);

    free(queue);

}