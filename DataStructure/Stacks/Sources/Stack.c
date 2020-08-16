#include "../Headers/Stack.h"
#include "../../../System/Utils.h"
#include "../../../Unit Test/CuTest/CuTest.h"


/** Allocates space for the stack in the memory.
 *
 * @param freeItem the freeing item function address, that will be called to free the stack items
 * @return Pointer to the stack stored on the heap.
 **/

Stack *stackInitialization(void (*freeItem)(void *)) {

    if (freeItem == NULL) {
#ifdef C_DATASTRUCTURES_ERRORSTESTSTRUCT_H
        ERROR_TEST->errorCode = INVALID_ARG;
        return NULL;
#else
        fprintf(stderr, INVALID_ARG_MESSAGE, "free function pointer", "stack data structure");
        exit(INVALID_ARG);
#endif

    }

    Stack *s = (Stack *) malloc(sizeof(Stack));
    if (s == NULL) {
#ifdef C_DATASTRUCTURES_ERRORSTESTSTRUCT_H
        ERROR_TEST->errorCode = FAILED_ALLOCATION;
        return NULL;
#else
        fprintf(stderr, FAILED_ALLOCATION_MESSAGE, "stack", "stack data structure");
        exit(FAILED_ALLOCATION);
#endif

    }

    s->freeItem = freeItem;
    s->allocated = 10;
    s->memory = (void **) malloc(sizeof(void *) * s->allocated);

    if (s->memory == NULL) {
#ifdef C_DATASTRUCTURES_ERRORSTESTSTRUCT_H
        ERROR_TEST->errorCode = FAILED_ALLOCATION;
        return NULL;
#else
        fprintf(stderr, FAILED_ALLOCATION_MESSAGE, "stack array", "stack data structure");
        exit(FAILED_ALLOCATION);
#endif

    }

    s->top = -1;

    return s;

}


/** Pushes data on top of the stack.
 *
 * @param stack Pointer to the stack on the heap.
 * @param dataSize the size of the provided data
 **/

void stackPush(Stack *stack, void *data) {
    if (stack == NULL) {
#ifdef C_DATASTRUCTURES_ERRORSTESTSTRUCT_H
        ERROR_TEST->errorCode = NULL_POINTER;
        return;
#else
        fprintf(stderr, NULL_POINTER_MESSAGE, "stack", "stack data structure");
        exit(NULL_POINTER);
#endif

    } else if (data == NULL) {
#ifdef C_DATASTRUCTURES_ERRORSTESTSTRUCT_H
        ERROR_TEST->errorCode = INVALID_ARG;
        return;
#else
        fprintf(stderr, INVALID_ARG_MESSAGE, "item pointer", "stack data structure");
        exit(INVALID_ARG);
#endif

    }

    if (stack->top == stack->allocated - 1) {
        stack->allocated *= 2;
        stack->memory = (void **) realloc(stack->memory, sizeof(void *) * stack->allocated);
        if (stack->memory == NULL) {

#ifdef C_DATASTRUCTURES_ERRORSTESTSTRUCT_H
            ERROR_TEST->errorCode = FAILED_REALLOCATION;
            return;
#else
            fprintf(stderr, FAILED_REALLOCATION_MESSAGE, "stack array", "stack data structure");
            exit(FAILED_REALLOCATION);
#endif

        }

    }

    stack->memory[++stack->top] = data;

}


/** This function will take an array of items, then it will push all the items into the stack.
 *
 * @param stack the stack address
 * @param array the array of items address
 * @param arrLength the length of the items array
 */

void stackAddAll(Stack *stack, void **array, int arrLength) {
    if (stack == NULL) {
#ifdef C_DATASTRUCTURES_ERRORSTESTSTRUCT_H
        ERROR_TEST->errorCode = NULL_POINTER;
        return;
#else
        fprintf(stderr, NULL_POINTER_MESSAGE, "stack", "stack data structure");
        exit(NULL_POINTER);
#endif

    } else if (array == NULL) {
#ifdef C_DATASTRUCTURES_ERRORSTESTSTRUCT_H
        ERROR_TEST->errorCode = INVALID_ARG;
        return;
#else
        fprintf(stderr, INVALID_ARG_MESSAGE, "items array pointer", "stack data structure");
        exit(INVALID_ARG);
#endif

    }

    for (int i = 0; i < arrLength; i++)
        stackPush(stack, array[i]);


}


/** This function will return a double void array that contains a copy of all the stack items.
 *
 * @param stack the stack address
 * @return it will return a double void array consist of stack items
 */

