#include "../Headers/DoublyLinkedList.h"
#include "../../../System/Utils.h"
#include "../../../Unit Test/CuTest/CuTest.h"


typedef struct Node {
    void *item;
    struct Node *next; // a pointer to the next node.
    struct Node *prevNode; // a pointer to the previous node.
} Node;


/** This function will allocate a new linked list in the memory, setup it's fields and return it.
 *
 * @param freeFun the free function address that will be called to free the linked list items
 * @param comparator the comparator function address, that will be called to compare two items
 * */

DoublyLinkedList *
doublyLinkedListInitialization(void (*freeFun)(void *), int (*comparator)(const void *, const void *)) {
    if (freeFun == NULL) {
#ifdef C_DATASTRUCTURES_ERRORSTESTSTRUCT_H
        ERROR_TEST->errorCode = INVALID_ARG;
        return NULL;
#else
        fprintf(stderr, INVALID_ARG_MESSAGE, "free function pointer", "doubly linked list data structure");
        exit(INVALID_ARG);
#endif

    }

    DoublyLinkedList *linkedList = (DoublyLinkedList *) malloc(sizeof(DoublyLinkedList));
    if (linkedList == NULL) {
#ifdef C_DATASTRUCTURES_ERRORSTESTSTRUCT_H
        ERROR_TEST->errorCode = FAILED_ALLOCATION;
        return NULL;
#else
        fprintf(stderr, FAILED_ALLOCATION_MESSAGE, "linked list", "doubly linked list data structure");
        exit(FAILED_ALLOCATION);
#endif

    }

    linkedList->head = linkedList->tail = NULL;
    linkedList->length = 0;
    linkedList->freeFun = freeFun;
    linkedList->comparator = comparator;

    return linkedList;
}


/** This function will take the linked list address, and the item address as a parameters,
  * then it will add the item in the start of the linked list.
  *
  * @param linkedList the linked list address
  * @param item the new item address
  */

void doublyLinkedListAddFirst(DoublyLinkedList *linkedList, void *item) {
    if (linkedList == NULL) {
#ifdef C_DATASTRUCTURES_ERRORSTESTSTRUCT_H
        ERROR_TEST->errorCode = NULL_POINTER;
        return;
#else
        fprintf(stderr, NULL_POINTER_MESSAGE, "linked list pointer", "doubly linked list data structure");
        exit(NULL_POINTER);
#endif

    } else if (item == NULL) {
#ifdef C_DATASTRUCTURES_ERRORSTESTSTRUCT_H
        ERROR_TEST->errorCode = INVALID_ARG;
        return;
#else
        fprintf(stderr, INVALID_ARG_MESSAGE, "item pointer", "doubly linked list data structure");
        exit(INVALID_ARG);
#endif

    }

    Node *newNode = (Node *) malloc(sizeof(Node));
    if (newNode == NULL) {
#ifdef C_DATASTRUCTURES_ERRORSTESTSTRUCT_H
        ERROR_TEST->errorCode = FAILED_ALLOCATION;
        return;
#else
        fprintf(stderr, FAILED_ALLOCATION_MESSAGE, "new node", "doubly linked list data structure");
        exit(FAILED_ALLOCATION);
#endif

    }

    newNode->item = item;

    newNode->next = linkedList->head;
    newNode->prevNode = NULL;

    if (doublyLinkedListIsEmpty(linkedList))
        linkedList->tail = newNode;
    else
        linkedList->head->prevNode = newNode;

    linkedList->head = newNode;
    linkedList->length++;

}


/** This function will take the linked list address, and the item address as a parameters,
 * then it will add the item in the end of the linked list.
 *
 * @param linkedList the linked list address
 * @param item the new item address
 */

