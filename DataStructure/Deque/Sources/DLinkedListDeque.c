#include "../Headers/DLinkedListDeque.h"
#include "../../LinkedLists/Headers/DoublyLinkedList.h"
#include "../../../System/Utils.h"








/** This function will initialize a new doubly linked list deque in the memory,
 * then return it's pointer
 * @param freeFun the freeing function that will be called to free the deque items
 * @return it will return the new allocated deque pointer
 */

DLDeque *dlDequeInitialization(void (*freeFun)(void *)) {

    if (freeFun == NULL) {
        fprintf(stderr, INVALID_ARG_MESSAGE, "freeing function pointer", "doubly linked list deque data structure");
        exit(INVALID_ARG);
    }

    DLDeque *dlDeque = (DLDeque *) malloc(sizeof(DLDeque));
    if (dlDeque == NULL) {
        fprintf(stderr, FAILED_ALLOCATION_MESSAGE, "doubly linked list deque", "doubly linked list deque data structure");
        exit(FAILED_ALLOCATION);
    }
    dlDeque->linkedList = doublyLinkedListInitialization(freeFun, NULL);

    return dlDeque;

}









/** This function will take a new item then,
 * it will insert the passed item in the front of the deque.
 * @param deque the deque pointer
 * @param item it new item pointer
 */

void dLDequeInsertFront(DLDeque *deque, void *item) {
    if (deque == NULL) {
        fprintf(stderr, NULL_POINTER_MESSAGE, "deque", "doubly linked list deque data structure");
        exit(NULL_POINTER);
    } else if (item == NULL) {
        fprintf(stderr, INVALID_ARG_MESSAGE, "new item pointer", "doubly linked list deque data structure");
        exit(INVALID_ARG);
    }

    doublyLinkedListAddFirst(deque->linkedList, item);

}








/** This function will take a new item,
 * then it will insert the new item in the end of the deque.
 * @param deque the deque pointer
 * @param item the new item pointer
 */

void dLDequeInsertRear(DLDeque *deque, void *item) {

    if (deque == NULL) {
        fprintf(stderr, NULL_POINTER_MESSAGE, "deque", "doubly linked list deque data structure");
        exit(NULL_POINTER);
    } else if (item == NULL) {
        fprintf(stderr, INVALID_ARG_MESSAGE, "new item pointer", "doubly linked list deque data structure");
        exit(INVALID_ARG);
    }

    doublyLinkedListAddLast(deque->linkedList, item);

}










/** This function will return the front item in the deque,
 * then it will remove the item from the deque.
 * @param deque the deque pointer
 * @return it will return the front item in the deque
 */

void *dLDequeGetFront(DLDeque *deque) {
    if (deque == NULL) {
        fprintf(stderr, NULL_POINTER_MESSAGE, "deque", "doubly linked list deque data structure");
        exit(NULL_POINTER);
    } else if (dLDequeIsEmpty(deque)) {
        fprintf(stderr, EMPTY_DATA_STRUCTURE_MESSAGE, "doubly linked list deque data structure");
        exit(EMPTY_DATA_STRUCTURE);
    }

    return doublyLinkedListDeleteFirstWtoFr(deque->linkedList);

}









/** This function will return the last item in the deque,
 * then it will remove the item from the deque
 * @param deque the deque pointer
 * @return it will return the last item in the deque
 */

void *dLDequeGetRear(DLDeque *deque) {

    if (deque == NULL) {
        fprintf(stderr, NULL_POINTER_MESSAGE, "deque", "doubly linked list deque data structure");
        exit(NULL_POINTER);
    } else if (dLDequeIsEmpty(deque)) {
        fprintf(stderr, EMPTY_DATA_STRUCTURE_MESSAGE, "doubly linked list deque data structure");
        exit(EMPTY_DATA_STRUCTURE);
    }

    return doublyLinkedListDeleteLastWtoFr(deque->linkedList);

}









/** This function will return the first item in the deque,
 * without removing the item from the deque.
 * @param deque the deque pointer
 * @return it will return the first item in the deque
 */

void *dLDequePeekFront(DLDeque *deque) {

    if (deque == NULL) {
        fprintf(stderr, NULL_POINTER_MESSAGE, "deque", "doubly linked list deque data structure");
        exit(NULL_POINTER);
    } else if (dLDequeIsEmpty(deque)) {
        fprintf(stderr, EMPTY_DATA_STRUCTURE_MESSAGE, "doubly linked list deque data structure");
        exit(EMPTY_DATA_STRUCTURE);
    }

    return doublyLinkedListGetFirst(deque->linkedList);

}










/** This function will return the last item in the deque,
 * without removing the item from the deque.
 * @param deque the deque pointer
 * @return it will return the last item in the deque
 */

void *dLDequePeekRear(DLDeque *deque) {

    if (deque == NULL) {
        fprintf(stderr, NULL_POINTER_MESSAGE, "deque", "doubly linked list deque data structure");
        exit(NULL_POINTER);
    } else if (dLDequeIsEmpty(deque)) {
        fprintf(stderr, EMPTY_DATA_STRUCTURE_MESSAGE, "doubly linked list deque data structure");
        exit(EMPTY_DATA_STRUCTURE);
    }

    return doublyLinkedListGetLast(deque->linkedList);

}










/** This function will return a double void array that consist of the deque items.
 * @param deque the deque pointer
 * @return it will return an array contains all the deque items
 */

void **dLDequeToArray(DLDeque *deque) {

    if (deque == NULL) {
        fprintf(stderr, NULL_POINTER_MESSAGE, "deque", "doubly linked list deque data structure");
        exit(NULL_POINTER);
    }

    return doublyLinkedListToArray(deque->linkedList);

}










/** This function will return the number of the items in the deque.
 * @param deque the deque pointer
 * @return it will return the number of the items in the deque
 */

int dLDequeGetLength(DLDeque *deque) {

    if (deque == NULL) {
        fprintf(stderr, NULL_POINTER_MESSAGE, "deque", "doubly linked list deque data structure");
        exit(NULL_POINTER);
    }

    return doublyLinkedListGetLength(deque->linkedList);

}











/** This function will check if the deque is empty or not,
 * and if it was the function will return one (1), other wise it will return zero (0).
 * @param deque the deque pointer
 * @return it will return one if the deque was empty, other wise it will return zero
 */

int dLDequeIsEmpty(DLDeque *deque) {

    if (deque == NULL) {
        fprintf(stderr, NULL_POINTER_MESSAGE, "deque", "doubly linked list deque data structure");
        exit(NULL_POINTER);
    }

    return doublyLinkedListIsEmpty(deque->linkedList);

}











/** This function will clear and free all the deque items,
 * without freeing the deque.
 * @param deque the deque pointer
 */

void clearDLDeque(DLDeque *deque) {

    if (deque == NULL) {
        fprintf(stderr, NULL_POINTER_MESSAGE, "deque", "doubly linked list deque data structure");
        exit(NULL_POINTER);
    }

    doublyLinkedListClear(deque->linkedList);

}











/** This function will destroy and free the deque with all it's items.
 * @param deque the deque pointer
 */

void destroyDLDeque(DLDeque *deque) {

    if (deque == NULL) {
        fprintf(stderr, NULL_POINTER_MESSAGE, "deque", "doubly linked list deque data structure");
        exit(NULL_POINTER);
    }

    destroyDoublyLinkedList(deque->linkedList);
    free(deque);

}