void **stackToArray(Stack *stack) {
    if (stack == NULL) {
#ifdef C_DATASTRUCTURES_ERRORSTESTSTRUCT_H
        ERROR_TEST->errorCode = NULL_POINTER;
        return NULL;
#else
        fprintf(stderr, NULL_POINTER_MESSAGE, "stack", "stack data structure");
        exit(NULL_POINTER);
#endif

    }

    void **arr = (void **) malloc(sizeof(void *) * (stack->top + 1));
    if (arr == NULL) {
#ifdef C_DATASTRUCTURES_ERRORSTESTSTRUCT_H
        ERROR_TEST->errorCode = FAILED_ALLOCATION;
        return NULL;
#else
        fprintf(stderr, FAILED_ALLOCATION_MESSAGE, "to array", "stack data structure");
        exit(FAILED_ALLOCATION);
#endif

    }

    for (int i = 0; i <= stack->top; i++)
        arr[i] = stack->memory[i];

    return arr;
}


/** Pops data off the stack and returns a pointer reference to it.
 *
 *  @param stack  Pointer to the stack on the heap.
 *  @return Pointer to data that was stored on top of the stack.
 **/
void *stackPop(Stack *stack) {
    if (stack == NULL) {
#ifdef C_DATASTRUCTURES_ERRORSTESTSTRUCT_H
        ERROR_TEST->errorCode = NULL_POINTER;
        return NULL;
#else
        fprintf(stderr, NULL_POINTER_MESSAGE, "stack", "stack data structure");
        exit(NULL_POINTER);
#endif

    } else if (stackIsEmpty(stack)) {
#ifdef C_DATASTRUCTURES_ERRORSTESTSTRUCT_H
        ERROR_TEST->errorCode = EMPTY_DATA_STRUCTURE;
        return NULL;
#else
        fprintf(stderr, EMPTY_DATA_STRUCTURE_MESSAGE, "stack data structure");
        exit(EMPTY_DATA_STRUCTURE);
#endif

    }

    return stack->memory[stack->top--];

}


/** Takes a reference to a stack and returns whether the stack is Empty or not.
 *
 * @param stack  Pointer to the stack on the heap.
 * @return 1 if Empty else 0.
 **/

short stackIsEmpty(Stack *stack) {
    if (stack == NULL) {
#ifdef C_DATASTRUCTURES_ERRORSTESTSTRUCT_H
        ERROR_TEST->errorCode = NULL_POINTER;
        return -1;
#else
        fprintf(stderr, NULL_POINTER_MESSAGE, "stack", "stack data structure");
        exit(NULL_POINTER);
#endif

    }

    return (short) (stack->top == -1);

}


/** This function will return the number of items in the stack.
 *
 * @param stack the stack address
 * @return it will return the number of items in the array
 */

int stackGetLength(Stack *stack) {

    if (stack == NULL) {
#ifdef C_DATASTRUCTURES_ERRORSTESTSTRUCT_H
        ERROR_TEST->errorCode = NULL_POINTER;
        return -1;
#else
        fprintf(stderr, NULL_POINTER_MESSAGE, "stack", "stack data structure");
        exit(NULL_POINTER);
#endif

    }

    return stack->top + 1;
}


/** Takes a reference to a stack and returns the top most stored item.
 *
 * @param stack  Pointer to the stack on the heap.
 * @return Returns a pointer to the top stored item on top of the stack.
 **/

void *stackPeek(Stack *stack) {
    if (stack == NULL) {
#ifdef C_DATASTRUCTURES_ERRORSTESTSTRUCT_H
        ERROR_TEST->errorCode = NULL_POINTER;
        return NULL;
#else
        fprintf(stderr, NULL_POINTER_MESSAGE, "stack", "stack data structure");
        exit(NULL_POINTER);
#endif

    } else if (stackIsEmpty(stack)) {
#ifdef C_DATASTRUCTURES_ERRORSTESTSTRUCT_H
        ERROR_TEST->errorCode = EMPTY_DATA_STRUCTURE;
        return NULL;
#else
        fprintf(stderr, EMPTY_DATA_STRUCTURE_MESSAGE, "stack data structure");
        exit(EMPTY_DATA_STRUCTURE);
#endif

    }

    return stack->memory[stack->top];

}


/** This function will take two stacks,
 * then it will return one (1) if the two stacks are equal,
 * other wise it will return zero (0).
 *
 * @param stack the first stack pointer
 * @param stack1 the second stack pointer
 * @param cmp the comparator function, that will be called to compare the stacks items
 * @return it will return 1 if the two stack are equal, other wise it will return 0
 */

