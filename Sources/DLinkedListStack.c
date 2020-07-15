#include "../Headers/DLinkedListStack.h"
#include "../Headers/DoublyLinkedList.h"



/** This function will take the size of the items in the stack as a parameters,
    then it will initialize the stack and return it's address.
 * @param freeFun the free function address thar will be called to free the stack items
 * @return it will return the new stack address
 */

DLinkedListStack *dlStackInitialization(void (*freeFun)(void *)) {

    DLinkedListStack *stack = (DLinkedListStack *) malloc(sizeof(DLinkedListStack));

    stack->linkedList = doublyLinkedListInitialization(freeFun, NULL);

    return stack;

}





/** This function will take the stack address, and the item address as a parameters,
    then it will pushStack the item into the stack.
 * @param stack the stack address
 * @param item the new item address
 */

void dlStackPush(DLinkedListStack *stack, void *item) {
    if (stack == NULL) {
         fprintf(stderr,"Illegal argument, the stack is NULL.");
        exit(-4);
    }

    doublyLinkedListAddLast(stack->linkedList, item);

}





/** This function will take the stack address, the array address, and the array length as a parameters,
    then it will add all the array items into the stack in order.
 * @param stack the stack address
 * @param arr the new items array address
 * @param arrLength the length of the new items array
 */

void dlStackAddAll(DLinkedListStack *stack, void **arr, int arrLength) {
    if (stack == NULL) {
        fprintf(stderr,"Illegal argument, the stack is NULL.");
        exit(-4);
    }


    for (int i = 0; i < arrLength; i++)
        dlStackPush(stack,arr[i]);

}





/** This function will take the stack address as a parameter,
    then it will return the last item that pushed to the stack,
    then the item will be removed from the stack.
 * Note: if the stack i empty the program will be terminated.
 * @param stack the stack address
 * @return it will return the (last in) item address in the stack
 */

void *dlStackPop(DLinkedListStack *stack) {

    if (stack == NULL) {
         fprintf(stderr,"Illegal argument, the stack is NULL.");
        exit(-4);
    } else if (dlStackIsEmpty(stack)) {
         fprintf(stderr,"Illegal state, the stack is empty.");
        exit(-4);
    }

    void *item = doublyLinkedListGetLast(stack->linkedList);
    doublyLinkedListDeleteLastWtoFr(stack->linkedList);

    return item;
}






/** This function will take the stack address as a parameter,
    then it will return a void array pointer that contains all the stack items.
 * @param stack the stack address
 * @return it will return a double void array that contains a copy of all the items in the stack
 */

void **dlStackToArray(DLinkedListStack *stack) {

    if (stack == NULL) {
        fprintf(stderr,"Illegal argument, the stack is NULL.");
        exit(-4);
    }

    return doublyLinkedListToArray(stack->linkedList);

}






/** This function will take the stack address as a parameter,
    then it will return the last item that pushed to the stack,
    without removing the item from the stack.
 * Note: if the stack i empty the program will be terminated.
 * @param stack the stack address
 * @return it will return the (last in) item address in the stack
 */

void *dlStackPeek(DLinkedListStack *stack) {

    if (stack == NULL) {
         fprintf(stderr,"Illegal argument, the stack is NULL.");
        exit(-4);
    } else if (dlStackIsEmpty(stack)) {
         fprintf(stderr,"Illegal state, the stack is empty.");
        exit(-4);
    }

    void *item = doublyLinkedListGetLast(stack->linkedList);

    return item;
}





/** This function will take the stack address as a parameter,
    then it will return the number of the items in the stack.
 * @param stack the stack address
 * @return it will return the number of items in the stack
 */

int dlStackGetLength(DLinkedListStack *stack) {
    return stack->linkedList->length;
}







/** This function will take the stack address as a parameter,
    then it will return one (1) if the stack is empty,
    other wise it will return zero (0).
 * @param stack the stack address
 * @return it will return one if the stack is empty, other wise it will return zero
 */

int dlStackIsEmpty(DLinkedListStack *stack) {
    return doublyLinkedListIsEmpty(stack->linkedList);
}





/** This function will take the stack address as a parameter,
    then it will delete and free the stack from all it's items.
 * @param stack the stack address
 */

void clearDLStack(DLinkedListStack *stack) {
    doublyLinkedListClear(stack->linkedList);
}






/** This function will take the stack address as a parameter,
 * then it will destroy and free the stack and all it's items.
 * @param stack the stack address
 */

void destroyDLStack(DLinkedListStack *stack) {
    destroyDoublyLinkedList(stack->linkedList);
    free(stack);
}