void doublyLinkedListAddLast(DoublyLinkedList *linkedList, void *item) {
    if (linkedList == NULL) {
#ifdef C_DATASTRUCTURES_ERRORSTESTSTRUCT_H
        ERROR_TEST->errorCode = NULL_POINTER;
        return;
#else
        fprintf(stderr, NULL_POINTER_MESSAGE, "linked list pointer", "doubly linked list data structure");
        exit(NULL_POINTER);
#endif

    } else if (item == NULL) {
#ifdef C_DATASTRUCTURES_ERRORSTESTSTRUCT_H
        ERROR_TEST->errorCode = INVALID_ARG;
        return;
#else
        fprintf(stderr, INVALID_ARG_MESSAGE, "item pointer", "doubly linked list data structure");
        exit(INVALID_ARG);
#endif

    }

    Node *newNode = (Node *) malloc(sizeof(Node));
    if (newNode == NULL) {
#ifdef C_DATASTRUCTURES_ERRORSTESTSTRUCT_H
        ERROR_TEST->errorCode = FAILED_ALLOCATION;
        return;
#else
        fprintf(stderr, FAILED_ALLOCATION_MESSAGE, "new node", "doubly linked list data structure");
        exit(FAILED_ALLOCATION);
#endif

    }

    newNode->item = item;

    newNode->next = NULL;

    if (doublyLinkedListIsEmpty(linkedList))
        linkedList->head = newNode;
    else
        linkedList->tail->next = newNode;

    newNode->prevNode = linkedList->tail;
    linkedList->tail = newNode;
    linkedList->length++;
}


/** This function will take the linked list address, item index, and the item address as parameters,
 * then it will add the item in the passed index.
 *
 * @param linkedList the linked list address
 * @param index the index of the new item
 * @param item the new item address
 */

void doublyLinkedListAddAtIndex(DoublyLinkedList *linkedList, int index, void *item) {
    if (linkedList == NULL) {
#ifdef C_DATASTRUCTURES_ERRORSTESTSTRUCT_H
        ERROR_TEST->errorCode = NULL_POINTER;
        return;
#else
        fprintf(stderr, NULL_POINTER_MESSAGE, "linked list pointer", "doubly linked list data structure");
        exit(NULL_POINTER);
#endif

    } else if (item == NULL) {
#ifdef C_DATASTRUCTURES_ERRORSTESTSTRUCT_H
        ERROR_TEST->errorCode = INVALID_ARG;
        return;
#else
        fprintf(stderr, INVALID_ARG_MESSAGE, "item pointer", "doubly linked list data structure");
        exit(INVALID_ARG);
#endif

    } else if (index < 0 || index >= doublyLinkedListGetLength(linkedList)) {
#ifdef C_DATASTRUCTURES_ERRORSTESTSTRUCT_H
        ERROR_TEST->errorCode = OUT_OF_RANGE;
        return;
#else
        fprintf(stderr, OUT_OF_RANGE_MESSAGE, "doubly linked list data structure");
        exit(OUT_OF_RANGE);
#endif

    }

    Node *newNode = (Node *) malloc(sizeof(Node));
    if (newNode == NULL) {
#ifdef C_DATASTRUCTURES_ERRORSTESTSTRUCT_H
        ERROR_TEST->errorCode = FAILED_ALLOCATION;
        return;
#else
        fprintf(stderr, FAILED_ALLOCATION_MESSAGE, "new node", "doubly linked list data structure");
        exit(FAILED_ALLOCATION);
#endif

    }

    newNode->item = item;

    Node *currentNode = linkedList->head;
    while (index-- != 0)
        currentNode = currentNode->next;


    if (currentNode->prevNode == NULL) {
        newNode->next = currentNode;
        newNode->prevNode = NULL;
        currentNode->prevNode = newNode;
        linkedList->head = newNode;
    } else {
        newNode->next = currentNode;
        newNode->prevNode = currentNode->prevNode;
        currentNode->prevNode->next = newNode;
        currentNode->prevNode = newNode;
    }

    linkedList->length++;

}


/** This function will take the linked list address, items array, and the length of the array as parameters,
 * then it will copy the array item if the linked list in a new items addresses.
 *
 * Note: this function will add all the new items in the end of the linked list.
 *
 * @param linkedList the linked list address
 * @param items the new items array address
 * @param itemsLength the length of the new items array
 */

void doublyLinkedListAddAll(DoublyLinkedList *linkedList, void **items, int itemsLength) {
    if (linkedList == NULL) {
#ifdef C_DATASTRUCTURES_ERRORSTESTSTRUCT_H
        ERROR_TEST->errorCode = NULL_POINTER;
        return;
#else
        fprintf(stderr, NULL_POINTER_MESSAGE, "linked list pointer", "doubly linked list data structure");
        exit(NULL_POINTER);
#endif

    } else if (items == NULL) {
#ifdef C_DATASTRUCTURES_ERRORSTESTSTRUCT_H
        ERROR_TEST->errorCode = INVALID_ARG;
        return;
#else
        fprintf(stderr, INVALID_ARG_MESSAGE, "items array pointer", "doubly linked list data structure");
        exit(INVALID_ARG);
#endif

    }

    for (int i = 0; i < itemsLength; i++)
        doublyLinkedListAddLast(linkedList, items[i]);

}


