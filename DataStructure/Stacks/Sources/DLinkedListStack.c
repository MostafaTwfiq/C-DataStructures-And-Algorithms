#include "../../LinkedLists/Headers/DoublyLinkedList.h"
#include "../Headers/DLinkedListStack.h"
#include "../../../System/Utils.h"
#include "../../../Unit Test/CuTest/CuTest.h"


/** This function will take the size of the items in the stack as a parameters,
 * then it will initialize the stack and return it's address.
 *
 * @param freeFun the free function address thar will be called to free the stack items
 * @return it will return the new stack address
 */

DLinkedListStack *dlStackInitialization(void (*freeFun)(void *)) {
    if (freeFun == NULL) {
#ifdef C_DATASTRUCTURES_ERRORSTESTSTRUCT_H
        ERROR_TEST->errorCode = INVALID_ARG;
        return NULL;
#else
        fprintf(stderr, INVALID_ARG_MESSAGE, "free function pointer", "doubly linked list stack data structure");
        exit(INVALID_ARG);
#endif

    }

    DLinkedListStack *stack = (DLinkedListStack *) malloc(sizeof(DLinkedListStack));
    if (stack == NULL) {
#ifdef C_DATASTRUCTURES_ERRORSTESTSTRUCT_H
        ERROR_TEST->errorCode = FAILED_ALLOCATION;
        return NULL;
#else
        fprintf(stderr, FAILED_ALLOCATION_MESSAGE, "stack", "doubly linked list stack data structure");
        exit(FAILED_ALLOCATION);
#endif

    }

    stack->linkedList = doublyLinkedListInitialization(freeFun, NULL);

    return stack;

}


/** This function will take the stack address, and the item address as a parameters,
 * then it will stackPush the item into the stack.
 *
 * @param stack the stack address
 * @param item the new item address
 */

void dlStackPush(DLinkedListStack *stack, void *item) {
    if (stack == NULL) {
#ifdef C_DATASTRUCTURES_ERRORSTESTSTRUCT_H
        ERROR_TEST->errorCode = NULL_POINTER;
        return;
#else
        fprintf(stderr, NULL_POINTER_MESSAGE, "stack", "doubly linked list stack data structure");
        exit(NULL_POINTER);
#endif

    } else if (item == NULL) {
#ifdef C_DATASTRUCTURES_ERRORSTESTSTRUCT_H
        ERROR_TEST->errorCode = INVALID_ARG;
        return;
#else
        fprintf(stderr, INVALID_ARG_MESSAGE, "item pointer", "doubly linked list stack data structure");
        exit(INVALID_ARG);
#endif

    }

    doublyLinkedListAddLast(stack->linkedList, item);

}


/** This function will take the stack address, the array address, and the array length as a parameters,
 * then it will add all the array items into the stack in order.
 *
 * @param stack the stack address
 * @param arr the new items array address
 * @param arrLength the length of the new items array
 */

void dlStackAddAll(DLinkedListStack *stack, void **arr, int arrLength) {
    if (stack == NULL) {
#ifdef C_DATASTRUCTURES_ERRORSTESTSTRUCT_H
        ERROR_TEST->errorCode = NULL_POINTER;
        return;
#else
        fprintf(stderr, NULL_POINTER_MESSAGE, "stack", "doubly linked list stack data structure");
        exit(NULL_POINTER);
#endif

    } else if (arr == NULL) {
#ifdef C_DATASTRUCTURES_ERRORSTESTSTRUCT_H
        ERROR_TEST->errorCode = INVALID_ARG;
        return;
#else
        fprintf(stderr, INVALID_ARG_MESSAGE, "item array pointer", "doubly linked list stack data structure");
        exit(INVALID_ARG);
#endif

    }


    for (int i = 0; i < arrLength; i++)
        dlStackPush(stack, arr[i]);

}


/** This function will take the stack address as a parameter,
 * then it will return the last item that pushed to the stack,
 * then the item will be removed from the stack.
 *
 * Note: if the stack i empty the program will be terminated.
 *
 * @param stack the stack address
 * @return it will return the (last in) item address in the stack
 */

