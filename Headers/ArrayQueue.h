#ifndef C_DATASTRUCTURES_ARRAYQUEUE_H
#define C_DATASTRUCTURES_ARRAYQUEUE_H

#include "Utils.h"



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
 */

typedef struct ArrayQueue{
    void ** memory;
    int allocated;
    int front;
    int rear;
    void (*freeItem)(void *);
} ArrayQueue;



ArrayQueue* QueueInitialize(void (*freeItem)(void *item));

void ArrayQueueEnqueue(ArrayQueue* arrayQueue, void *data);

void *ArrayQueueDequeue(ArrayQueue *arrayQueue);

void ArrayQueueDisplay(ArrayQueue *arrayQueue,void(*fptr)(void *));

void ArrayQueueDestroy(ArrayQueue *arrayQueue);

void ArrayQueueClear(ArrayQueue *arrayQueue);

short isArrayQueueEmpty(ArrayQueue *arrayQueue);

int ArrayQueueLength(ArrayQueue * arrayQueue);

void ArrayQueueEnqueueAll(ArrayQueue * arrayQueue, void **arr, int arrLength);

void *ArrayQueuePeek(ArrayQueue * arrayQueue);

void **ArrayQueueToArray(ArrayQueue * arrayQueue);

#endif //C_DATASTRUCTURES_ARRAYQUEUE_H
