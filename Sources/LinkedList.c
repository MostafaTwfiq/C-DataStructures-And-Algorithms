#include "../Headers/LinkedList.h"



typedef struct Node {
    void *item; //void pointer so the node be generic.
    struct Node *next; // a pointer to the next node.
} Node;




/** This function will allocate a new linked list in the memory, setup it's fields and return it.
 * @param sizeOfType */

LinkedList *linkedListInitialization(int sizeOfType) {
    LinkedList *linkedList = (LinkedList *) malloc(sizeof(LinkedList));
    linkedList->head = linkedList->tail = NULL;
    linkedList->sizeOfType = sizeOfType;
    linkedList->length = 0;

    return linkedList;
}




/** This function will take the linked list address and the item address as a parameters,
    then it will add the item in the start of the linked list.
  * @param linkedList
  * @param item */

void linkedListAddFirst(LinkedList *linkedList, void *item) {
    if (linkedList == NULL) {
         fprintf(stderr,"Illegal argument, the linked list is NULL.");
        exit(-1);
    }

    Node *newNode = (Node *) malloc(sizeof(Node));
    newNode->item = item;

    newNode->next = linkedList->head;

    if (linkedListIsEmpty(linkedList))
        linkedList->tail = newNode;

    linkedList->head = newNode;
    linkedList->length++;
}




/** This function will take the linked list address and the item address as a parameters,
 * then it will add the item in the end of the linked list.
 * @param linkedList
 * @param item */

void linkedListAddLast(LinkedList *linkedList, void *item) {
    if (linkedList == NULL) {
         fprintf(stderr,"Illegal argument, the linked list is NULL.");
        exit(-1);
    }

    Node *newNode = (Node *) malloc(sizeof(Node));
    newNode->item = item;

    newNode->next = NULL;

    if (linkedListIsEmpty(linkedList))
        linkedList->head = newNode;
    else
        linkedList->tail->next = newNode;

    linkedList->tail = newNode;
    linkedList->length++;
}




/** This function will take the linked list address, item index, and the item address  the a parameters,
 * then it will add the item in the passed index.
 * @param linkedList
 * @param index
 * @param item
 */

void linkedListAddAtIndex(LinkedList *linkedList, int index, void *item) {
    if (linkedList == NULL) {
         fprintf(stderr,"Illegal argument, the linked list is NULL.");
        exit(-1);
    } else if (index < 0 || index >= linkedListGetLength(linkedList)) {
         fprintf(stderr,"index is out range of the linked list.");
        exit(-1);
    }

    Node *newNode = (Node *) malloc(sizeof(Node));
    newNode->item = item;

    Node *currentNode = linkedList->head;
    Node *prevNode = NULL;
    while (index-- != 0) {
        prevNode = currentNode;
        currentNode = currentNode->next;
    }

    if (prevNode == NULL) {
        newNode->next = currentNode;
        linkedList->head = newNode;
    } else {
        prevNode->next = newNode;
        newNode->next = currentNode;
    }

    linkedList->length++;
}




/** This function will take the linked list address, items array, and the length of the array as parameters,
 * then it will copy the array item if the linked list in a new items addresses.
 * @param linkedList
 * @param items
 * @param itemsLength
 */

void linkedListAddAll(LinkedList *linkedList, void *items, int itemsLength) {
    if (linkedList == NULL) {
         fprintf(stderr,"Illegal argument, the linked list is NULL.");
        exit(-1);
    }

    for (int i = 0; i < itemsLength; i++) {
        void *item = (void *) malloc(linkedList->sizeOfType);
        memcpy(item, (items + i * linkedList->sizeOfType), linkedList->sizeOfType);

        linkedListAddLast(linkedList, item);
    }

}




/** This function will take the linked list address as a parameter,
 * then it will delete and free the first element from the linked list.
 * @param linkedList
 */

void linkedListDeleteFirst(LinkedList *linkedList) {

    if (linkedList == NULL) {
         fprintf(stderr,"Illegal argument, the linked list is NULL.");
        exit(-1);
    } else if (linkedListIsEmpty(linkedList)) {
         fprintf(stderr,"linked list is empty.");
        exit(-1);
    }

    Node *nodeToFree = linkedList->head;
    if (linkedList->head == linkedList->tail) {
        linkedList->tail = NULL;
    }

    linkedList->head = linkedList->head->next;

    linkedList->length--;
    free(nodeToFree->item);
    free(nodeToFree);
}




/** This function will take the linked list address as a parameter,
 * then it will delete and free only the node without the item of the first element from the linked list.
 * @param linkedList
 */

void linkedListDeleteFirstWtFr(LinkedList *linkedList) {

    if (linkedList == NULL) {
         fprintf(stderr,"Illegal argument, the linked list is NULL.");
        exit(-1);
    } else if (linkedListIsEmpty(linkedList)) {
         fprintf(stderr,"linked list is empty.");
        exit(-1);
    }

    Node *nodeToFree = linkedList->head;
    if (linkedList->head == linkedList->tail) {
        linkedList->tail = NULL;
    }

    linkedList->head = linkedList->head->next;

    linkedList->length--;
    free(nodeToFree);
}




