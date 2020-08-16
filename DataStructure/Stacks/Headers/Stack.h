#ifndef C_DATASTRUCTURES_STACK_H
#define C_DATASTRUCTURES_STACK_H

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
} Stack;

Stack *stackInitialization(void (*freeItem)(void *item));

void stackPush(Stack *stack, void *data);

void stackAddAll(Stack *stack, void **array, int arrLength);

void *stackPop(Stack *stack);

short stackIsEmpty(Stack *stack);

void *stackPeek(Stack *stack);

void **stackToArray(Stack *stack);

int stackGetLength(Stack *stack);

int stackContains(Stack *stack, void *item, int (*cmp)(const void *, const void *));

int stackEquals(Stack *stack, Stack *stack1, int (*cmp)(const void *, const void *));

void clearStack(Stack *stack);

void destroyStack(void *stack);

#ifdef __cplusplus
}
#endif

#endif //C_DATASTRUCTURES_STACK_H
