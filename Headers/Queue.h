#ifndef C_DATASTRUCTURES_QUEUE_H
#define C_DATASTRUCTURES_QUEUE_H

#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "ErrorCode.h"

/** @struct ArrayQueue
 *  @brief This structure implements a basic generic Queue where memory is laid out sequentially.
 *  @var ArrayQueue:: memory
 *  Member 'memory' is a pointer to the the Queue's memory.
 *  @var ArrayQueue::allocated
 *  Member 'allocated' holds the current max allocated size for the Queue.
 *  @var ArrayQueue::front
 *  Member 'top' holds the index to the front of the Queue Element.
  *  @var ArrayQueue::rear
 *  Member 'top' holds the index to the last Queue Element.
 *  @var ArrayQueue::sizeOfType
 *  Member 'sizeOfType' the size of the data stored in the Queue.
 */
typedef struct ArrayQueue{
    void ** memory;
    int allocated;
    int front;
    int rear;
    int sizeOfType;
}ArrayQueue;

ArrayQueue *QueueInitialize(int size);

void ArrayQueueEnqueue(ArrayQueue *arrayQueue,void *data);

void *ArrayQueueDequeue(ArrayQueue *arrayQueue);

void ArrayQueueDisplay(ArrayQueue *arrayQueue,void(*fptr)(void *));

void ArrayQueueDestroy(ArrayQueue *arrayQueue);

void ArrayQueueClear(ArrayQueue *arrayQueue);

short isArrayQueueEmpty(ArrayQueue *arrayQueue);

int ArrayQueueLength(ArrayQueue * arrayQueue);

void ArrayQueueEnqueueAll(ArrayQueue * arrayQueue,void *arr, int arrLength);

void *ArrayQueuePeek(ArrayQueue * arrayQueue);

void *ArrayQueueToArray(ArrayQueue * arrayQueue);

#endif //C_DATASTRUCTURES_QUEUE_H