void *dlStackPop(DLinkedListStack *stack) {

    if (stack == NULL) {
#ifdef C_DATASTRUCTURES_ERRORSTESTSTRUCT_H
        ERROR_TEST->errorCode = NULL_POINTER;
        return NULL;
#else
        fprintf(stderr, NULL_POINTER_MESSAGE, "stack", "doubly linked list stack data structure");
        exit(NULL_POINTER);
#endif

    } else if (dlStackIsEmpty(stack)) {
#ifdef C_DATASTRUCTURES_ERRORSTESTSTRUCT_H
        ERROR_TEST->errorCode = EMPTY_DATA_STRUCTURE;
        return NULL;
#else
        fprintf(stderr, EMPTY_DATA_STRUCTURE_MESSAGE, "doubly linked list stack data structure");
        exit(EMPTY_DATA_STRUCTURE);
#endif

    }

    void *item = doublyLinkedListGetLast(stack->linkedList);
    doublyLinkedListDeleteLastWtoFr(stack->linkedList);

    return item;
}


/** This function will take the stack address as a parameter,
 * then it will return a void array pointer that contains all the stack items.
 *
 * @param stack the stack address
 * @return it will return a double void array that contains a copy of all the items in the stack
 */

void **dlStackToArray(DLinkedListStack *stack) {

    if (stack == NULL) {
#ifdef C_DATASTRUCTURES_ERRORSTESTSTRUCT_H
        ERROR_TEST->errorCode = NULL_POINTER;
        return NULL;
#else
        fprintf(stderr, NULL_POINTER_MESSAGE, "stack", "doubly linked list stack data structure");
        exit(NULL_POINTER);
#endif

    }

    return doublyLinkedListToArray(stack->linkedList);

}


/** This function will take the stack address as a parameter,
 * then it will return the last item that pushed to the stack,
 * without removing the item from the stack.
 *
 * Note: if the stack i empty the program will be terminated.
 *
 * @param stack the stack address
 * @return it will return the (last in) item address in the stack
 */

void *dlStackPeek(DLinkedListStack *stack) {

    if (stack == NULL) {
#ifdef C_DATASTRUCTURES_ERRORSTESTSTRUCT_H
        ERROR_TEST->errorCode = NULL_POINTER;
        return NULL;
#else
        fprintf(stderr, NULL_POINTER_MESSAGE, "stack", "doubly linked list stack data structure");
        exit(NULL_POINTER);
#endif

    } else if (dlStackIsEmpty(stack)) {
#ifdef C_DATASTRUCTURES_ERRORSTESTSTRUCT_H
        ERROR_TEST->errorCode = EMPTY_DATA_STRUCTURE;
        return NULL;
#else
        fprintf(stderr, EMPTY_DATA_STRUCTURE_MESSAGE, "doubly linked list stack data structure");
        exit(EMPTY_DATA_STRUCTURE);
#endif

    }

    void *item = doublyLinkedListGetLast(stack->linkedList);

    return item;
}


/** This function will take the stack address as a parameter,
 * then it will return the number of the items in the stack.
 *
 * @param stack the stack address
 * @return it will return the number of items in the stack
 */

int dlStackGetLength(DLinkedListStack *stack) {

    if (stack == NULL) {
#ifdef C_DATASTRUCTURES_ERRORSTESTSTRUCT_H
        ERROR_TEST->errorCode = NULL_POINTER;
        return -1;
#else
        fprintf(stderr, NULL_POINTER_MESSAGE, "stack", "doubly linked list stack data structure");
        exit(NULL_POINTER);
#endif

    }

    return stack->linkedList->length;
}


/** This function will take the stack address as a parameter,
 * then it will return one (1) if the stack is empty,
 * other wise it will return zero (0).
 *
 * @param stack the stack address
 * @return it will return one if the stack is empty, other wise it will return zero
 */

int dlStackIsEmpty(DLinkedListStack *stack) {

    if (stack == NULL) {
#ifdef C_DATASTRUCTURES_ERRORSTESTSTRUCT_H
        ERROR_TEST->errorCode = NULL_POINTER;
        return -1;
#else
        fprintf(stderr, NULL_POINTER_MESSAGE, "stack", "doubly linked list stack data structure");
        exit(NULL_POINTER);
#endif

    }

    return doublyLinkedListIsEmpty(stack->linkedList);

}


/** This function will take two doubly linked list stack,
 * then it will check if the two stacks are equal or not,
 * and if they was the function will return one (1), other wise it will return zero (0).
 *
 * @param fStack the first stack pointer
 * @param sStack the second stack pointer
 * @param cmp the comparator function pointer, that will be called to compare the stacks items
 * @return it will return 1 if the two stack are the same, other wise it will return 0
 */

