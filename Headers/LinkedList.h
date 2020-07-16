#ifndef C_DATASTRUCTURES_LINKEDLIST_H
#define C_DATASTRUCTURES_LINKEDLIST_H
#include "Utils.h"


typedef struct LinkedList {
    struct Node *head;
    struct Node *tail;
    int length;
    void (*freeFun)(void *);
    int (*comparator)(const void *, const void *);
} LinkedList;


LinkedList *linkedListInitialization(void (*freeFun)(void *),  int (*comparator)(const void *, const void *));


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


void printLinkedList(LinkedList *linkedList, void (*printFun) (const void *));


void linkedListClear(LinkedList *linkedList);


void destroyLinkedList(LinkedList *linkedList);


#endif //C_DATASTRUCTURES_LINKEDLIST_H