/** This function will take the linked list address as a parameter,
 * then it will delete and free the first element from the linked list.
 *
 * @param linkedList the linked list address
 */

void doublyLinkedListDeleteFirst(DoublyLinkedList *linkedList) {

    if (linkedList == NULL) {
#ifdef C_DATASTRUCTURES_ERRORSTESTSTRUCT_H
        ERROR_TEST->errorCode = NULL_POINTER;
        return;
#else
        fprintf(stderr, NULL_POINTER_MESSAGE, "linked list pointer", "doubly linked list data structure");
        exit(NULL_POINTER);
#endif

    } else if (doublyLinkedListIsEmpty(linkedList)) {
#ifdef C_DATASTRUCTURES_ERRORSTESTSTRUCT_H
        ERROR_TEST->errorCode = EMPTY_DATA_STRUCTURE;
        return;
#else
        fprintf(stderr, EMPTY_DATA_STRUCTURE_MESSAGE, "doubly linked list data structure");
        exit(EMPTY_DATA_STRUCTURE);
#endif

    }

    Node *nodeToFree = linkedList->head;
    if (linkedList->head == linkedList->tail) {
        linkedList->head = linkedList->tail = NULL;
    } else {
        linkedList->head = linkedList->head->next;
        linkedList->head->prevNode = NULL;
    }

    linkedList->length--;
    linkedList->freeFun(nodeToFree->item);
    free(nodeToFree);

}


/** This function will take the linked list address as a parameter,
 * then it will delete and free only the node without the item of the first element from the linked list.
 *
 * @param linkedList the linked list address
 * @return it will return the deleted item
 */

void *doublyLinkedListDeleteFirstWtoFr(DoublyLinkedList *linkedList) {

    if (linkedList == NULL) {
#ifdef C_DATASTRUCTURES_ERRORSTESTSTRUCT_H
        ERROR_TEST->errorCode = NULL_POINTER;
        return NULL;
#else
        fprintf(stderr, NULL_POINTER_MESSAGE, "linked list pointer", "doubly linked list data structure");
        exit(NULL_POINTER);
#endif

    } else if (doublyLinkedListIsEmpty(linkedList)) {
#ifdef C_DATASTRUCTURES_ERRORSTESTSTRUCT_H
        ERROR_TEST->errorCode = EMPTY_DATA_STRUCTURE;
        return NULL;
#else
        fprintf(stderr, EMPTY_DATA_STRUCTURE_MESSAGE, "doubly linked list data structure");
        exit(EMPTY_DATA_STRUCTURE);
#endif

    }

    Node *nodeToFree = linkedList->head;
    if (linkedList->head == linkedList->tail) {
        linkedList->head = linkedList->tail = NULL;
    } else {
        linkedList->head = linkedList->head->next;
        linkedList->head->prevNode = NULL;
    }

    linkedList->length--;
    void *returnItem = nodeToFree->item;
    free(nodeToFree);

    return returnItem;

}


/** This function will take the linked list address as a parameter,
 * then it will delete and free the last element from the linked list.
 *
 * @param linkedList the linked list address
 */

void doublyLinkedListDeleteLast(DoublyLinkedList *linkedList) {

    if (linkedList == NULL) {
#ifdef C_DATASTRUCTURES_ERRORSTESTSTRUCT_H
        ERROR_TEST->errorCode = NULL_POINTER;
        return;
#else
        fprintf(stderr, NULL_POINTER_MESSAGE, "linked list pointer", "doubly linked list data structure");
        exit(NULL_POINTER);
#endif

    } else if (doublyLinkedListIsEmpty(linkedList)) {
#ifdef C_DATASTRUCTURES_ERRORSTESTSTRUCT_H
        ERROR_TEST->errorCode = EMPTY_DATA_STRUCTURE;
        return;
#else
        fprintf(stderr, EMPTY_DATA_STRUCTURE_MESSAGE, "doubly linked list data structure");
        exit(EMPTY_DATA_STRUCTURE);
#endif

    }

    Node *nodeToFree = linkedList->tail;
    if (linkedList->head == linkedList->tail)
        linkedList->head = linkedList->tail = NULL;
    else {
        linkedList->tail = nodeToFree->prevNode;
        linkedList->tail->next = NULL;
    }

    linkedList->length--;
    linkedList->freeFun(nodeToFree->item);
    free(nodeToFree);

}


