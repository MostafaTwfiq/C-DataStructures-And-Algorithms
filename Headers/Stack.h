#ifndef C_DATASTRUCTURES_STACK_H
#define C_DATASTRUCTURES_STACK_H
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/** @struct Stack
 *  @brief This structure blah blah blah...
 *  @var Stack:: memory
 *  Member 'memory' is a pointer to the the stacks memory.
 *  @var Stack::allocated
 *  Member 'allocated' holds the current max allocated size for the stack.
 *  @var Stack::top
 *  Member 'top' holds the index to the top most stored value.
 *  @var Stack::sizeOfType
 *  Member 'sizeOfType' the size of the data stored in the stack.
 */
typedef struct Stack {
    void **memory;
    int allocated;
    int top;
    int sizeOfType;
}Stack;

Stack* StackInitalization(int size);

void pushStack(Stack *stack, void *data);

void stackAddAll(Stack *stack, void *arr, int arrLength);

void *popStack(Stack *stack);

short isEmptyStack(Stack *stack);

void *peekStack(Stack *stack);

void *stackToArray(Stack *stack);

int getStackLength(Stack *stack);

void StackClear(Stack* stack);

void StackDestroy(Stack* stack);

#endif //C_DATASTRUCTURES_STACK_H
