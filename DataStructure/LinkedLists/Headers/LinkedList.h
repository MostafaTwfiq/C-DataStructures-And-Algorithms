#ifndef C_DATASTRUCTURES_LINKEDLIST_H
#define C_DATASTRUCTURES_LINKEDLIST_H

#ifdef __cplusplus
extern "C" {
#endif

/** @struct LinkedList
*  @brief This structure implements a basic generic LinkedList.
*  @var LinkedList::head
*  Member 'head' is a pointer to first node.
*  @var LinkedList::tail
*  Member 'tail' is as pointer to the end node.
*  @var LinkedList::length
*  Member 'length' holds the number of the nodes.
*  @var LinkedList::freeFun
*  Member 'freeFun' the freeing item function pointer
* @var LinkedList::comparator
* Member 'comparator' the items comparator function pointer
*/

typedef struct LinkedList {
    struct Node *head;
    struct Node *tail;
    int length;

    void (*freeFun)(void *);

    int (*comparator)(const void *, const void *);
} LinkedList;


LinkedList *linkedListInitialization(void (*freeFun)(void *), int (*comparator)(const void *, const void *));

void linkedListAddFirst(LinkedList *linkedList, void *item);

void linkedListAddLast(LinkedList *linkedList, void *item);

void linkedListAddAtIndex(LinkedList *linkedList, int index, void *item);

void linkedListAddAll(LinkedList *linkedList, void **items, int itemsLength);

void linkedListDeleteFirst(LinkedList *linkedList);

void *linkedListDeleteFirstWtoFr(LinkedList *linkedList);

void linkedListDeleteLast(LinkedList *linkedList);

void *linkedListDeleteLastWtoFr(LinkedList *linkedList);

void linkedListDeleteAtIndex(LinkedList *linkedList, int index);

void *linkedListDeleteAtIndexWtoFr(LinkedList *linkedList, int index);

int linkedListContains(LinkedList *linkedList, void *item);

int linkedListGetIndex(LinkedList *linkedList, void *item);

void *linkedListGetItem(LinkedList *linkedList, void *item);

void *linkedListGetFirst(LinkedList *linkedList);

void *linkedListGetLast(LinkedList *linkedList);

void **linkedListToArray(LinkedList *linkedList);

void *linkedListGet(LinkedList *linkedList, int index);

int linkedListGetLength(LinkedList *linkedList);

int linkedListIsEmpty(LinkedList *linkedList);

void printLinkedList(LinkedList *linkedList, void (*printFun)(const void *));

void linkedListClear(LinkedList *linkedList);

void destroyLinkedList(void *linkedList);

#ifdef __cplusplus
}
#endif

#endif //C_DATASTRUCTURES_LINKEDLIST_H