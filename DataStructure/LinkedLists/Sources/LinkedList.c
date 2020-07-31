#include "../Headers/LinkedList.h"
#include "../../../System/Utils.h"
#include "../../../Unit Test/CuTest/CuTest.h"




typedef struct Node {
    void *item; //void pointer so the node be generic.
    struct Node *next; // a pointer to the next node.
} Node;




/** This function will allocate a new linked list in the memory, setup it's fields and return it.
 * @param freeFun the free function address that will be called to free the items in the linked list
 * @param comparator the comparator function address, that will be called to compare two items
*/

LinkedList *linkedListInitialization(void (*freeFun)(void *),  int (*comparator)(const void *, const void *)) {

    if (freeFun == NULL) {
        fprintf(stderr, INVALID_ARG_MESSAGE, "free function pointer", "linked list data structure");
        #ifdef CU_TEST_H
     		DUMMY_TEST_DATASTRUCTURE->errorCode = INVALID_ARG;
     		return NULL;
     	#else
     		exit(INVALID_ARG);
     	#endif

    }

    LinkedList *linkedList = (LinkedList *) malloc(sizeof(LinkedList));
    if (linkedList == NULL) {
        fprintf(stderr, FAILED_ALLOCATION_MESSAGE, "linked list", "linked list data structure");
        #ifdef CU_TEST_H
     		DUMMY_TEST_DATASTRUCTURE->errorCode = FAILED_ALLOCATION;
     		return NULL;
     	#else
     		exit(FAILED_ALLOCATION);
     	#endif

    }

    linkedList->head = linkedList->tail = NULL;
    linkedList->length = 0;
    linkedList->freeFun  = freeFun;
    linkedList->comparator = comparator;

    return linkedList;
}





/** This function will take the linked list address, and the item address as a parameters,
    then it will add the item in the start of the linked list.
  * @param linkedList the linked list address
  * @param item the new item address
  * */

void linkedListAddFirst(LinkedList *linkedList, void *item) {
    if (linkedList == NULL) {
        fprintf(stderr, NULL_POINTER_MESSAGE, "linked list pointer", "linked list data structure");
        #ifdef CU_TEST_H
     		DUMMY_TEST_DATASTRUCTURE->errorCode = NULL_POINTER;
     		return;
     	#else
     		exit(NULL_POINTER);
     	#endif

    } else if (item == NULL) {
        fprintf(stderr, INVALID_ARG_MESSAGE, "item pointer", "linked list data structure");
        #ifdef CU_TEST_H
     		DUMMY_TEST_DATASTRUCTURE->errorCode = INVALID_ARG;
     		return;
     	#else
     		exit(INVALID_ARG);
     	#endif

    }

    Node *newNode = (Node *) malloc(sizeof(Node));
    if (newNode == NULL) {
        fprintf(stderr, FAILED_ALLOCATION_MESSAGE, "new node", "linked list data structure");
        #ifdef CU_TEST_H
     		DUMMY_TEST_DATASTRUCTURE->errorCode = FAILED_ALLOCATION;
     		return;
     	#else
     		exit(FAILED_ALLOCATION);
     	#endif

    }

    newNode->item = item;

    newNode->next = linkedList->head;

    if (linkedListIsEmpty(linkedList))
        linkedList->tail = newNode;

    linkedList->head = newNode;
    linkedList->length++;

}




/** This function will take the linked list address, and the item address as a parameters,
 * then it will add the item in the end of the linked list.
 * @param linkedList the linked list address
 * @param item the new item address
 */

void linkedListAddLast(LinkedList *linkedList, void *item) {
    if (linkedList == NULL) {
        fprintf(stderr, NULL_POINTER_MESSAGE, "linked list pointer", "linked list data structure");
        #ifdef CU_TEST_H
     		DUMMY_TEST_DATASTRUCTURE->errorCode = NULL_POINTER;
     		return;
     	#else
     		exit(NULL_POINTER);
     	#endif

    } else if (item == NULL) {
        fprintf(stderr, INVALID_ARG_MESSAGE, "item pointer", "linked list data structure");
        #ifdef CU_TEST_H
     		DUMMY_TEST_DATASTRUCTURE->errorCode = INVALID_ARG;
     		return;
     	#else
     		exit(INVALID_ARG);
     	#endif

    }

    Node *newNode = (Node *) malloc(sizeof(Node));
    if (newNode == NULL) {
        fprintf(stderr, FAILED_ALLOCATION_MESSAGE, "new node", "linked list data structure");
        #ifdef CU_TEST_H
     		DUMMY_TEST_DATASTRUCTURE->errorCode = FAILED_ALLOCATION;
     		return;
     	#else
     		exit(FAILED_ALLOCATION);
     	#endif

    }

    newNode->item = item;

    newNode->next = NULL;

    if (linkedListIsEmpty(linkedList))
        linkedList->head = newNode;
    else
        linkedList->tail->next = newNode;

    linkedList->tail = newNode;
    linkedList->length++;
}




