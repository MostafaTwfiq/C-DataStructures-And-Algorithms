#include "../Headers/Stack.h"



/** Allocates space for the stack in the memory.
 * @param freeItem the freeing item function address, that will be called to free the stack items
 * @return Pointer to the stack stored on the heap.
 **/

Stack* stackInitialization(void (*freeItem)(void *item)) {

    Stack *s = ( Stack*  )malloc( sizeof( Stack ) );

    if( !s ) {
        fprintf( stderr , "Failed At allocating Stack" );
        exit( FAILED_ALLOCATION );
    }

    s->freeItem =  freeItem;
    s->allocated = 10;
    s->memory = (StackItem **) malloc( sizeof(StackItem *) * s->allocated);

    if( !s->memory ) {
        fprintf( stderr , "Failed At allocating memory for Stack" );
        exit( FAILED_ALLOCATION );
    }

    s->top = -1;

    return s;

}





/** Pushes data on top of the stack.
 * @param stack Pointer to the stack on the heap.
 * @param dataSize the size of the provided data
 * @param data pointer to data to be stored on top of the stack.
 **/

void pushStack( Stack* stack ,  void * data, int dataSize) {
    if( !stack || !data ) {
        fprintf( stderr , "Param Cannot be Null" );
        exit( NULL_POINTER );
    }

    if(stack->top == stack->allocated - 1 ) {
        stack->allocated *= 2;
        stack->memory =  (StackItem **) realloc( stack->memory  , sizeof(StackItem *) * stack->allocated );

        if ( !stack->memory ) {
            fprintf( stderr , "Failed at reallocating the Stack" );
            exit( FAILED_REALLOCATION );
        }
    }

    StackItem *newItem = (StackItem *) malloc(sizeof(StackItem));
    newItem->value = data;
    newItem->sizeOfItem = dataSize;
    stack->memory[++stack->top] = newItem;

}



/** This function will take an array of items, then it will push all the items into the stack.
 * @param stack the stack address
 * @param array the array of items address
 * @param arrLength the length of the items array
 * @param sizeOfItem the size of the array items in bytes
 */

void stackAddAll(Stack *stack, void **array, int arrLength, int sizeOfItem) {
    if (stack == NULL) {
        fprintf( stderr , "Param Cannot be Null" );
        exit( NULL_POINTER );
    }
    for (int i = 0; i < arrLength; i++) {
        pushStack(stack, array[i], sizeOfItem);
    }


}



/** This function will return a double void array that contains a copy of all the stack items.
 * @param stack the stack address
 * @return it will return a double void array consist of stack items
 */

void **stackToArray(Stack *stack) {
    if( !stack ) {
        fprintf( stderr , "Stack Param Cannot be Null" );
        exit( NULL_POINTER );
    }

    void **arr = (void **) malloc(sizeof(void *) * stack->top + 1);

    for (int i = 0; i <= stack->top; i++) {
        arr[i] = (void *) malloc(stack->memory[i]->sizeOfItem);
        memcpy(arr[i], stack->memory[i]->value, stack->memory[i]->sizeOfItem);
    }

    return arr;
}



/** Pops data off the stack and returns a pointer reference to it.
 *  @param stack  Pointer to the stack on the heap.
 *  @return Pointer to data that was stored on top of the stack.
 **/
 void *popStack( Stack* stack ) {
    if( !stack ) {
        fprintf( stderr , "Stack Param Cannot be Null" );
        exit( NULL_POINTER );
    }

    void *returnItem = stack->memory[stack->top]->value;
    free(stack->memory[stack->top--]);

    return returnItem;

}




/** Takes a reference to a stack and returns whether the stack is Empty or not.
 * @param stack  Pointer to the stack on the heap.
 * @return 1 if Empty else 0.
 **/

short isEmptyStack( Stack* stack ) {
    if( !stack ) {
        fprintf( stderr , "Stack Param Cannot be Null" );
        exit( NULL_POINTER );
    }

    return (short) (stack->top == -1 );

}




/** This function will return the number of items in the stack.
 * @param stack the stack address
 * @return it will return the number of items in the array
 */

int getStackLength(Stack *stack) {

    if( !stack ) {
        fprintf( stderr , "Stack Param Cannot be Null" );
        exit( NULL_POINTER );
    }

    return stack->top + 1;
}






/** Takes a reference to a stack and returns the top most stored item.
 * @param stack  Pointer to the stack on the heap.
 * @return Returns a pointer to the top stored item on top of the stack.
 **/

void* peekStack( Stack* stack ) {
    if( !stack ) {
        fprintf( stderr , "Stack Param Cannot be Null" );
        exit( NULL_POINTER );
    }
    if (isEmptyStack(stack)) {
        fprintf( stderr , "Stack is empty." );
        exit(EMPTY_DATASTRUCTURE );
    }

    return stack->memory[stack->top]->value;

}





/** Clear the Stack from it's stored values popping them continuously. Stack can be later top after clear.
 * @param stack Reference pointer to a Stack.
 **/
void StackClear( Stack* stack ) {
    if( !stack ) {
        fprintf( stderr , "Stack Param Cannot be Null" );
        exit( NULL_POINTER );
    }

    for (int i = 0; i < getStackLength(stack); i++) {
        stack->freeItem(stack->memory[i]->value);
        free(stack->memory[i]);
    }

}





/** Clears and Destroys the Stack. Stack cannot be top after being destroyed.
 * @param stack Reference pointer to a Stack.
 **/

void StackDestroy( Stack* stack ) {

    StackClear( stack );

    free( stack->memory );
    free( stack );

}