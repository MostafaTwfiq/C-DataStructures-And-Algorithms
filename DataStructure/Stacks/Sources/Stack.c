#include "../Headers/Stack.h"
#include "../../../System/Utils.h"


/** Allocates space for the stack in the memory.
 * @param freeItem the freeing item function address, that will be called to free the stack items
 * @return Pointer to the stack stored on the heap.
 **/

Stack* stackInitialization(void (*freeItem)(void *)) {

    if (freeItem == NULL) {
        fprintf(stderr, INVALID_ARG_MESSAGE, "free function pointer", "stack data structure");
        exit(INVALID_ARG);
    }

    Stack *s = ( Stack*  )malloc( sizeof( Stack ) );
    if (s == NULL) {
        fprintf(stderr, FAILED_ALLOCATION_MESSAGE, "stack", "stack data structure");
        exit(FAILED_ALLOCATION);
    }

    s->freeItem =  freeItem;
    s->allocated = 10;
    s->memory = (void **) malloc( sizeof(void *) * s->allocated);

    if(s->memory == NULL) {
        fprintf(stderr, FAILED_ALLOCATION_MESSAGE, "stack array", "stack data structure" );
        exit(FAILED_ALLOCATION);
    }

    s->top = -1;

    return s;

}





/** Pushes data on top of the stack.
 * @param stack Pointer to the stack on the heap.
 * @param dataSize the size of the provided data
 **/

void pushStack( Stack* stack ,  void * data) {
    if (stack == NULL) {
        fprintf(stderr, NULL_POINTER_MESSAGE, "stack", "stack data structure");
        exit(NULL_POINTER);
    } else if (data == NULL) {
        fprintf(stderr, INVALID_ARG_MESSAGE, "item pointer", "stack data structure");
        exit(INVALID_ARG);
    }

    if(stack->top == stack->allocated - 1 ) {
        stack->allocated *= 2;
        stack->memory =  (void **) realloc( stack->memory  , sizeof(void *) * stack->allocated );
        if (stack->memory == NULL) {
            fprintf(stderr, FAILED_REALLOCATION_MESSAGE, "stack array", "stack data structure");
            exit(FAILED_REALLOCATION);
        }

    }

    stack->memory[++stack->top] = data;

}



/** This function will take an array of items, then it will push all the items into the stack.
 * @param stack the stack address
 * @param array the array of items address
 * @param arrLength the length of the items array
 */

void stackAddAll(Stack *stack, void **array, int arrLength) {
    if (stack == NULL) {
        fprintf(stderr, NULL_POINTER_MESSAGE, "stack", "stack data structure");
        exit(NULL_POINTER);
    } else if (array == NULL) {
        fprintf(stderr, INVALID_ARG_MESSAGE, "items array pointer", "stack data structure");
        exit(INVALID_ARG);
    }

    for (int i = 0; i < arrLength; i++)
        pushStack(stack, array[i]);


}



/** This function will return a double void array that contains a copy of all the stack items.
 * @param stack the stack address
 * @return it will return a double void array consist of stack items
 */

void **stackToArray(Stack *stack) {
    if (stack == NULL) {
        fprintf(stderr, NULL_POINTER_MESSAGE, "stack", "stack data structure");
        exit(NULL_POINTER);
    }

    void **arr = (void **) malloc(sizeof(void *) * stack->top + 1);
    if (arr == NULL) {
        fprintf(stderr, FAILED_ALLOCATION_MESSAGE, "to array", "stack data structure");
        exit(FAILED_ALLOCATION);
    }

    for (int i = 0; i <= stack->top; i++)
        arr[i] = stack->memory[i];

    return arr;
}



/** Pops data off the stack and returns a pointer reference to it.
 *  @param stack  Pointer to the stack on the heap.
 *  @return Pointer to data that was stored on top of the stack.
 **/
 void *popStack( Stack* stack ) {
    if (stack == NULL) {
        fprintf(stderr, NULL_POINTER_MESSAGE, "stack", "stack data structure");
        exit(NULL_POINTER);
    } else if (isEmptyStack(stack)) {
        fprintf(stderr, EMPTY_DATA_STRUCTURE_MESSAGE, "stack data structure");
        exit(EMPTY_DATA_STRUCTURE);
    }

    return stack->memory[stack->top--];

}




/** Takes a reference to a stack and returns whether the stack is Empty or not.
 * @param stack  Pointer to the stack on the heap.
 * @return 1 if Empty else 0.
 **/

short isEmptyStack( Stack* stack ) {
    if (stack == NULL) {
        fprintf(stderr, NULL_POINTER_MESSAGE, "stack", "stack data structure");
        exit(NULL_POINTER);
    }

    return (short) (stack->top == -1 );

}




/** This function will return the number of items in the stack.
 * @param stack the stack address
 * @return it will return the number of items in the array
 */

int getStackLength(Stack *stack) {

    if (stack == NULL) {
        fprintf(stderr, NULL_POINTER_MESSAGE, "stack", "stack data structure");
        exit(NULL_POINTER);
    }

    return stack->top + 1;
}






/** Takes a reference to a stack and returns the top most stored item.
 * @param stack  Pointer to the stack on the heap.
 * @return Returns a pointer to the top stored item on top of the stack.
 **/

void* peekStack( Stack* stack ) {
    if (stack == NULL) {
        fprintf(stderr, NULL_POINTER_MESSAGE, "stack", "stack data structure");
        exit(NULL_POINTER);
    } else if (isEmptyStack(stack)) {
        fprintf(stderr, EMPTY_DATA_STRUCTURE_MESSAGE, "stack data structure");
        exit(EMPTY_DATA_STRUCTURE);
    }

    return stack->memory[stack->top];

}





/** Clear the Stack from it's stored values popping them continuously. Stack can be later top after clear.
 * @param stack Reference pointer to a Stack.
 **/
void StackClear( Stack* stack ) {
    if (stack == NULL) {
        fprintf(stderr, NULL_POINTER_MESSAGE, "stack", "stack data structure");
        exit(NULL_POINTER);
    }

    for (int i = 0; i < getStackLength(stack); i++)
        stack->freeItem(stack->memory[i]);

}





/** Clears and Destroys the Stack. Stack cannot be top after being destroyed.
 * @param stack Reference pointer to a Stack.
 **/

void StackDestroy( Stack* stack ) {

    StackClear( stack );

    free( stack->memory );
    free( stack );

}