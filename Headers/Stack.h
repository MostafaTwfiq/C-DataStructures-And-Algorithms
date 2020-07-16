#ifndef C_DATASTRUCTURES_STACK_H
#define C_DATASTRUCTURES_STACK_H
#include "Utils.h"

#ifdef __cplusplus
extern "C" {
#endif

/** @struct Stack
 *  @brief This structure implements a basic generic stack.
 *  @var Stack:: memory
 *  Member 'memory' is a pointer to the the stacks memory.
 *  @var Stack::allocated
 *  Member 'allocated' holds the current max allocated size for the stack.
 *  @var Stack::top
 *  Member 'top' holds the index to the top most stored item.
 *  @var Stack::sizeOfItem
 *  Member 'sizeOfItem' the size of the data stored in the stack.
 */


typedef struct StackItem {
    void *value;
    int sizeOfItem;
} StackItem;

typedef struct Stack {
    struct StackItem **memory;
    int allocated;
    int top;

    void (*freeItem)(void *item);
} Stack;

Stack *stackInitialization(void (*freeItem)(void *item));

void pushStack(Stack *stack, void *data, int dataSize);

void stackAddAll(Stack *stack, void **array, int arrLength, int sizeOfItem);

void *popStack(Stack *stack);

short isEmptyStack(Stack *stack);

void *peekStack(Stack *stack);

void **stackToArray(Stack *stack);

int getStackLength(Stack *stack);

void StackClear(Stack *stack);

void StackDestroy(Stack *stack);

#ifdef __cplusplus
}
#endif

#endif //C_DATASTRUCTURES_STACK_H