/** This function will take the linked list address as a parameter,
    then it will delete and free the last element from the linked list.
 * @param linkedList
 */

void linkedListDeleteLast(LinkedList *linkedList) {

    if (linkedList == NULL) {
         fprintf(stderr,"Illegal argument, the linked list is NULL.");
        exit(-1);
    } else if (linkedListIsEmpty(linkedList)) {
         fprintf(stderr,"linked list is empty.");
        exit(-1);
    }

    Node *currentNode = linkedList->head;
    Node *prevNode = NULL;
    while (currentNode->next != NULL) {
        prevNode = currentNode;
        currentNode = currentNode->next;
    }

    if (prevNode == NULL)
        linkedList->head = NULL;
    else
        prevNode->next = NULL;

    linkedList->tail = prevNode;

    linkedList->length--;
    free(currentNode->item);
    free(currentNode);
}




/** This function will take the linked list address as a parameter,
    then it will delete and free only the node without the item of the last element from the linked list.
 * @param linkedList
 */

void linkedListDeleteLastWtFr(LinkedList *linkedList) {

    if (linkedList == NULL) {
         fprintf(stderr,"Illegal argument, the linked list is NULL.");
        exit(-1);
    } else if (linkedListIsEmpty(linkedList)) {
         fprintf(stderr,"linked list is empty.");
        exit(-1);
    }

    Node *currentNode = linkedList->head;
    Node *prevNode = NULL;
    while (currentNode->next != NULL) {
        prevNode = currentNode;
        currentNode = currentNode->next;
    }

    if (prevNode == NULL)
        linkedList->head = NULL;
    else
        prevNode->next = NULL;

    linkedList->tail = prevNode;

    linkedList->length--;
    free(currentNode);
}





/** This function will take the linked list address, and the index as parameters,
    then it will delete the item in this index.
 * If the index is out of the linked list rang then the program will be terminated.
 * @param linkedList
 * @param index
 */

void linkedListDeleteAtIndex(LinkedList *linkedList, int index) {
    if (linkedList == NULL) {
         fprintf(stderr,"Illegal argument, the linked list is NULL.");
        exit(-1);
    } else if (index < 0 || index >= linkedListGetLength(linkedList)) {
         fprintf(stderr,"index is out range of the linked list.");
        exit(-1);
    }

    Node *currentNode = linkedList->head;
    Node *prevNode = NULL;
    for (int i = 0; i < index; i++) {
        prevNode = currentNode;
        currentNode = currentNode->next;
    }

    if (currentNode == linkedList->head)
        linkedListDeleteFirst(linkedList);
    else if (currentNode == linkedList->tail)
        linkedListDeleteLast(linkedList);
    else {
        prevNode->next = currentNode->next;

        linkedList->length--;
        free(currentNode->item);
        free(currentNode);
    }

}




/** This function will take the linked list address, and the index as parameters,
    then it will delete and free only the node without the item of the item in this index.
 * If the index is out of the linked list rang then the program will be terminated.
 * @param linkedList
 * @param index
 */

void linkedListDeleteAtIndexWtFr(LinkedList *linkedList, int index) {
    if (linkedList == NULL) {
         fprintf(stderr,"Illegal argument, the linked list is NULL.");
        exit(-1);
    } else if (index < 0 || index >= linkedListGetLength(linkedList)) {
         fprintf(stderr,"index is out range of the linked list.");
        exit(-1);
    }

    Node *currentNode = linkedList->head;
    Node *prevNode = NULL;
    for (int i = 0; i < index; i++) {
        prevNode = currentNode;
        currentNode = currentNode->next;
    }

    if (currentNode == linkedList->head)
        linkedListDeleteFirstWtFr(linkedList);
    else if (currentNode == linkedList->tail)
        linkedListDeleteLastWtFr(linkedList);
    else {
        prevNode->next = currentNode->next;

        linkedList->length--;
        free(currentNode);
    }

}






/** This function will take the linked list address, the item address, and the comparator function as parameters, then
    then it will return 1 if the item is in the list other wise it will return zero (0).
 *The function will use the comparator function to know if the two items are equivalent or not.
 * @param linkedList
 * @param item
 * @param comparator
 * @return
 */

int linkedListContains(LinkedList *linkedList, void *item,
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
        if (comparator(currentNode->item, item) == 0)
            return 1;

        currentNode = currentNode->next;
    }

    return 0;
}




/** This function will take the linked list address, the item address, adn the comparator function as a parameters,
    then it will return the index of the given item, other wise it will return minus one (-1) .
 * The function will use the comparator function to know if the two items are equivalent or not.
 * @param linkedList
 * @param item
 * @param comparator
 * @return
 */

int linkedListGetIndex(LinkedList *linkedList, void *item,
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
        if (comparator(currentNode->item, item) == 0)
            return index;

    }

    return -1;
}




/** This function will take the linked list address as a parameter,
    then it will return the first item in the list.
 * Note: if the linked list is empty the function will return NULL.
 * @param linkedList
 * @return
 */