/** This function will take the linked list address as a parameter,
 * then it will delete and free only the node without the item of the last element from the linked list.
 *
 * @param linkedList the linked list address
 * @return it will return the deleted item
 */

void *doublyLinkedListDeleteLastWtoFr(DoublyLinkedList *linkedList) {

    if (linkedList == NULL) {
#ifdef C_DATASTRUCTURES_ERRORSTESTSTRUCT_H
        ERROR_TEST->errorCode = NULL_POINTER;
        return NULL;
#else
        fprintf(stderr, NULL_POINTER_MESSAGE, "linked list pointer", "doubly linked list data structure");
        exit(NULL_POINTER);
#endif

    } else if (doublyLinkedListIsEmpty(linkedList)) {
#ifdef C_DATASTRUCTURES_ERRORSTESTSTRUCT_H
        ERROR_TEST->errorCode = EMPTY_DATA_STRUCTURE;
        return NULL;
#else
        fprintf(stderr, EMPTY_DATA_STRUCTURE_MESSAGE, "doubly linked list data structure");
        exit(EMPTY_DATA_STRUCTURE);
#endif

    }

    Node *nodeToFree = linkedList->tail;
    if (linkedList->head == linkedList->tail)
        linkedList->head = linkedList->tail = NULL;
    else {
        linkedList->tail = nodeToFree->prevNode;
        linkedList->tail->next = NULL;
    }

    linkedList->length--;
    void *returnItem = nodeToFree->item;
    free(nodeToFree);

    return returnItem;
}


/** This function will take the linked list address, and the index as parameters,
 * then it will delete the item in this index.
 *
 * Note: if the index is out of the linked list rang then the program will be terminated.
 *
 * @param linkedList the linked list address
 * @param index the index of the item that wanted to be deleted
 */

void doublyLinkedListDeleteAtIndex(DoublyLinkedList *linkedList, int index) {
    if (linkedList == NULL) {
#ifdef C_DATASTRUCTURES_ERRORSTESTSTRUCT_H
        ERROR_TEST->errorCode = NULL_POINTER;
        return;
#else
        fprintf(stderr, NULL_POINTER_MESSAGE, "linked list pointer", "doubly linked list data structure");
        exit(NULL_POINTER);
#endif

    } else if (doublyLinkedListIsEmpty(linkedList)) {
#ifdef C_DATASTRUCTURES_ERRORSTESTSTRUCT_H
        ERROR_TEST->errorCode = EMPTY_DATA_STRUCTURE;
        return;
#else
        fprintf(stderr, EMPTY_DATA_STRUCTURE_MESSAGE, "doubly linked list data structure");
        exit(EMPTY_DATA_STRUCTURE);
#endif

    } else if (index < 0 || index >= doublyLinkedListGetLength(linkedList)) {
#ifdef C_DATASTRUCTURES_ERRORSTESTSTRUCT_H
        ERROR_TEST->errorCode = OUT_OF_RANGE;
        return;
#else
        fprintf(stderr, OUT_OF_RANGE_MESSAGE, "doubly linked list data structure");
        exit(OUT_OF_RANGE);
#endif

    }

    Node *currentNode = linkedList->head;
    for (int i = 0; i < index; i++)
        currentNode = currentNode->next;

    if (currentNode == linkedList->head) //if the index == 0.
        doublyLinkedListDeleteFirst(linkedList);
    else if (currentNode == linkedList->tail) //if the index = length - 1.
        doublyLinkedListDeleteLast(linkedList);
    else {
        currentNode->prevNode->next = currentNode->next;
        currentNode->next->prevNode = currentNode->prevNode;

        linkedList->length--;
        linkedList->freeFun(currentNode->item);
        free(currentNode);
    }

}


/** This function will take the linked list address, and the index as parameters,
 * then it will delete and free only the node without the item of the item in this index.
 *
 * Note: if the index is out of the linked list rang then the program will be terminated.
 *
 * @param linkedList the linked list address
 * @param index the index of the item that want to be deleted
 * @return it will return the deleted item
 */

