#ifndef C_DATASTRUCTURES_QUEUE_H
#define C_DATASTRUCTURES_QUEUE_H

#ifdef __cplusplus
extern "C" {
#endif


/** @struct Queue
 *  @brief This structure implements a basic generic Queue where memory is laid out sequentially.
 *  @var Queue:: memory
 *  Member 'memory' is a pointer to the the Queue's memory.
 *  @var Queue::allocated
 *  Member 'allocated' holds the current max allocated size for the Queue.
 *  @var Queue::front
 *  Member 'front' holds the index to the front of the Queue Element.
  *  @var Queue::rear
 *  Member 'rear' holds the index to the last Queue Element.
 *  @var Queue:: 'freeFn'
 *  Member 'freeFn' holds pointer to the function responsible for freeing the elements stored in the queue.
 */

typedef struct Queue {
    void **memory;
    int allocated;
    int front;
    int rear;

    void (*freeItem)(void *);
} Queue;

Queue *queueInitialization(void (*freeFun)(void *));

void queueEnqueue(Queue *arrayQueue, void *data);

void *queueDequeue(Queue *arrayQueue);

void destroyQueue(void *arrayQueue);

void clearQueue(Queue *arrayQueue);

int queueIsEmpty(Queue *arrayQueue);

int queueGetLength(Queue *arrayQueue);

void queueEnqueueAll(Queue *arrayQueue, void **arr, int arrLength);

void *queuePeek(Queue *arrayQueue);

void **queueToArray(Queue *arrayQueue);

#ifdef __cplusplus
}
#endif

#endif //C_DATASTRUCTURES_QUEUE_H
