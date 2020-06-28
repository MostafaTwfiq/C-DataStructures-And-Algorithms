#include "../Headers/Stack.h"


/* Allocates space for the stack on the heap.
 * @param size Size of the data to be stored on to the stack.
 * @return Pointer to the stack stored on the heap.
 **/
Stack* stackInitialization(int size ) {

    if( !size ) {
        fprintf( stderr , "Size Param Cannot be Zero( 0 )" );
        exit( INVALID_ARG );
    }

    Stack *s = ( Stack*  )malloc( sizeof( Stack ) );

    if( !s ) {
        fprintf( stderr , "Failed At allocating Stack" );
        exit( FAILED_ALLOCATION );
    }

    s->sizeOfType =  size;
    s->allocated = 10;
    s->memory = (void **) malloc( sizeof(void *) * s->allocated);

    if( !s->memory ) {
        fprintf( stderr , "Failed At allocating memory for Stack" );
        exit( FAILED_ALLOCATION );
    }
    s->top = -1;
    return s;
}

/* Pushes data on top of the stack.
 * @param stack Pointer to the stack on the heap.
 * @param data pointer to data to be stored on top of the stack.
 **/
void pushStack( Stack* stack ,  void * data ) {
    if( !stack || !data ) {
        fprintf( stderr , "Param Cannot be Null" );
        exit( NULL_POINTER );
    }

    if(stack->top == stack->allocated - 1 ) {
        stack->allocated *= 2;
        stack->memory =  (void **) realloc( stack->memory  , sizeof(void *) * stack->allocated );

        if ( !stack->memory ) {
            fprintf( stderr , "Failed at reallocating the Stack" );
            exit( FAILED_REALLOCATION );
        }
    }

    stack->top++;
    stack->memory[stack->top] = data;

}

void stackAddAll(Stack *stack, void *arr, int arrLength) {
    if (stack == NULL) {
        fprintf( stderr , "Param Cannot be Null" );
        exit( NULL_POINTER );
    }

    void *item;
    for (int i = 0; i < arrLength; i++) {
        item = (void *) malloc(stack->sizeOfType);
        memcpy(item, arr + stack->sizeOfType * i, stack->sizeOfType);
        pushStack(stack, item);
    }


}

void *stackToArray(Stack *stack) {
    if( !stack ) {
        fprintf( stderr , "Stack Param Cannot be Null" );
        exit( NULL_POINTER );
    }

    void *arr = (void *) malloc(stack->sizeOfType * stack->top + 1);

    for (int i = 0; i < stack->top + 1; i++)
        memcpy(arr + stack->sizeOfType * i, stack->memory[i], stack->sizeOfType);

    return arr;
}

/* Pops data off the stack and returns a pointer refrence to it.
 *  @param stack  Pointer to the stack on the heap.
 *  @return Pointer to data that was stored on top of the stack.
 **/
 void* popStack( Stack* stack ) {
    if( !stack ) {
        fprintf( stderr , "Stack Param Cannot be Null" );
        exit( NULL_POINTER );
    }

    return stack->memory[stack->top--];
}

/* Takes a reference to a stack and returns whether the stack is Empty or not.
 * @param stack  Pointer to the stack on the heap.
 * @return 1 if Empty else 0.
 **/
short isEmptyStack( Stack* stack ) {
    if( !stack ) {
        fprintf( stderr , "Stack Param Cannot be Null" );
        exit( NULL_POINTER );
    }
    return (stack->top == -1 );
}

int getStackLength(Stack *stack) {

    if( !stack ) {
        fprintf( stderr , "Stack Param Cannot be Null" );
        exit( NULL_POINTER );
    }

    return stack->top + 1;
}

/* Takes a reference to a stack and returns the top most stored value.
 * @param stack  Pointer to the stack on the heap.
 * @return Returns a pointer to the top stored value on top of the stack.
 **/
void* peekStack( Stack* stack ) {
    if( !stack ) {
        fprintf( stderr , "Stack Param Cannot be Null" );
        exit( NULL_POINTER );
    }
    if (isEmptyStack(stack)) {
        fprintf( stderr , "Stack is empty." );
        exit( EMPTY_STACK );
    }

    return stack->memory[stack->top];
}

/* Clear the Stack from it's stored values popping them continuously. Stack can be later top after clear.
 * @param stack Reference pointer to a Stack.
 **/
void StackClear( Stack* stack ) {
    if( !stack ) {
        fprintf( stderr , "Stack Param Cannot be Null" );
        exit( NULL_POINTER );
    }

    while( !isEmptyStack( stack ) )
        popStack( stack );

}

/* Clears and Destroys the Stack. Stack cannot be top after being destroyed.
 * @param stack Reference pointer to a Stack.
 **/
void StackDestroy( Stack* stack ) {
    if( !stack ) {
        fprintf( stderr , "Stack Param Cannot be Null" );
        exit( NULL_POINTER );
    }

    StackClear( stack );
    free( stack->memory );
    stack->memory = NULL;
    free( stack );
}