void *doublyLinkedListDeleteAtIndexWtoFr(DoublyLinkedList *linkedList, int index) {
    if (linkedList == NULL) {
#ifdef C_DATASTRUCTURES_ERRORSTESTSTRUCT_H
        ERROR_TEST->errorCode = NULL_POINTER;
        return NULL;
#else
        fprintf(stderr, NULL_POINTER_MESSAGE, "linked list pointer", "doubly linked list data structure");
        exit(NULL_POINTER);
#endif

    } else if (doublyLinkedListIsEmpty(linkedList)) {
#ifdef C_DATASTRUCTURES_ERRORSTESTSTRUCT_H
        ERROR_TEST->errorCode = EMPTY_DATA_STRUCTURE;
        return NULL;
#else
        fprintf(stderr, EMPTY_DATA_STRUCTURE_MESSAGE, "doubly linked list data structure");
        exit(EMPTY_DATA_STRUCTURE);
#endif

    } else if (index < 0 || index >= doublyLinkedListGetLength(linkedList)) {
#ifdef C_DATASTRUCTURES_ERRORSTESTSTRUCT_H
        ERROR_TEST->errorCode = OUT_OF_RANGE;
        return NULL;
#else
        fprintf(stderr, OUT_OF_RANGE_MESSAGE, "doubly linked list data structure");
        exit(OUT_OF_RANGE);
#endif

    }

    Node *currentNode = linkedList->head;
    for (int i = 0; i < index; i++)
        currentNode = currentNode->next;

    if (currentNode == linkedList->head) //if the index == 0.
        return doublyLinkedListDeleteFirstWtoFr(linkedList);
    else if (currentNode == linkedList->tail) //if the index = length - 1.
        return doublyLinkedListDeleteLastWtoFr(linkedList);
    else {
        currentNode->prevNode->next = currentNode->next;
        currentNode->next->prevNode = currentNode->prevNode;

        linkedList->length--;
        void *returnItem = currentNode->item;
        free(currentNode);

        return returnItem;

    }

}


/** This function will take the linked list address, and the item address as parameters, then
 * then it will return 1 if the item is in the list other wise it will return zero (0).
 *
 * Note: the function will use the comparator function to know if the two items are equivalent or not.
 *
 * Note: the function will not free the passed item.
 *
 * @param linkedList the linked list address
 * @param item the item address that has the same item as the wanted one
 * @return it will return one if the item is in the linked list, other wise it will return zero
 */

int doublyLinkedListContains(DoublyLinkedList *linkedList, void *item) {

    if (linkedList == NULL) {
#ifdef C_DATASTRUCTURES_ERRORSTESTSTRUCT_H
        ERROR_TEST->errorCode = NULL_POINTER;
        return -1;
#else
        fprintf(stderr, NULL_POINTER_MESSAGE, "linked list pointer", "doubly linked list data structure");
        exit(NULL_POINTER);
#endif

    } else if (item == NULL) {
#ifdef C_DATASTRUCTURES_ERRORSTESTSTRUCT_H
        ERROR_TEST->errorCode = INVALID_ARG;
        return -1;
#else
        fprintf(stderr, INVALID_ARG_MESSAGE, "item pointer", "doubly linked list data structure");
        exit(INVALID_ARG);
#endif

    } else if (linkedList->comparator == NULL) {
#ifdef C_DATASTRUCTURES_ERRORSTESTSTRUCT_H
        ERROR_TEST->errorCode = NULL_POINTER;
        return -1;
#else
        fprintf(stderr, NULL_POINTER_MESSAGE, "comparator function", "doubly linked list data structure");
        exit(NULL_POINTER);
#endif

    }

    Node *currentNode = linkedList->head;

    while (currentNode != NULL) {
        // if the comparator function returned zero then the two items are equal.
        if (linkedList->comparator(item, currentNode->item) == 0)
            return 1;

        currentNode = currentNode->next;
    }

    return 0;

}


/** This function will take the linked list address, and the item address as a parameters,
 * then it will return the index of the given item, other wise it will return minus one (-1).
 *
 * Note: the function will use the comparator function to know if the two items are equivalent or not.
 *
 * Note: the function will not free the passed item.
 *
 * @param linkedList the linked list address
 * @param item the item address the has the same item as the wanted one
 * @return it will return the index of the item if found, other wise it will return -1
 */

