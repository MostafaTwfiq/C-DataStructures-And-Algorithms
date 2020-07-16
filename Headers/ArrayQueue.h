#ifndef C_DATASTRUCTURES_ARRAYQUEUE_H
#define C_DATASTRUCTURES_ARRAYQUEUE_H

#include "Utils.h"

#ifdef __cplusplus
extern "C" {
#endif

/** @struct ArrayQueue
 *  @brief This structure implements a basic generic Queue where memory is laid out sequentially.
 *  @var ArrayQueue:: memory
 *  Member 'memory' is a pointer to the the Queue's memory.
 *  @var ArrayQueue::allocated
 *  Member 'allocated' holds the current max allocated size for the Queue.
 *  @var ArrayQueue::front
 *  Member 'front' holds the index to the front of the Queue Element.
  *  @var ArrayQueue::rear
 *  Member 'rear' holds the index to the last Queue Element.
 *  @var ArrayQueue::sizeOfItem
 *  Member 'sizeOfItem' the size of the data stored in the Queue.
 *  @var ArrayQueue:: 'freeFn'
 *  Member 'freeFn' holds pointer to the function responsible for freeing the elements stored in the Deque.
 */


typedef struct ArrayQueue{
    void ** memory;
    int allocated;
    int front;
    int rear;
    void (*freeItem)(void *);
} ArrayQueue;



ArrayQueue *QueueInitialize(void (*freeFn)(void *));


void ArrayQueueEnqueue(ArrayQueue* arrayQueue, void *data);


void *ArrayQueueDequeue(ArrayQueue *arrayQueue);


void ArrayQueueDisplay(ArrayQueue *arrayQueue, void(*fptr)(void *));


void ArrayQueueDestroy(ArrayQueue *arrayQueue);


void ArrayQueueClear(ArrayQueue *arrayQueue);


int16_t isArrayQueueEmpty(ArrayQueue *arrayQueue);


uint32_t ArrayQueueLength(ArrayQueue *arrayQueue);


void ArrayQueueEnqueueAll(ArrayQueue * arrayQueue, void **arr, int arrLength);


void *ArrayQueuePeek(ArrayQueue *arrayQueue);


void **ArrayQueueToArray(ArrayQueue *arrayQueue);

#ifdef __cplusplus
}
#endif

#endif //C_DATASTRUCTURES_ARRAYQUEUE_H
