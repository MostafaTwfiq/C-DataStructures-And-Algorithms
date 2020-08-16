#ifndef C_DATASTRUCTURES_DLINKEDLISTSTACK_H
#define C_DATASTRUCTURES_DLINKEDLISTSTACK_H

#ifdef __cplusplus
extern "C" {
#endif


/** @struct DLinkedListStack
*  @brief This structure implements a basic generic DLinkedListStack.
*  @var DLinkedListStack:: linkedList
*  Member 'linkedList' is a pointer to the stack doubly linked list.
*/

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

int dlStackEquals(DLinkedListStack *fStack, DLinkedListStack *sStack, int (*cmp)(const void *, const void *));

int dlStackContains(DLinkedListStack *fStack, void *item, int (*cmp)(const void *, const void *));

void clearDLStack(DLinkedListStack *stack);

void destroyDLStack(void *stack);

#ifdef __cplusplus
}
#endif


#endif //C_DATASTRUCTURES_DLINKEDLISTSTACK_H