int doublyLinkedListGetIndex(DoublyLinkedList *linkedList, void *item) {

    if (linkedList == NULL) {
#ifdef C_DATASTRUCTURES_ERRORSTESTSTRUCT_H
        ERROR_TEST->errorCode = NULL_POINTER;
        return -1;
#else
        fprintf(stderr, NULL_POINTER_MESSAGE, "linked list pointer", "doubly linked list data structure");
        exit(NULL_POINTER);
#endif

    } else if (item == NULL) {
#ifdef C_DATASTRUCTURES_ERRORSTESTSTRUCT_H
        ERROR_TEST->errorCode = INVALID_ARG;
        return -1;
#else
        fprintf(stderr, INVALID_ARG_MESSAGE, "item pointer", "doubly linked list data structure");
        exit(INVALID_ARG);
#endif

    } else if (linkedList->comparator == NULL) {
#ifdef C_DATASTRUCTURES_ERRORSTESTSTRUCT_H
        ERROR_TEST->errorCode = NULL_POINTER;
        return -1;
#else
        fprintf(stderr, NULL_POINTER_MESSAGE, "comparator function", "doubly linked list data structure");
        exit(NULL_POINTER);
#endif

    }

    Node *currentNode = linkedList->head;

    for (int index = 0; currentNode != NULL; currentNode = currentNode->next, index++) {
        // if the comparator function returned zero then the two items are equal.
        if (linkedList->comparator(item, currentNode->item) == 0)
            return index;

    }

    return -1;

}


/** This function will take the linked list address as a parameter,
 * then it will return the first item in the list.
 *
 * Note: if the linked list is empty the function will return NULL.
 *
 * @param linkedList the linked list address
 * @return it will return the first item in the linked list
 */

void *doublyLinkedListGetFirst(DoublyLinkedList *linkedList) {

    if (linkedList == NULL) {
#ifdef C_DATASTRUCTURES_ERRORSTESTSTRUCT_H
        ERROR_TEST->errorCode = NULL_POINTER;
        return NULL;
#else
        fprintf(stderr, NULL_POINTER_MESSAGE, "linked list pointer", "doubly linked list data structure");
        exit(NULL_POINTER);
#endif

    } else if (doublyLinkedListIsEmpty(linkedList)) {
#ifdef C_DATASTRUCTURES_ERRORSTESTSTRUCT_H
        ERROR_TEST->errorCode = EMPTY_DATA_STRUCTURE;
        return NULL;
#else
        fprintf(stderr, EMPTY_DATA_STRUCTURE_MESSAGE, "doubly linked list data structure");
        exit(EMPTY_DATA_STRUCTURE);
#endif

    }

    return linkedList->head->item;

}


/** This function will take the linked list address as a parameter,
 * then it will return the last item in the list.
 *
 * Note: if the linked list is empty the function will return NULL.
 *
 * @param linkedList the linked list address
 * @return it will return the last item in the linked list
 */

void *doublyLinkedListGetLast(DoublyLinkedList *linkedList) {

    if (linkedList == NULL) {
#ifdef C_DATASTRUCTURES_ERRORSTESTSTRUCT_H
        ERROR_TEST->errorCode = NULL_POINTER;
        return NULL;
#else
        fprintf(stderr, NULL_POINTER_MESSAGE, "linked list pointer", "doubly linked list data structure");
        exit(NULL_POINTER);
#endif

    } else if (doublyLinkedListIsEmpty(linkedList)) {
#ifdef C_DATASTRUCTURES_ERRORSTESTSTRUCT_H
        ERROR_TEST->errorCode = EMPTY_DATA_STRUCTURE;
        return NULL;
#else
        fprintf(stderr, EMPTY_DATA_STRUCTURE_MESSAGE, "doubly linked list data structure");
        exit(EMPTY_DATA_STRUCTURE);
#endif

    }

    return linkedList->tail->item;

}


/** This function will take the linked list address, and the item address, as a parameters,
 * then it will return the item from the list if found, other wise it will return NULL.
 *
 * Note: the function will use the comparator function to know if the two items are equivalent or not.
 *
 * Note: the function will not free the passed item.
 *
 * @param linkedList the linked list address
 * @param item the item address that hash the same item of the wanted one
 * @return it will return the item address if found, other wise it will return NULL
 */