int dlStackEquals(DLinkedListStack *fStack, DLinkedListStack *sStack, int (*cmp)(const void *, const void *)) {

    if (fStack == NULL) {
#ifdef C_DATASTRUCTURES_ERRORSTESTSTRUCT_H
        ERROR_TEST->errorCode = NULL_POINTER;
        return -1;
#else
        fprintf(stderr, NULL_POINTER_MESSAGE, "first stack pointer", "doubly linked list stack data structure");
        exit(NULL_POINTER);
#endif

    } else if (sStack == NULL) {
#ifdef C_DATASTRUCTURES_ERRORSTESTSTRUCT_H
        ERROR_TEST->errorCode = INVALID_ARG;
        return -1;
#else
        fprintf(stderr, INVALID_ARG_MESSAGE, "second stack pointer", "doubly linked list stack data structure");
        exit(INVALID_ARG);
#endif

    } else if (cmp == NULL) {
#ifdef C_DATASTRUCTURES_ERRORSTESTSTRUCT_H
        ERROR_TEST->errorCode = INVALID_ARG;
        return -1;
#else
        fprintf(stderr, INVALID_ARG_MESSAGE, "comparator function pointer", "doubly linked list stack data structure");
        exit(INVALID_ARG);
#endif
    }

    if (doublyLinkedListGetLength(fStack->linkedList) != doublyLinkedListGetLength(sStack->linkedList))
        return 0;

    for (int i = 0; i < doublyLinkedListGetLength(fStack->linkedList); i++) {

        if (cmp(doublyLinkedListGet(fStack->linkedList, i), doublyLinkedListGet(sStack->linkedList, i)) != 0)
            return 0;

    }

    return 1;

}


/** This function will take a stack and an item,
 * then it will check if the item exists in the stack or not,
 * and if it was the function will return one (1), other wise it will return zero (0).
 *
 * @param fStack the stack pointer
 * @param item the item pointer
 * @param cmp the comparator function pointer, that will be called to compare the items
 * @return it will return 1 if the item exist in the stack, other wise it will return 0
 */

int dlStackContains(DLinkedListStack *fStack, void *item, int (*cmp)(const void *, const void *)) {

    if (fStack == NULL) {
#ifdef C_DATASTRUCTURES_ERRORSTESTSTRUCT_H
        ERROR_TEST->errorCode = NULL_POINTER;
        return -1;
#else
        fprintf(stderr, NULL_POINTER_MESSAGE, "first stack pointer", "doubly linked list stack data structure");
        exit(NULL_POINTER);
#endif

    } else if (item == NULL) {
#ifdef C_DATASTRUCTURES_ERRORSTESTSTRUCT_H
        ERROR_TEST->errorCode = INVALID_ARG;
        return -1;
#else
        fprintf(stderr, INVALID_ARG_MESSAGE, "item pointer", "doubly linked list stack data structure");
        exit(INVALID_ARG);
#endif

    } else if (cmp == NULL) {
#ifdef C_DATASTRUCTURES_ERRORSTESTSTRUCT_H
        ERROR_TEST->errorCode = INVALID_ARG;
        return -1;
#else
        fprintf(stderr, INVALID_ARG_MESSAGE, "comparator function pointer", "doubly linked list stack data structure");
        exit(INVALID_ARG);
#endif
    }

    for (int i = 0; i < doublyLinkedListGetLength(fStack->linkedList); i++) {

        if (cmp(item, doublyLinkedListGet(fStack->linkedList, i)) == 0)
            return 1;

    }

    return 0;

}


/** This function will take the stack address as a parameter,
 * then it will delete and free the stack from all it's items.
 *
 * @param stack the stack address
 */

void clearDLStack(DLinkedListStack *stack) {

    if (stack == NULL) {
#ifdef C_DATASTRUCTURES_ERRORSTESTSTRUCT_H
        ERROR_TEST->errorCode = NULL_POINTER;
        return;
#else
        fprintf(stderr, NULL_POINTER_MESSAGE, "stack", "doubly linked list stack data structure");
        exit(NULL_POINTER);
#endif

    }

    doublyLinkedListClear(stack->linkedList);

}


/** This function will take the stack address as a parameter,
 * then it will destroy and free the stack and all it's items.
 *
 * @param stack the stack address
 */

void destroyDLStack(void *stack) {
    if (stack == NULL) {
#ifdef C_DATASTRUCTURES_ERRORSTESTSTRUCT_H
        ERROR_TEST->errorCode = NULL_POINTER;
        return;
#else
        fprintf(stderr, NULL_POINTER_MESSAGE, "stack", "doubly linked list stack data structure");
        exit(NULL_POINTER);
#endif

    }

    destroyDoublyLinkedList(((DLinkedListStack *) stack)->linkedList);
    free(stack);

}