void *linkedListGetFirst(LinkedList *linkedList) {

    if (linkedList == NULL) {
         fprintf(stderr,"Illegal argument, the linked list is NULL.");
        exit(-1);
    }

    return linkedList->head->item;
}




/** This function will take the linked list address as a parameter,
    then it will return the last item in the list.
 * Note: if the linked list is empty the function will return NULL.
 * @param linkedList
 * @return
 */

void *linkedListGetLast(LinkedList *linkedList) {

    if (linkedList == NULL) {
         fprintf(stderr,"Illegal argument, the linked list is NULL.");
        exit(-1);
    }

    return linkedList->tail->item;
}




/** This function will take the linked list address, the item address, and the comparator function as a parameters,
    then it will return the item from the list if found, other wise it will return NULL.
 * The function will use the comparator function to know if the two items are equivalent or not.
 * @param linkedList
 * @param item
 * @param comparator
 * @return
 */

void *linkedListGetItem(LinkedList *linkedList, void *item,
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
        if (comparator(currentNode->item, item) == 0)
            return currentNode->item;

        currentNode = currentNode->next;
    }

    return NULL;
}




/** This function will take the linked list address, and the index as parameters,
    then it will return the item in the given index.
 * If the index is out of the linked list range the program will terminate.
 * @param linkedList
 * @param index
 * @return
 */

void *linkedListGet(LinkedList *linkedList, int index) {

    if (linkedList == NULL) {
         fprintf(stderr,"Illegal argument, the linked list is NULL.");
        exit(-1);
    } else if (index < 0 || index >= linkedListGetLength(linkedList)) {
         fprintf(stderr,"index is out range of the linked list.");
        exit(-1);
    }

    Node *currentNode = linkedList->head;
    for (int i = 0; i < index; i++)
        currentNode = currentNode->next;

    return currentNode->item;
}




/** This function will take the linked list address as a parameter,
    then it will return a void pointer to an array consist of the items in the linked list.
 * The items in the array doesn't share the same address in the linked list items.
 * @param linkedList
 * @return
 */

void *linkedListToArray(LinkedList *linkedList) {
    if (linkedList == NULL) {
         fprintf(stderr,"Illegal argument, the linked list is NULL.");
        exit(-1);
    }

    void *array = (void *) malloc(linkedList->sizeOfType * linkedListGetLength(linkedList));

    Node *currentNode = linkedList->head;
    for (int i = 0; i < linkedListGetLength(linkedList); i++) {
        memcpy(array + i * linkedList->sizeOfType, currentNode->item, linkedList->sizeOfType);

        currentNode = currentNode->next;
    }

    return array;
}




/** This function will take the linked list address as a parameter,
    the it will return the number of items in the linked list.
 * @param linkedList
 * @return
 */

int linkedListGetLength(LinkedList *linkedList) {

    if (linkedList == NULL) {
         fprintf(stderr,"Illegal argument, the linked list is NULL.");
        exit(-1);
    }

    return linkedList->length;
}




/** This function will take the linked list address as a parameter,
    then it will return one (1) if the linked list is empty, other wise it will return 0.
 * @param linkedList
 * @return
 */

int linkedListIsEmpty(LinkedList *linkedList) {

    if (linkedList == NULL) {
         fprintf(stderr,"Illegal argument, the linked list is NULL.");
        exit(-1);
    }

    return linkedList->head == NULL && linkedList->tail == NULL;
}




/** This method will take the linked list address, and the print function address, as a parameter,
    then it will call thr print function and pass to it an item pointer to be printed.
 * @param linkedList
 * @param printFun
 */

void printLinkedList(LinkedList *linkedList, void (*printFun) (const void *)) {
    Node *currentNode = linkedList->head;
    while (currentNode != NULL) {
        printFun(currentNode->item);
        currentNode = currentNode->next;
    }

}




/** This function will take the linked list address as a parameter,
    then it will delete and free all the items from the linked list.
 * @param linkedList
 */

void linkedListClear(LinkedList *linkedList) {

    if (linkedList == NULL) {
         fprintf(stderr,"Illegal argument, the linked list is NULL.");
        exit(-1);
    }

    Node *currentNode = linkedList->head;
    Node *nodeToFree;

    while (currentNode != NULL) {
        nodeToFree = currentNode;
        currentNode = currentNode->next;

        free(nodeToFree->item);
        free(nodeToFree);
    }

    linkedList->head = linkedList->tail = NULL;
    linkedList->length = 0;
}




/** This function will take the linked list address as a parameter,
    then it will destroy and free the linked list and all it's nodes.
 * @param linkedList
 */

void destroyLinkedList(LinkedList *linkedList) {

    if (linkedList == NULL) {
         fprintf(stderr,"Illegal argument, the linked list is NULL.");
        exit(-1);
    }

    Node *currentNode = linkedList->head;
    Node *nodeToFree;

    while (currentNode != NULL) {
        nodeToFree = currentNode;
        currentNode = currentNode->next;

        free(nodeToFree->item);
        free(nodeToFree);
    }

    free(linkedList);

}
