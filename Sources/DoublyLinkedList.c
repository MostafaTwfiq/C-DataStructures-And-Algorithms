#include "../Headers/DoublyLinkedList.h"





typedef struct DLLItem {
    void *value;
    int sizeOfItem;
} DLLItem;


typedef struct Node {
    DLLItem *item;
    struct Node *next; // a pointer to the next node.
    struct Node *prevNode; // a pointer to the previous node.
} Node;






void dLinkedListDestroyItem(DLLItem *item, void (*freeFun)(void *));







/** This function will allocate a new linked list in the memory, setup it's fields and return it.
 * @param freeFun the free function address that will be called to free the linked list items
 * */

DoublyLinkedList *doublyLinkedListInitialization(void (*freeFun)(void *)) {
    DoublyLinkedList *linkedList = (DoublyLinkedList *) malloc(sizeof(DoublyLinkedList));
    linkedList->head = linkedList->tail = NULL;
    linkedList->freeFun = freeFun;
    linkedList->length = 0;

    return linkedList;
}









/** This function will take the linked list address, the item address, and the size of the item as a parameters,
    then it will add the item in the start of the linked list.
  * @param linkedList the linked list address
  * @param item the new item address
  * @param sizeOfItem the size of the new item in bytes
  */

void doublyLinkedListAddFirst(DoublyLinkedList *linkedList, void *item, int sizeOfItem) {
    if (linkedList == NULL) {
         fprintf(stderr,"Illegal argument, the linked list is NULL.");
        exit(-1);
    }

    Node *newNode = (Node *) malloc(sizeof(Node));
    DLLItem *newItem = (DLLItem *) malloc(sizeof(DLLItem));
    newItem->value = item;
    newItem->sizeOfItem = sizeOfItem;
    newNode->item = newItem;

    newNode->next = linkedList->head;
    newNode->prevNode = NULL;

    if (doublyLinkedListIsEmpty(linkedList))
        linkedList->tail = newNode;
    else
        linkedList->head->prevNode = newNode;

    linkedList->head = newNode;
    linkedList->length++;
}










/** This function will take the linked list address, the item address, and the size of the item as a parameters,
 * then it will add the item in the end of the linked list.
 * @param linkedList the linked list address
 * @param item the new item address
 * @param sizeOfItem the size of the new item in bytes
 */

void doublyLinkedListAddLast(DoublyLinkedList *linkedList, void *item, int sizeOfItem) {
    if (linkedList == NULL) {
         fprintf(stderr,"Illegal argument, the linked list is NULL.");
        exit(-1);
    }

    Node *newNode = (Node *) malloc(sizeof(Node));
    DLLItem *newItem = (DLLItem *) malloc(sizeof(DLLItem));
    newItem->value = item;
    newItem->sizeOfItem = sizeOfItem;
    newNode->item = newItem;

    newNode->next = NULL;

    if (doublyLinkedListIsEmpty(linkedList))
        linkedList->head = newNode;
    else
        linkedList->tail->next = newNode;

    newNode->prevNode = linkedList->tail;
    linkedList->tail = newNode;
    linkedList->length++;
}









/** This function will take the linked list address, item index, the item address, and the size of item as parameters,
 * then it will add the item in the passed index.
 * @param linkedList the linked list address
 * @param index the index of the new item
 * @param item the new item address
 * @param sizeOfItem the size of the new item in bytes
 */

