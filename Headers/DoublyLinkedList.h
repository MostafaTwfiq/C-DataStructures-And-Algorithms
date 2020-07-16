#ifndef C_DATASTRUCTURES_DOUBLYLINKEDLIST_H
#define C_DATASTRUCTURES_DOUBLYLINKEDLIST_H
#include "Utils.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef struct DoublyLinkedList {
    struct Node *head;
    struct Node *tail;
    int length;
    void (*freeFun)(void *);
    int (*comparator)(const void *, const void *);
} DoublyLinkedList;


DoublyLinkedList *
doublyLinkedListInitialization(void (*freeFun)(void *), int (*comparator)(const void *, const void *));

void doublyLinkedListAddFirst(DoublyLinkedList *linkedList, void *item);

void doublyLinkedListAddLast(DoublyLinkedList *linkedList, void *item);

void doublyLinkedListAddAtIndex(DoublyLinkedList *linkedList, int index, void *item);

void doublyLinkedListAddAll(DoublyLinkedList *linkedList, void **items, int itemsLength);

void doublyLinkedListDeleteFirst(DoublyLinkedList *linkedList);

void *doublyLinkedListDeleteFirstWtoFr(DoublyLinkedList *linkedList);

void doublyLinkedListDeleteLast(DoublyLinkedList *linkedList);

void *doublyLinkedListDeleteLastWtoFr(DoublyLinkedList *linkedList);

void doublyLinkedListDeleteAtIndex(DoublyLinkedList *linkedList, int index);

void *doublyLinkedListDeleteAtIndexWtoFr(DoublyLinkedList *linkedList, int index);

int doublyLinkedListContains(DoublyLinkedList *linkedList, void *item);

int doublyLinkedListGetIndex(DoublyLinkedList *linkedList, void *item);

void *doublyLinkedListGetItem(DoublyLinkedList *linkedList, void *item);

void *doublyLinkedListGetFirst(DoublyLinkedList *linkedList);

void *doublyLinkedListGetLast(DoublyLinkedList *linkedList);

void **doublyLinkedListToArray(DoublyLinkedList *linkedList);

void *doublyLinkedListGet(DoublyLinkedList *linkedList, int index);

int doublyLinkedListGetLength(DoublyLinkedList *linkedList);

int doublyLinkedListIsEmpty(DoublyLinkedList *linkedList);

void printDoublyLinkedList(DoublyLinkedList *linkedList, void (*printFun)(const void *));

void doublyLinkedListClear(DoublyLinkedList *linkedList);

void destroyDoublyLinkedList(DoublyLinkedList *linkedList);

#ifdef __cplusplus
}
#endif

#endif //C_DATASTRUCTURES_DOUBLYLINKEDLIST_H