void *doublyLinkedListGetItem(DoublyLinkedList *linkedList, void *item) {

    if (linkedList == NULL) {
#ifdef C_DATASTRUCTURES_ERRORSTESTSTRUCT_H
        ERROR_TEST->errorCode = NULL_POINTER;
        return NULL;
#else
        fprintf(stderr, NULL_POINTER_MESSAGE, "linked list pointer", "doubly linked list data structure");
        exit(NULL_POINTER);
#endif

    } else if (item == NULL) {
#ifdef C_DATASTRUCTURES_ERRORSTESTSTRUCT_H
        ERROR_TEST->errorCode = INVALID_ARG;
        return NULL;
#else
        fprintf(stderr, INVALID_ARG_MESSAGE, "item pointer", "doubly linked list data structure");
        exit(INVALID_ARG);
#endif

    } else if (linkedList->comparator == NULL) {
#ifdef C_DATASTRUCTURES_ERRORSTESTSTRUCT_H
        ERROR_TEST->errorCode = NULL_POINTER;
        return NULL;
#else
        fprintf(stderr, NULL_POINTER_MESSAGE, "comparator function", "doubly linked list data structure");
        exit(NULL_POINTER);
#endif
    }

    Node *currentNode = linkedList->head;

    while (currentNode != NULL) {
        // if the comparator function returned zero then the two items are equal.
        if (linkedList->comparator(item, currentNode->item) == 0)
            return currentNode->item;

        currentNode = currentNode->next;
    }

    return NULL;
}


/** This function will take the linked list address, and the index as parameters,
 * then it will return the item in the given index.
 *
 * Note: if the index is out of the linked list range the program will terminate.
 *
 * @param linkedList the linked list address
 * @param index the index of the wanted item
 * @return it will return the item in the provided index
 */

void *doublyLinkedListGet(DoublyLinkedList *linkedList, int index) {

    if (linkedList == NULL) {
#ifdef C_DATASTRUCTURES_ERRORSTESTSTRUCT_H
        ERROR_TEST->errorCode = NULL_POINTER;
        return NULL;
#else
        fprintf(stderr, NULL_POINTER_MESSAGE, "linked list pointer", "doubly linked list data structure");
        exit(NULL_POINTER);
#endif

    } else if (doublyLinkedListIsEmpty(linkedList)) {
#ifdef C_DATASTRUCTURES_ERRORSTESTSTRUCT_H
        ERROR_TEST->errorCode = EMPTY_DATA_STRUCTURE;
        return NULL;
#else
        fprintf(stderr, EMPTY_DATA_STRUCTURE_MESSAGE, "doubly linked list data structure");
        exit(EMPTY_DATA_STRUCTURE);
#endif

    } else if (index < 0 || index >= doublyLinkedListGetLength(linkedList)) {
#ifdef C_DATASTRUCTURES_ERRORSTESTSTRUCT_H
        ERROR_TEST->errorCode = OUT_OF_RANGE;
        return NULL;
#else
        fprintf(stderr, OUT_OF_RANGE_MESSAGE, "doubly linked list data structure");
        exit(OUT_OF_RANGE);
#endif

    }

    Node *currentNode = linkedList->head;
    for (int i = 0; i < index; i++)
        currentNode = currentNode->next;

    return currentNode->item;

}


/** This function will take the linked list address as a parameter,
 * then it will return a void pointer to an array consist of the items in the linked list.
 *
 * Note: the items in the array doesn't share the same address in the linked list items.
 *
 * @param linkedList the linked list address
 * @return it will return a double void array that hash a copy of the items in the linked list
 */

void **doublyLinkedListToArray(DoublyLinkedList *linkedList) {
    if (linkedList == NULL) {
#ifdef C_DATASTRUCTURES_ERRORSTESTSTRUCT_H
        ERROR_TEST->errorCode = NULL_POINTER;
        return NULL;
#else
        fprintf(stderr, NULL_POINTER_MESSAGE, "linked list pointer", "doubly linked list data structure");
        exit(NULL_POINTER);
#endif

    }

    void **array = (void **) malloc(sizeof(void *) * doublyLinkedListGetLength(linkedList));
    if (array == NULL) {
#ifdef C_DATASTRUCTURES_ERRORSTESTSTRUCT_H
        ERROR_TEST->errorCode = FAILED_ALLOCATION;
        return NULL;
#else
        fprintf(stderr, FAILED_ALLOCATION_MESSAGE, "to array", "doubly linked list data structure");
        exit(FAILED_ALLOCATION);
#endif

    }

    Node *currentNode = linkedList->head;
    for (int i = 0; i < doublyLinkedListGetLength(linkedList); i++) {
        array[i] = currentNode->item;
        currentNode = currentNode->next;
    }

    return array;

}


