#ifndef C_DATASTRUCTURES_STACKQUEUE_H
#define C_DATASTRUCTURES_STACKQUEUE_H

#ifdef __cplusplus
extern "C" {
#endif


/** @struct SQueue
*  @brief This structure implements a basic generic Queue using two stacks.
*  @var SQueue:: fStack
*  Member 'fStack' is a pointer to the first stack.
*  @var SQueue::sStack
*  Member 'sStack' is a pointer to the second stack.
*/

typedef struct SQueue {
    struct Stack *fStack;
    struct Stack *sStack;
} SQueue;

SQueue *stackQueueInitialization(void (*freeItem)(void *item));

void sQueueEnqueue(SQueue *queue, void *item);

void sQueueAddAll(SQueue *queue, void **items, int itemsLength);

void *sQueueDequeue(SQueue *queue);

void *sQueuePeek(SQueue *queue);

int sQueueGetLength(SQueue *queue);

int sQueueIsEmpty(SQueue *queue);

void **sQueueToArray(SQueue *queue);

void clearSQueue(SQueue *queue);

void destroySQueue(void *queue);

#ifdef __cplusplus
}
#endif

#endif //C_DATASTRUCTURES_STACKQUEUE_H
