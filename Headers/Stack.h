#ifndef C_DATASTRUCTURES_STACK_H
#define C_DATASTRUCTURES_STACK_H
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef enum ERROR {
    FAILED_ALLOCATION     = -1,
    FAILED_REALLOCATION   = -2,
    FAILED_COPY           = -3,
    INVALID_ARG           = -4,
    NULL_POINTER          = -5
}ERROR;

typedef struct Stack {
    void* memory;
    int allocated;
    int used;
    int sizeOfTypeOf;
}Stack;

Stack* StackInitalization(int size);

void pushStack(Stack *stack, void *data);

void *popStack(Stack *stack);

short isEmptyStack(Stack *stack);

void *peekStack(Stack *stack);

void StackClear(Stack* stack);

void StackDestroy(Stack* stack);

#endif //C_DATASTRUCTURES_STACK_H