int stackEquals(Stack *stack, Stack *stack1, int (*cmp)(const void *, const void *)) {

    if (stack == NULL) {
#ifdef C_DATASTRUCTURES_ERRORSTESTSTRUCT_H
        ERROR_TEST->errorCode = NULL_POINTER;
        return -1;
#else
        fprintf(stderr, NULL_POINTER_MESSAGE, "stack", "stack data structure");
        exit(NULL_POINTER);
#endif

    } else if (stack1 == NULL) {
#ifdef C_DATASTRUCTURES_ERRORSTESTSTRUCT_H
        ERROR_TEST->errorCode = INVALID_ARG;
        return -1;
#else
        fprintf(stderr, INVALID_ARG_MESSAGE, "second stack pointer", "stack data structure");
        exit(INVALID_ARG);
#endif

    } else if (cmp == NULL) {
#ifdef C_DATASTRUCTURES_ERRORSTESTSTRUCT_H
        ERROR_TEST->errorCode = INVALID_ARG;
        return -1;
#else
        fprintf(stderr, INVALID_ARG_MESSAGE, "comparator function pointer", "stack data structure");
        exit(INVALID_ARG);
#endif
    }

    if (stack->top != stack1->top)
        return 0;

    else {

        for (int i = 0; i <= stack->top; i++) {
            if (cmp(stack->memory[i], stack1->memory[i]) != 0)
                return 0;
        }

        return 1;
    }
}


/** This function will take a stack and an item,
 * then it will check if the item exist in the stack or not,
 * and if it was the function will return one (1),
 * other wise it will return (0).
 *
 * @param stack the stack pointer
 * @param item the item pointer
 * @param cmp the comparator function, that will be called to compare the stacks items
 * @return it will return 1 if the item exist in the stack, other wise it will return 0
 */

int stackContains(Stack *stack, void *item, int (*cmp)(const void *, const void *)) {

    if (stack == NULL) {
#ifdef C_DATASTRUCTURES_ERRORSTESTSTRUCT_H
        ERROR_TEST->errorCode = NULL_POINTER;
        return -1;
#else
        fprintf(stderr, NULL_POINTER_MESSAGE, "stack", "stack data structure");
        exit(NULL_POINTER);
#endif

    } else if (item == NULL) {
#ifdef C_DATASTRUCTURES_ERRORSTESTSTRUCT_H
        ERROR_TEST->errorCode = INVALID_ARG;
        return -1;
#else
        fprintf(stderr, INVALID_ARG_MESSAGE, "item pointer", "stack data structure");
        exit(INVALID_ARG);
#endif

    } else if (cmp == NULL) {
#ifdef C_DATASTRUCTURES_ERRORSTESTSTRUCT_H
        ERROR_TEST->errorCode = INVALID_ARG;
        return -1;
#else
        fprintf(stderr, INVALID_ARG_MESSAGE, "comparator function pointer", "stack data structure");
        exit(INVALID_ARG);
#endif
    }

    for (int i = 0; i <= stack->top; i++) {

        if (cmp(stack->memory[i], item) == 0)
            return 1;

    }

    return 0;

}


/** Clear the Stack from it's stored values popping them continuously. Stack can be later top after clear.
 *
 * @param stack Reference pointer to a Stack.
 **/

void clearStack(Stack *stack) {
    if (stack == NULL) {
#ifdef C_DATASTRUCTURES_ERRORSTESTSTRUCT_H
        ERROR_TEST->errorCode = NULL_POINTER;
        return;
#else
        fprintf(stderr, NULL_POINTER_MESSAGE, "stack", "stack data structure");
        exit(NULL_POINTER);
#endif

    }

    for (int i = 0; i < stackGetLength(stack); i++)
        stack->freeItem(stack->memory[i]);

    stack->top = -1;

}


/** Clears and Destroys the Stack. Stack cannot be top after being destroyed.
 *
 * @param stack Reference pointer to a Stack.
 **/

void destroyStack(void *stack) {

    if (stack == NULL) {
#ifdef C_DATASTRUCTURES_ERRORSTESTSTRUCT_H
        ERROR_TEST->errorCode = NULL_POINTER;
        return;
#else
        fprintf(stderr, NULL_POINTER_MESSAGE, "stack", "stack data structure");
        exit(NULL_POINTER);
#endif

    }

    clearStack(stack);

    free(((Stack *) stack)->memory);
    free(stack);

}