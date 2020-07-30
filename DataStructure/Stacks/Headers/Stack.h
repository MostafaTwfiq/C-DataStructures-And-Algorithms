#ifndef C_DATASTRUCTURES_STACK_H
#define C_DATASTRUCTURES_STACK_H

#include <stdint.h>

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
 *  @var Stack::freeItem
 *  Member 'freeItem' the freeing item function pointer
 */

typedef struct Stack {
    void **memory;
    int allocated;
    int top;
    void (*freeItem)(void *);
}Stack;

Stack *stackInitialization(void (*freeItem)(void *item));

void pushStack( Stack* stack, void * data);

void stackAddAll(Stack *stack, void **array, int arrLength);

void *popStack(Stack *stack);

short isEmptyStack(Stack *stack);

void *peekStack(Stack *stack);

void **stackToArray(Stack *stack);

int getStackLength(Stack *stack);

void StackClear(Stack *stack);

void StackDestroy(Stack *stack);

uint32_t StackContains(Stack *stack, void *item,int (*cmp)(void *,void*));

uint32_t stackIsEqual(Stack * stack, Stack * stack1, int (*cmp)(void *,void*));

#ifdef __cplusplus
}
#endif

#endif //C_DATASTRUCTURES_STACK_H
