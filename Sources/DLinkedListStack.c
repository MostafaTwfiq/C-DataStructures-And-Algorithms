#include "../Headers/DLinkedListStack.h"




/** This function will take the size of the items in the stack as a parameters,
    then it will initialize the stack and return it's address.
 * @param sizeOfType
 * @return
 */

DLinkedListStack *dlStackInitialization(int sizeOfType) {

    DLinkedListStack *stack = (DLinkedListStack *) malloc(sizeof(DLinkedListStack));

    stack->linkedList = doublyLinkedListInitialization(sizeOfType);

    return stack;

}




/** This function will take the stack address, and the item address a a parameters,
    then it will push the item into the stack.
 * @param stack
 * @param item
 */

void dlStackPush(DLinkedListStack *stack, void *item) {
    if (stack == NULL) {
        printf("Illegal argument, the stack is NULL.");
        exit(-4);
    }

    doublyLinkedListAddLast(stack->linkedList, item);

}




/** This function will take the stack address as a parameter,
    then it will return the last item that pushed to the stack,
    then the item will be removed from the stack.
 * Note: if the stack i empty the program will be terminated.
 * @param stack
 * @return
 */

void *dlStackPop(DLinkedListStack *stack) {

    if (stack == NULL) {
        printf("Illegal argument, the stack is NULL.");
        exit(-4);
    } else if (dlStackIsEmpty(stack)) {
        printf("Illegal state, the stack is empty.");
        exit(-4);
    }

    void *item = doublyLinkedListGetLast(stack->linkedList);
    doublyLinkedListDeleteLastWtFr(stack->linkedList);

    return item;
}




/** This function will take the stack address as a parameter,
    then it will return the last item that pushed to the stack,
    without removing the item from the stack.
 * Note: if the stack i empty the program will be terminated.
 * @param stack
 * @return
 */

void *dlStackPeek(DLinkedListStack *stack) {

    if (stack == NULL) {
        printf("Illegal argument, the stack is NULL.");
        exit(-4);
    } else if (dlStackIsEmpty(stack)) {
        printf("Illegal state, the stack is empty.");
        exit(-4);
    }

    void *item = doublyLinkedListGetLast(stack->linkedList);

    return item;
}





/** This function will take the stack address as a parameter,
    then it will return one (1) if the stack is empty,
    other wise it will return zero (0).
 * @param stack
 * @return
 */

int dlStackIsEmpty(DLinkedListStack *stack) {
    return doublyLinkedListIsEmpty(stack->linkedList);
}





/** This function will take the stack address as a parameter,
    then it will delete and free the stack from all it's items.
 * @param stack
 */

void clearDLStack(DLinkedListStack *stack) {
    doublyLinkedListClear(stack->linkedList);
}




/** This function will take the stack address as a parameter,
 * then it will destroy and free the stack and all it's items.
 * @param stack
 */

void destroyDLStack(DLinkedListStack *stack) {
    destroyDoublyLinkedList(stack->linkedList);
    free(stack);
}