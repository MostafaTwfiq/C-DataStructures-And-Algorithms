#include "../Headers/Stack.h"

/// Allocates space for the stack on the heap.
/// \param size Size of the daata to be stored on to the stack.
/// \return Pointer to the stack dtored on the heap.
Stack* StackInitalization(int size) {

    if(!size) {
        fprintf(stderr,"Size Param Cannot be Zero(0)");
        exit(INVALID_ARG);
    }

    Stack *s = (Stack* )malloc(sizeof(Stack));

    if(!s) {
        fprintf(stderr,"Failed At allocating Stack");
        exit(FAILED_ALLOCATION);
    }

    s->sizeOfTypeOf= size;
    s->allocated = 10;
    s->memory = malloc(size*s->allocated);

    if(!s->memory) {
        fprintf(stderr,"Failed At allocating memory for Stack");
        exit(FAILED_ALLOCATION);
    }
    s->used = -1;
    return s;
}

/// Pushes data on top of the stack.
/// \param stack Pointer to the stack on the heap.
/// \param data pointer to data to be stored on top of the stack.
void pushStack(Stack* stack, void * data){
    if(!stack || !data){
        fprintf(stderr,"Param Cannot be Null");
        exit(NULL_POINTER);
    }

    if(stack->used == stack->allocated-1) {
        stack->allocated*=2;
        stack->memory =  realloc(stack->memory,stack->sizeOfTypeOf*stack->allocated);

        if (!stack->memory) {
            fprintf(stderr,"Failed at reallocating the Stack");
            exit(FAILED_REALLOCATION);
        }
    }

    stack->used++;
    memcpy((stack->memory + stack->used*stack->sizeOfTypeOf),data,stack->sizeOfTypeOf);

    if(memcmp(stack->memory + stack->used*stack->sizeOfTypeOf,data,stack->sizeOfTypeOf)) {
        fprintf(stderr,"Failed at Copying data");
        exit(FAILED_COPY);
    }

}

/// Pops data off the stack and returns a pointer refrence to it.
/// \param stack  Pointer to the stack on the heap.
/// \return Pointer to data that was stored on top of the stack.
void* popStack(Stack* stack){
    if(!stack){
        fprintf(stderr,"Stack Param Cannot be Null");
        exit(NULL_POINTER);
    }
    stack->used--;
    return stack->memory+(stack->used+1)*stack->sizeOfTypeOf;
}

/// Takes a reference to a stack and returns whether the stack is Empty or not.
/// \param stack  Pointer to the stack on the heap.
/// \return 1 if Empty else 0.
short isEmptyStack(Stack* stack) {
    if(!stack){
        fprintf(stderr,"Stack Param Cannot be Null");
        exit(NULL_POINTER);
    }
    return (stack->used == -1);
}

/// Takes a reference to a stack and returns the top most stored value.
/// \param stack  Pointer to the stack on the heap.
/// \return Returns a pointer to the top stored value on top of the stack.
void* peekStack(Stack* stack) {
    if(!stack){
        fprintf(stderr,"Stack Param Cannot be Null");
        exit(NULL_POINTER);
    }
    return (stack->used == -1) ?NULL: stack->memory+stack->used*stack->sizeOfTypeOf;
}

/// Clear the Stack from it's stored values popping them continuously. Stack can be later used after clear.
/// \param stack Reference pointer to a Stack.
void StackClear(Stack* stack){
    if(!stack){
        fprintf(stderr,"Stack Param Cannot be Null");
        exit(NULL_POINTER);
    }
    while(!isEmptyStack(stack)){
        void * res = popStack(stack);
        res = NULL;
    }
};

/// Clears and Destroys the Stack. StacK cannot be used after being destroyed.
/// \param stack Reference pointer to a Stack.
void StackDestroy(Stack* stack) {
    if(!stack){
        fprintf(stderr,"Stack Param Cannot be Null");
        exit(NULL_POINTER);
    }
    StackClear(stack);
    free(stack->memory);
    stack->memory=NULL;
    free(stack);
    stack=NULL;
};