void doublyLinkedListAddAtIndex(DoublyLinkedList *linkedList, int index, void *item, int sizeOfItem) {
    if (linkedList == NULL) {
         fprintf(stderr,"Illegal argument, the linked list is NULL.");
        exit(-1);
    } else if (index < 0 || index >= doublyLinkedListGetLength(linkedList)) {
         fprintf(stderr,"index is out range of the linked list.");
        exit(-1);
    }

    Node *newNode = (Node *) malloc(sizeof(Node));
    DLLItem *newItem = (DLLItem *) malloc(sizeof(DLLItem));
    newItem->value = item;
    newItem->sizeOfItem = sizeOfItem;
    newNode->item = newItem;

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









/** This function will take the linked list address, items array, the length of the array, and the size of items as parameters,
 * then it will copy the array item if the linked list in a new items addresses.
 * @param linkedList the linked list address
 * @param items the new items array address
 * @param itemsLength the length of the new items array
 * @param sizeOfItem the size of the new items in bytes
 */

void doublyLinkedListAddAll(DoublyLinkedList *linkedList, void **items, int itemsLength, int sizeOfItem) {
    if (linkedList == NULL) {
         fprintf(stderr,"Illegal argument, the linked list is NULL.");
        exit(-1);
    }

    for (int i = 0; i < itemsLength; i++)
        doublyLinkedListAddLast(linkedList, items[i], sizeOfItem);

}









/** This function will take the linked list address as a parameter,
 * then it will delete and free the first element from the linked list.
 * @param linkedList the linked list address
 */

void doublyLinkedListDeleteFirst(DoublyLinkedList *linkedList) {

    if (linkedList == NULL) {
         fprintf(stderr,"Illegal argument, the linked list is NULL.");
        exit(-1);
    } else if (doublyLinkedListIsEmpty(linkedList)) {
         fprintf(stderr,"linked list is empty.");
        exit(-1);
    }

    Node *nodeToFree = linkedList->head;
    if (linkedList->head == linkedList->tail) {
        linkedList->head = linkedList->tail = NULL;
    } else {
        linkedList->head = linkedList->head->next;
        linkedList->head->prevNode = NULL;
    }

    linkedList->length--;
    dLinkedListDestroyItem(nodeToFree->item, linkedList->freeFun);
    free(nodeToFree);

}










/** This function will take the linked list address as a parameter,
 * then it will delete and free only the node without the item of the first element from the linked list.
 * @param linkedList the linked list address
 */

void doublyLinkedListDeleteFirstWtFr(DoublyLinkedList *linkedList) {

    if (linkedList == NULL) {
         fprintf(stderr,"Illegal argument, the linked list is NULL.");
        exit(-1);
    } else if (doublyLinkedListIsEmpty(linkedList)) {
         fprintf(stderr,"linked list is empty.");
        exit(-1);
    }

    Node *nodeToFree = linkedList->head;
    if (linkedList->head == linkedList->tail) {
        linkedList->head = linkedList->tail = NULL;
    } else {
        linkedList->head = linkedList->head->next;
        linkedList->head->prevNode = NULL;
    }

    linkedList->length--;
    free(nodeToFree->item);
    free(nodeToFree);

}









/** This function will take the linked list address as a parameter,
    then it will delete and free the last element from the linked list.
 * @param linkedList the linked list address
 */

void doublyLinkedListDeleteLast(DoublyLinkedList *linkedList) {

    if (linkedList == NULL) {
         fprintf(stderr,"Illegal argument, the linked list is NULL.");
        exit(-1);
    } else if (doublyLinkedListIsEmpty(linkedList)) {
         fprintf(stderr,"linked list is empty.");
        exit(-1);
    }

    Node *nodeToFree = linkedList->tail;
    if (linkedList->head == linkedList->tail)
        linkedList->head = linkedList->tail = NULL;
    else {
        linkedList->tail = nodeToFree->prevNode;
        linkedList->tail->next = NULL;
    }

    linkedList->length--;
    dLinkedListDestroyItem(nodeToFree->item, linkedList->freeFun);
    free(nodeToFree);
}









/** This function will take the linked list address as a parameter,
    then it will delete and free only the node without the item of the last element from the linked list.
 * @param linkedList the linked list address
 */

void doublyLinkedListDeleteLastWtFr(DoublyLinkedList *linkedList) {

    if (linkedList == NULL) {
         fprintf(stderr,"Illegal argument, the linked list is NULL.");
        exit(-1);
    } else if (doublyLinkedListIsEmpty(linkedList)) {
         fprintf(stderr,"linked list is empty.");
        exit(-1);
    }

    Node *nodeToFree = linkedList->tail;
    if (linkedList->head == linkedList->tail)
        linkedList->head = linkedList->tail = NULL;
    else {
        linkedList->tail = nodeToFree->prevNode;
        linkedList->tail->next = NULL;
    }

    linkedList->length--;
    free(nodeToFree->item);
    free(nodeToFree);

}









/** This function will take the linked list address, and the index as parameters,
    then it will delete the item in this index.
 * If the index is out of the linked list rang then the program will be terminated.
 * @param linkedList the linked list address
 * @param index the index of the item that wanted to be deleted
 */

void doublyLinkedListDeleteAtIndex(DoublyLinkedList *linkedList, int index) {
    if (linkedList == NULL) {
         fprintf(stderr,"Illegal argument, the linked list is NULL.");
        exit(-1);
    } else if (index < 0 || index >= doublyLinkedListGetLength(linkedList)) {
         fprintf(stderr,"index is out range of the linked list.");
        exit(-1);
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
        dLinkedListDestroyItem(currentNode->item, linkedList->freeFun);
        free(currentNode);
    }

}









/** This function will take the linked list address, and the index as parameters,
    then it will delete and free only the node without the item of the item in this index.
 * If the index is out of the linked list rang then the program will be terminated.
 * @param linkedList the linked list address
 * @param index the index of the item that want to be deleted
 */

void doublyLinkedListDeleteAtIndexWtFr(DoublyLinkedList *linkedList, int index) {
    if (linkedList == NULL) {
         fprintf(stderr,"Illegal argument, the linked list is NULL.");
        exit(-1);
    } else if (index < 0 || index >= doublyLinkedListGetLength(linkedList)) {
         fprintf(stderr,"index is out range of the linked list.");
        exit(-1);
    }

    Node *currentNode = linkedList->head;
    for (int i = 0; i < index; i++)
        currentNode = currentNode->next;

    if (currentNode == linkedList->head) //if the index == 0.
        doublyLinkedListDeleteFirstWtFr(linkedList);
    else if (currentNode == linkedList->tail) //if the index = length - 1.
        doublyLinkedListDeleteLastWtFr(linkedList);
    else {
        currentNode->prevNode->next = currentNode->next;
        currentNode->next->prevNode = currentNode->prevNode;

        linkedList->length--;
        free(currentNode->item);
        free(currentNode);

    }

}










/** This function will take the linked list address, the item address, and the comparator function as parameters, then
    then it will return 1 if the item is in the list other wise it will return zero (0).
 *The function will use the comparator function to know if the two items are equivalent or not.
 * @param linkedList the linked list address
 * @param item the item address that has the same item as the wanted one
 * @param comparator the comparator function address
 * @return it will return one if the item is in the linked list, other wise it will return zero
 */

int doublyLinkedListContains(DoublyLinkedList *linkedList, void *item,
                             int (*comparator)(const void *, const void *)) {

    if (linkedList == NULL) {
         fprintf(stderr,"Illegal argument, the linked list is NULL.");
        exit(-1);
    } else if (comparator == NULL) {
         fprintf(stderr,"Illegal argument, the comparator function is NULL.");
        exit(-1);
    }

    Node *currentNode = linkedList->head;

    while (currentNode != NULL) {
        // if the comparator function returned zero then the two items are equal.
        if (comparator(currentNode->item->value, item) == 0)
            return 1;

        currentNode = currentNode->next;
    }

    return 0;
}










/** This function will take the linked list address, the item address, adn the comparator function as a parameters,
    then it will return the index of the given item, other wise it will return minus one (-1) .
 * The function will use the comparator function to know if the two items are equivalent or not.
 * @param linkedList the linked list address
 * @param item the item address the has the same item as the wanted one
 * @param comparator the comparator function address
 * @return it will return the index of the item if found, other wise it will return -1
 */

int doublyLinkedListGetIndex(DoublyLinkedList *linkedList, void *item,
                             int (*comparator)(const void *, const void *)) {

    if (linkedList == NULL) {
         fprintf(stderr,"Illegal argument, the linked list is NULL.");
        exit(-1);
    } else if (comparator == NULL) {
         fprintf(stderr,"Illegal argument, the comparator function is NULL.");
        exit(-1);
    }

    Node *currentNode = linkedList->head;

    for (int index = 0; currentNode != NULL; currentNode = currentNode->next, index++) {
        // if the comparator function returned zero then the two items are equal.
        if (comparator(currentNode->item->value, item) == 0)
            return index;

    }

    return -1;

}









/** This function will take the linked list address as a parameter,
    then it will return the first item in the list.
 * Note: if the linked list is empty the function will return NULL.
 * @param linkedList the linked list address
 * @return it will return the first item in the linked list
 */

void *doublyLinkedListGetFirst(DoublyLinkedList *linkedList) {

    if (linkedList == NULL) {
         fprintf(stderr,"Illegal argument, the linked list is NULL.");
        exit(-1);
    }

    return linkedList->head->item->value;

}








/** This function will take the linked list address as a parameter,
    then it will return the last item in the list.
 * Note: if the linked list is empty the function will return NULL.
 * @param linkedList the linked list address
 * @return it will return the last item in the linked list
 */

void *doublyLinkedListGetLast(DoublyLinkedList *linkedList) {

    if (linkedList == NULL) {
         fprintf(stderr,"Illegal argument, the linked list is NULL.");
        exit(-1);
    }

    return linkedList->tail->item->value;
}








/** This function will take the linked list address, the item address, and the comparator function as a parameters,
    then it will return the item from the list if found, other wise it will return NULL.
 * The function will use the comparator function to know if the two items are equivalent or not.
 * @param linkedList the linked list address
 * @param item the item address that hash the same item of the wanted one
 * @param comparator the comparator function address
 * @return it will return the item address if found, other wise it will return NULL
 */

void *doublyLinkedListGetItem(DoublyLinkedList *linkedList, void *item,
                              int (*comparator)(const void *, const void *)) {

    if (linkedList == NULL) {
         fprintf(stderr,"Illegal argument, the linked list is NULL.");
        exit(-1);
    } else if (comparator == NULL) {
         fprintf(stderr,"Illegal argument, the comparator function is NULL.");
        exit(-1);
    }

    Node *currentNode = linkedList->head;

    while (currentNode != NULL) {
        // if the comparator function returned zero then the two items are equal.
        if (comparator(currentNode->item->value, item) == 0)
            return currentNode->item->value;

        currentNode = currentNode->next;
    }

    return NULL;
}








/** This function will take the linked list address, and the index as parameters,
    then it will return the item in the given index.
 * If the index is out of the linked list range the program will terminate.
 * @param linkedList the linked list address
 * @param index the index of the wanted item
 * @return it will return the item in the provided index
 */

void *doublyLinkedListGet(DoublyLinkedList *linkedList, int index) {

    if (linkedList == NULL) {
         fprintf(stderr,"Illegal argument, the linked list is NULL.");
        exit(-1);
    } else if (index < 0 || index >= doublyLinkedListGetLength(linkedList)) {
         fprintf(stderr,"index is out range of the linked list.");
        exit(-1);
    }

    Node *currentNode = linkedList->head;
    for (int i = 0; i < index; i++)
        currentNode = currentNode->next;

    return currentNode->item->value;

}









/** This function will take the linked list address as a parameter,
    then it will return a void pointer to an array consist of the items in the linked list.
 * The items in the array doesn't share the same address in the linked list items.
 * @param linkedList the linked list address
 * @return it will return a double void array that hash a copy of the items in the linked list
 */

void **doublyLinkedListToArray(DoublyLinkedList *linkedList) {
    if (linkedList == NULL) {
         fprintf(stderr,"Illegal argument, the linked list is NULL.");
        exit(-1);
    }

    void **array = (void **) malloc(sizeof(void *) * doublyLinkedListGetLength(linkedList));

    Node *currentNode = linkedList->head;
    for (int i = 0; i < doublyLinkedListGetLength(linkedList); i++) {
        array[i] = (void *) malloc(currentNode->item->sizeOfItem);
        memcpy(array[i], currentNode->item->value, currentNode->item->sizeOfItem);

        currentNode = currentNode->next;
    }

    return array;
}









/** This function will take the linked list address as a parameter,
    the it will return the number of items in the linked list.
 * @param linkedList the linked list address
 * @return it will return the number of items in the linked list
 */

int doublyLinkedListGetLength(DoublyLinkedList *linkedList) {

    if (linkedList == NULL) {
         fprintf(stderr,"Illegal argument, the linked list is NULL.");
        exit(-1);
    }

    return linkedList->length;
}









/** This function will take the linked list address as a parameter,
    then it will return one (1) if the linked list is empty, other wise it will return 0.
 * @param linkedList the linked list address
 * @return it will return one if the linked list is empty, other wise it will return zero
 */

int doublyLinkedListIsEmpty(DoublyLinkedList *linkedList) {

    if (linkedList == NULL) {
         fprintf(stderr,"Illegal argument, the linked list is NULL.");
        exit(-1);
    }

    return linkedList->head == NULL && linkedList->tail == NULL;
}








/** This method will take the linked list address, and the print function address as a parameter,
    then it will call thr print function and pass to it an item pointer to be printed.
 * @param linkedList the linked list address
 * @param printFun the print function address
 */

void printDoublyLinkedList(DoublyLinkedList *linkedList, void (*printFun) (const void *)) {
    Node *currentNode = linkedList->head;
    while (currentNode != NULL) {
        printFun(currentNode->item->value);
        currentNode = currentNode->next;
    }

}









/** This function will take the linked list address as a parameter,
    then it will delete and free all the items from the linked list.
 * @param linkedList the linked list address
 */

void doublyLinkedListClear(DoublyLinkedList *linkedList) {

    if (linkedList == NULL) {
         fprintf(stderr,"Illegal argument, the linked list is NULL.");
        exit(-1);
    }

    Node *currentNode = linkedList->head;
    Node *nodeToFree;

    while (currentNode != NULL) {
        nodeToFree = currentNode;
        currentNode = currentNode->next;

        dLinkedListDestroyItem(nodeToFree->item, linkedList->freeFun);
        free(nodeToFree);
    }

    linkedList->head = linkedList->tail = NULL;
    linkedList->length = 0;
}










/** This function will take the linked list address as a parameter,
    then it will destroy and free the linked list and all it's nodes.
 * @param linkedList the linked list address
 */

void destroyDoublyLinkedList(DoublyLinkedList *linkedList) {

    doublyLinkedListClear(linkedList);
    free(linkedList);

}







/** This function will take the item address, and the free function address as a parameters,
 * then it will free the item container and it's item.
 * Note: this function should only be called from the doubly linked list functions.
 * @param item the item container address
 * @param freeFun the free item function address
 */

void dLinkedListDestroyItem(DLLItem *item, void (*freeFun)(void *)) {
    freeFun(item->value);
    free(item);
}