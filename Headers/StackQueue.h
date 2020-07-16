#ifndef C_DATASTRUCTURES_STACKQUEUE_H
#define C_DATASTRUCTURES_STACKQUEUE_H

#include "Stack.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef struct SQueue {
    Stack *fStack;
    Stack *sStack;
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

void destroySQueue(SQueue *queue);

#ifdef __cplusplus
}
#endif

#endif //C_DATASTRUCTURES_STACKQUEUE_H