/** This function will take the linked list address, item index, and the item address as a parameters,
 * then it will add the item in the passed index.
 * @param linkedList the linked list address
 * @param index the index that the new item will be inserted in
 * @param item the new item address
 */

void linkedListAddAtIndex(LinkedList *linkedList, int index, void *item) {
    if (linkedList == NULL) {
        fprintf(stderr, NULL_POINTER_MESSAGE, "linked list pointer", "linked list data structure");
        #ifdef CU_TEST_H
     		DUMMY_TEST_DATASTRUCTURE->errorCode = NULL_POINTER;
     		return;
     	#else
     		exit(NULL_POINTER);
     	#endif

    } else if (item == NULL) {
        fprintf(stderr, INVALID_ARG_MESSAGE, "item pointer", "linked list data structure");
        #ifdef CU_TEST_H
     		DUMMY_TEST_DATASTRUCTURE->errorCode = INVALID_ARG;
     		return;
     	#else
     		exit(INVALID_ARG);
     	#endif

    } else if (index < 0 || index >= linkedListGetLength(linkedList)) {
        fprintf(stderr, OUT_OF_RANGE_MESSAGE, "linked list data structure");
        #ifdef CU_TEST_H
     		DUMMY_TEST_DATASTRUCTURE->errorCode = OUT_OF_RANGE;
     		return;
     	#else
     		exit(OUT_OF_RANGE);
     	#endif

    }

    Node *newNode = (Node *) malloc(sizeof(Node));
    if (newNode == NULL) {
        fprintf(stderr, FAILED_ALLOCATION_MESSAGE, "new node", "linked list data structure");
        #ifdef CU_TEST_H
     		DUMMY_TEST_DATASTRUCTURE->errorCode = FAILED_ALLOCATION;
     		return;
     	#else
     		exit(FAILED_ALLOCATION);
     	#endif

    }

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
 * Note: this function will add all the new items in the end of the linked list
 * @param linkedList the linked list address
 * @param items the items array represented as a double pointer array
 * @param itemsLength the length of the items array
 */

void linkedListAddAll(LinkedList *linkedList, void **items, int itemsLength) {
    if (linkedList == NULL) {
        fprintf(stderr, NULL_POINTER_MESSAGE, "linked list pointer", "linked list data structure");
        #ifdef CU_TEST_H
     		DUMMY_TEST_DATASTRUCTURE->errorCode = NULL_POINTER;
     		return;
     	#else
     		exit(NULL_POINTER);
     	#endif

    } else if (items == NULL) {
        fprintf(stderr, INVALID_ARG_MESSAGE, "items array pointer", "linked list data structure");
        #ifdef CU_TEST_H
     		DUMMY_TEST_DATASTRUCTURE->errorCode = INVALID_ARG;
     		return;
     	#else
     		exit(INVALID_ARG);
     	#endif

    }

    for (int i = 0; i < itemsLength; i++)
        linkedListAddLast(linkedList, items[i]);

}




/** This function will take the linked list address as a parameter,
 * then it will delete and free the first element from the linked list.
 * @param linkedList
 */

void linkedListDeleteFirst(LinkedList *linkedList) {

    if (linkedList == NULL) {
        fprintf(stderr, NULL_POINTER_MESSAGE, "linked list pointer", "linked list data structure");
        #ifdef CU_TEST_H
     		DUMMY_TEST_DATASTRUCTURE->errorCode = NULL_POINTER;
     		return;
     	#else
     		exit(NULL_POINTER);
     	#endif

    } else if (linkedListIsEmpty(linkedList)) {
        fprintf(stderr, EMPTY_DATA_STRUCTURE_MESSAGE, "linked list data structure");
        #ifdef CU_TEST_H
     		DUMMY_TEST_DATASTRUCTURE->errorCode = EMPTY_DATA_STRUCTURE;
     		return;
     	#else
     		exit(EMPTY_DATA_STRUCTURE);
     	#endif

    }

    Node *nodeToFree = linkedList->head;
    if (linkedList->head == linkedList->tail) {
        linkedList->tail = NULL;
    }

    linkedList->head = linkedList->head->next;

    linkedList->length--;
    linkedList->freeFun(nodeToFree->item);
    free(nodeToFree);

}




/** This function will take the linked list address as a parameter,
 * then it will delete and free only the node without the item of the first element from the linked list.
 * @param linkedList
 * @return it will return the deleted item pointer
 */

void *linkedListDeleteFirstWtoFr(LinkedList *linkedList) {

    if (linkedList == NULL) {
        fprintf(stderr, NULL_POINTER_MESSAGE, "linked list pointer", "linked list data structure");
        #ifdef CU_TEST_H
     		DUMMY_TEST_DATASTRUCTURE->errorCode = NULL_POINTER;
     		return NULL;
     	#else
     		exit(NULL_POINTER);
     	#endif

    } else if (linkedListIsEmpty(linkedList)) {
        fprintf(stderr, EMPTY_DATA_STRUCTURE_MESSAGE, "linked list data structure");
        #ifdef CU_TEST_H
     		DUMMY_TEST_DATASTRUCTURE->errorCode = EMPTY_DATA_STRUCTURE;
     		return NULL;
     	#else
     		exit(EMPTY_DATA_STRUCTURE);
     	#endif

    }

    Node *nodeToFree = linkedList->head;
    if (linkedList->head == linkedList->tail) {
        linkedList->tail = NULL;
    }

    linkedList->head = linkedList->head->next;

    linkedList->length--;
    void *returnItem = nodeToFree->item;
    free(nodeToFree);

    return returnItem;

}




/** This function will take the linked list address as a parameter,
    then it will delete and free the last element from the linked list.
 * @param linkedList
 */

void linkedListDeleteLast(LinkedList *linkedList) {

    if (linkedList == NULL) {
        fprintf(stderr, NULL_POINTER_MESSAGE, "linked list pointer", "linked list data structure");
        #ifdef CU_TEST_H
     		DUMMY_TEST_DATASTRUCTURE->errorCode = NULL_POINTER;
     		return;
     	#else
     		exit(NULL_POINTER);
     	#endif

    } else if (linkedListIsEmpty(linkedList)) {
        fprintf(stderr, EMPTY_DATA_STRUCTURE_MESSAGE, "linked list data structure");
        #ifdef CU_TEST_H
     		DUMMY_TEST_DATASTRUCTURE->errorCode = EMPTY_DATA_STRUCTURE;
     		return;
     	#else
     		exit(EMPTY_DATA_STRUCTURE);
     	#endif

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
    linkedList->freeFun(currentNode->item);
    free(currentNode);

}




/** This function will take the linked list address as a parameter,
    then it will delete and free only the node without the item of the last element from the linked list.
 * @param linkedList
 * @return it will return the deleted item pointer
 */

void *linkedListDeleteLastWtoFr(LinkedList *linkedList) {

    if (linkedList == NULL) {
        fprintf(stderr, NULL_POINTER_MESSAGE, "linked list pointer", "linked list data structure");
        #ifdef CU_TEST_H
     		DUMMY_TEST_DATASTRUCTURE->errorCode = NULL_POINTER;
     		return NULL;
     	#else
     		exit(NULL_POINTER);
     	#endif

    } else if (linkedListIsEmpty(linkedList)) {
        fprintf(stderr, EMPTY_DATA_STRUCTURE_MESSAGE, "linked list data structure");
        #ifdef CU_TEST_H
     		DUMMY_TEST_DATASTRUCTURE->errorCode = EMPTY_DATA_STRUCTURE;
     		return NULL;
     	#else
     		exit(EMPTY_DATA_STRUCTURE);
     	#endif

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
    void *returnItem = currentNode->item;
    free(currentNode);

    return returnItem;

}





/** This function will take the linked list address, and the index as parameters,
    then it will delete the item in this index.
 * If the index is out of the linked list rang then the program will be terminated.
 * @param linkedList
 * @param index
 */

void linkedListDeleteAtIndex(LinkedList *linkedList, int index) {
    if (linkedList == NULL) {
        fprintf(stderr, NULL_POINTER_MESSAGE, "linked list pointer", "linked list data structure");
        #ifdef CU_TEST_H
     		DUMMY_TEST_DATASTRUCTURE->errorCode = NULL_POINTER;
     		return;
     	#else
     		exit(NULL_POINTER);
     	#endif

    } else if (linkedListIsEmpty(linkedList)) {
        fprintf(stderr, EMPTY_DATA_STRUCTURE_MESSAGE, "linked list data structure");
        #ifdef CU_TEST_H
     		DUMMY_TEST_DATASTRUCTURE->errorCode = EMPTY_DATA_STRUCTURE;
     		return;
     	#else
     		exit(EMPTY_DATA_STRUCTURE);
     	#endif

    } else if (index < 0 || index >= linkedListGetLength(linkedList)) {
         fprintf(stderr, OUT_OF_RANGE_MESSAGE, "linked list data structure");
        #ifdef CU_TEST_H
     		DUMMY_TEST_DATASTRUCTURE->errorCode = OUT_OF_RANGE;
     		return;
     	#else
     		exit(OUT_OF_RANGE);
     	#endif

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
        linkedList->freeFun(currentNode->item);
        free(currentNode);
    }

}




/** This function will take the linked list address, and the index as parameters,
    then it will delete and free only the node without the item of the item in this index.
 * If the index is out of the linked list rang then the program will be terminated.
 * @param linkedList
 * @param index
 * @return it will return the deleted item pointer
 */

void *linkedListDeleteAtIndexWtoFr(LinkedList *linkedList, int index) {
    if (linkedList == NULL) {
        fprintf(stderr, NULL_POINTER_MESSAGE, "linked list pointer", "linked list data structure");
        #ifdef CU_TEST_H
     		DUMMY_TEST_DATASTRUCTURE->errorCode = NULL_POINTER;
     		return NULL;
     	#else
     		exit(NULL_POINTER);
     	#endif

    } else if (linkedListIsEmpty(linkedList)) {
        fprintf(stderr, EMPTY_DATA_STRUCTURE_MESSAGE, "linked list data structure");
        #ifdef CU_TEST_H
     		DUMMY_TEST_DATASTRUCTURE->errorCode = EMPTY_DATA_STRUCTURE;
     		return NULL;
     	#else
     		exit(EMPTY_DATA_STRUCTURE);
     	#endif

    } else if (index < 0 || index >= linkedListGetLength(linkedList)) {
        fprintf(stderr, OUT_OF_RANGE_MESSAGE, "linked list data structure");
        #ifdef CU_TEST_H
     		DUMMY_TEST_DATASTRUCTURE->errorCode = OUT_OF_RANGE;
     		return NULL;
     	#else
     		exit(OUT_OF_RANGE);
     	#endif

    }

    Node *currentNode = linkedList->head;
    Node *prevNode = NULL;
    for (int i = 0; i < index; i++) {
        prevNode = currentNode;
        currentNode = currentNode->next;
    }

    if (currentNode == linkedList->head)
        return linkedListDeleteFirstWtoFr(linkedList);
    else if (currentNode == linkedList->tail)
        return linkedListDeleteLastWtoFr(linkedList);
    else {
        prevNode->next = currentNode->next;

        linkedList->length--;
        void *returnItem = currentNode->item;
        free(currentNode);

        return returnItem;

    }

}






/** This function will take the linked list address, and the item address as parameters, then
    then it will return 1 if the item is in the list other wise it will return zero (0).
 *The function will use the comparator function to know if the two items are equivalent or not.
 * @param linkedList
 * @param item
 * @return
 */

int linkedListContains(LinkedList *linkedList, void *item) {

    if (linkedList == NULL) {
        fprintf(stderr, NULL_POINTER_MESSAGE, "linked list pointer", "linked list data structure");
        #ifdef CU_TEST_H
     		DUMMY_TEST_DATASTRUCTURE->errorCode = NULL_POINTER;
     		return -1;
     	#else
     		exit(NULL_POINTER);
     	#endif

    } else if (item == NULL) {
        fprintf(stderr, INVALID_ARG_MESSAGE, "item pointer", "linked list data structure");
        #ifdef CU_TEST_H
     		DUMMY_TEST_DATASTRUCTURE->errorCode = INVALID_ARG;
     		return -1;
     	#else
     		exit(INVALID_ARG);
     	#endif

    } else if (linkedList->comparator == NULL) {
        fprintf(stderr, INVALID_ARG_MESSAGE, "comparator function", "linked list data structure");
        #ifdef CU_TEST_H
            DUMMY_TEST_DATASTRUCTURE->errorCode = INVALID_ARG;
            return -1;
        #else
            exit(INVALID_ARG);
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
    then it will return the index of the given item, other wise it will return minus one (-1) .
 * The function will use the comparator function to know if the two items are equivalent or not.
 * @param linkedList
 * @param item
 * @return
 */

int linkedListGetIndex(LinkedList *linkedList, void *item) {

    if (linkedList == NULL) {
        fprintf(stderr, NULL_POINTER_MESSAGE, "linked list pointer", "linked list data structure");
        #ifdef CU_TEST_H
     		DUMMY_TEST_DATASTRUCTURE->errorCode = NULL_POINTER;
            return -1;
     	#else
     		exit(NULL_POINTER);
     	#endif

    } else if (item == NULL) {
        fprintf(stderr, INVALID_ARG_MESSAGE, "item pointer", "linked list data structure");
        #ifdef CU_TEST_H
     		DUMMY_TEST_DATASTRUCTURE->errorCode = INVALID_ARG;
     		return -1;
     	#else
     		exit(INVALID_ARG);
     	#endif

    } else if (linkedList->comparator == NULL) {
        fprintf(stderr, INVALID_ARG_MESSAGE, "comparator function", "linked list data structure");
        #ifdef CU_TEST_H
            DUMMY_TEST_DATASTRUCTURE->errorCode = INVALID_ARG;
            return -1;
        #else
            exit(INVALID_ARG);
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
    then it will return the first item in the list.
 * Note: if the linked list is empty the function will return NULL.
 * @param linkedList
 * @return
 */

void *linkedListGetFirst(LinkedList *linkedList) {

    if (linkedList == NULL) {
        fprintf(stderr, NULL_POINTER_MESSAGE, "linked list pointer", "linked list data structure");
        #ifdef CU_TEST_H
     		DUMMY_TEST_DATASTRUCTURE->errorCode = NULL_POINTER;
        return NULL;
     	#else
     		exit(NULL_POINTER);
     	#endif

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
        fprintf(stderr, NULL_POINTER_MESSAGE, "linked list pointer", "linked list data structure");
        #ifdef CU_TEST_H
     		DUMMY_TEST_DATASTRUCTURE->errorCode = NULL_POINTER;
            return NULL;
     	#else
     		exit(NULL_POINTER);
     	#endif

    }

    return linkedList->tail->item;

}




/** This function will take the linked list address, and the item address as a parameters,
    then it will return the item from the list if found, other wise it will return NULL.
 * The function will use the comparator function to know if the two items are equivalent or not.
 * @param linkedList
 * @param item
 * @return
 */

void *linkedListGetItem(LinkedList *linkedList, void *item) {

    if (linkedList == NULL) {
        fprintf(stderr, NULL_POINTER_MESSAGE, "linked list pointer", "linked list data structure");
        #ifdef CU_TEST_H
     		DUMMY_TEST_DATASTRUCTURE->errorCode = NULL_POINTER;
     		return NULL;
     	#else
     		exit(NULL_POINTER);
     	#endif

    } else if (item == NULL) {
        fprintf(stderr, INVALID_ARG_MESSAGE, "item pointer", "linked list data structure");
        #ifdef CU_TEST_H
     		DUMMY_TEST_DATASTRUCTURE->errorCode = INVALID_ARG;
     		return NULL;
     	#else
     		exit(INVALID_ARG);
     	#endif

    } else if (linkedList->comparator == NULL) {
        fprintf(stderr, INVALID_ARG_MESSAGE, "comparator function", "linked list data structure");
        #ifdef CU_TEST_H
            DUMMY_TEST_DATASTRUCTURE->errorCode = INVALID_ARG;
            return NULL;
        #else
            exit(INVALID_ARG);
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
    then it will return the item in the given index.
 * If the index is out of the linked list range the program will terminate.
 * @param linkedList
 * @param index
 * @return
 */

void *linkedListGet(LinkedList *linkedList, int index) {

    if (linkedList == NULL) {
        fprintf(stderr, NULL_POINTER_MESSAGE, "linked list pointer", "linked list data structure");
        #ifdef CU_TEST_H
     		DUMMY_TEST_DATASTRUCTURE->errorCode = NULL_POINTER;
     		return NULL;
     	#else
     		exit(NULL_POINTER);
     	#endif

    } else if (index < 0 || index >= linkedListGetLength(linkedList)) {
        fprintf(stderr, OUT_OF_RANGE_MESSAGE, "linked list data structure");
        #ifdef CU_TEST_H
     		DUMMY_TEST_DATASTRUCTURE->errorCode = OUT_OF_RANGE;
     		return NULL;
     	#else
     		exit(OUT_OF_RANGE);
     	#endif

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

void **linkedListToArray(LinkedList *linkedList) {
    if (linkedList == NULL) {
        fprintf(stderr, NULL_POINTER_MESSAGE, "linked list pointer", "linked list data structure");
        #ifdef CU_TEST_H
     		DUMMY_TEST_DATASTRUCTURE->errorCode = NULL_POINTER;
     		return NULL;
     	#else
     		exit(NULL_POINTER);
     	#endif

    }

    void **array = (void **) malloc(sizeof(void *) * linkedListGetLength(linkedList));
    if (array == NULL) {
        fprintf(stderr, FAILED_ALLOCATION_MESSAGE, "to array", "linked list data structure");
        #ifdef CU_TEST_H
     		DUMMY_TEST_DATASTRUCTURE->errorCode = FAILED_ALLOCATION;
     		return NULL;
     	#else
     		exit(FAILED_ALLOCATION);
     	#endif

    }

    Node *currentNode = linkedList->head;
    for (int i = 0; i < linkedListGetLength(linkedList); i++) {
        array[i] = currentNode->item;

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
        fprintf(stderr, NULL_POINTER_MESSAGE, "linked list pointer", "linked list data structure");
        #ifdef CU_TEST_H
     		DUMMY_TEST_DATASTRUCTURE->errorCode = NULL_POINTER;
     		return -1;
     	#else
     		exit(NULL_POINTER);
     	#endif

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
        fprintf(stderr, NULL_POINTER_MESSAGE, "linked list pointer", "linked list data structure");
        #ifdef CU_TEST_H
     		DUMMY_TEST_DATASTRUCTURE->errorCode = NULL_POINTER;
     		return -1;
     	#else
     		exit(NULL_POINTER);
     	#endif

    }

    return linkedList->head == NULL && linkedList->tail == NULL;
}




/** This method will take the linked list address, and the print function address, as a parameter,
    then it will call thr print function and pass to it an item pointer to be printed.
 * @param linkedList
 * @param printFun
 */

void printLinkedList(LinkedList *linkedList, void (*printFun) (const void *)) {

    if (linkedList == NULL) {
        fprintf(stderr, NULL_POINTER_MESSAGE, "linked list pointer", "linked list data structure");
        #ifdef CU_TEST_H
     		DUMMY_TEST_DATASTRUCTURE->errorCode = NULL_POINTER;
     		return;
     	#else
     		exit(NULL_POINTER);
     	#endif

    } else if (printFun == NULL) {
        fprintf(stderr, INVALID_ARG_MESSAGE, "print function pointer", "linked list data structure");
        #ifdef CU_TEST_H
     		DUMMY_TEST_DATASTRUCTURE->errorCode = INVALID_ARG;
     		return;
     	#else
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
    then it will delete and free all the items from the linked list.
 * @param linkedList
 */

void linkedListClear(LinkedList *linkedList) {

    if (linkedList == NULL) {
        fprintf(stderr, NULL_POINTER_MESSAGE, "linked list pointer", "linked list data structure");
        #ifdef CU_TEST_H
     		DUMMY_TEST_DATASTRUCTURE->errorCode = NULL_POINTER;
     		return;
     	#else
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
    then it will destroy and free the linked list and all it's nodes.
 * @param linkedList
 */

void destroyLinkedList(LinkedList *linkedList) {

    if (linkedList == NULL) {
        fprintf(stderr, NULL_POINTER_MESSAGE, "linked list pointer", "linked list data structure");
        #ifdef CU_TEST_H
            DUMMY_TEST_DATASTRUCTURE->errorCode = NULL_POINTER;
            return;
        #else
            exit(NULL_POINTER);
        #endif

    }

    linkedListClear(linkedList);
    free(linkedList);

}