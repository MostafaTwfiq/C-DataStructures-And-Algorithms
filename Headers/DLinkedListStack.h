#ifndef C_DATASTRUCTURES_DLINKEDLISTSTACK_H
#define C_DATASTRUCTURES_DLINKEDLISTSTACK_H
#include "Utils.h"

#ifdef __cplusplus
extern "C" {
#endif


typedef struct DLinkedListStack {
    struct DoublyLinkedList *linkedList;
} DLinkedListStack;


DLinkedListStack *dlStackInitialization(void (*freeFun)(void *item));

void dlStackPush(DLinkedListStack *stack, void *item);

void dlStackAddAll(DLinkedListStack *stack, void **arr, int arrLength);

void *dlStackPop(DLinkedListStack *stack);

int dlStackGetLength(DLinkedListStack *stack);

int dlStackIsEmpty(DLinkedListStack *stack);

void *dlStackPeek(DLinkedListStack *stack);

void **dlStackToArray(DLinkedListStack *stack);

void clearDLStack(DLinkedListStack *stack);

void destroyDLStack(DLinkedListStack *stack);

#ifdef __cplusplus
}
#endif


#endif //C_DATASTRUCTURES_DLINKEDLISTSTACK_H