/** This function will take the linked list address as a parameter,
 * the it will return the number of items in the linked list.
 *
 * @param linkedList the linked list address
 * @return it will return the number of items in the linked list
 */

int doublyLinkedListGetLength(DoublyLinkedList *linkedList) {

    if (linkedList == NULL) {
#ifdef C_DATASTRUCTURES_ERRORSTESTSTRUCT_H
        ERROR_TEST->errorCode = NULL_POINTER;
        return -1;
#else
        fprintf(stderr, NULL_POINTER_MESSAGE, "linked list pointer", "doubly linked list data structure");
        exit(NULL_POINTER);
#endif

    }

    return linkedList->length;
}


/** This function will take the linked list address as a parameter,
 * then it will return one (1) if the linked list is empty, other wise it will return 0.
 *
 * @param linkedList the linked list address
 * @return it will return one if the linked list is empty, other wise it will return zero
 */

int doublyLinkedListIsEmpty(DoublyLinkedList *linkedList) {

    if (linkedList == NULL) {
#ifdef C_DATASTRUCTURES_ERRORSTESTSTRUCT_H
        ERROR_TEST->errorCode = NULL_POINTER;
        return -1;
#else
        fprintf(stderr, NULL_POINTER_MESSAGE, "linked list pointer", "doubly linked list data structure");
        exit(NULL_POINTER);
#endif

    }

    return linkedList->head == NULL && linkedList->tail == NULL;

}


/** This method will take the linked list address, and the print function address as a parameter,
 * then it will call thr print function and pass to it an item pointer to be printed.
 *
 * @param linkedList the linked list address
 * @param printFun the print function address
 */

void printDoublyLinkedList(DoublyLinkedList *linkedList, void (*printFun)(const void *)) {

    if (linkedList == NULL) {
#ifdef C_DATASTRUCTURES_ERRORSTESTSTRUCT_H
        ERROR_TEST->errorCode = NULL_POINTER;
        return;
#else
        fprintf(stderr, NULL_POINTER_MESSAGE, "linked list pointer", "doubly linked list data structure");
        exit(NULL_POINTER);
#endif

    } else if (printFun == NULL) {
#ifdef C_DATASTRUCTURES_ERRORSTESTSTRUCT_H
        ERROR_TEST->errorCode = INVALID_ARG;
        return;
#else
        fprintf(stderr, INVALID_ARG_MESSAGE, "print function pointer", "doubly linked list data structure");
        exit(INVALID_ARG);
#endif

    }


    Node *currentNode = linkedList->head;
    while (currentNode != NULL) {
        printFun(currentNode->item);
        currentNode = currentNode->next;
    }

}


/** This function will take the linked list address as a parameter,
 * then it will delete and free all the items from the linked list.
 *
 * @param linkedList the linked list address
 */

void doublyLinkedListClear(DoublyLinkedList *linkedList) {

    if (linkedList == NULL) {
#ifdef C_DATASTRUCTURES_ERRORSTESTSTRUCT_H
        ERROR_TEST->errorCode = NULL_POINTER;
        return;
#else
        fprintf(stderr, NULL_POINTER_MESSAGE, "linked list pointer", "doubly linked list data structure");
        exit(NULL_POINTER);
#endif

    }

    Node *currentNode = linkedList->head;
    Node *nodeToFree;

    while (currentNode != NULL) {
        nodeToFree = currentNode;
        currentNode = currentNode->next;

        linkedList->freeFun(nodeToFree->item);
        free(nodeToFree);
    }

    linkedList->head = linkedList->tail = NULL;
    linkedList->length = 0;
}


/** This function will take the linked list address as a parameter,
 * then it will destroy and free the linked list and all it's nodes.
 *
 * @param linkedList the linked list address
 */

void destroyDoublyLinkedList(void *linkedList) {

    if (linkedList == NULL) {
#ifdef C_DATASTRUCTURES_ERRORSTESTSTRUCT_H
        ERROR_TEST->errorCode = NULL_POINTER;
        return;
#else
        fprintf(stderr, NULL_POINTER_MESSAGE, "linked list pointer", "doubly linked list data structure");
        exit(NULL_POINTER);
#endif

    }

    doublyLinkedListClear(linkedList);
    free(linkedList);

}