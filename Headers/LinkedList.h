#ifndef C_DATASTRUCTURES_LINKEDLIST_H
#define C_DATASTRUCTURES_LINKEDLIST_H
#include "Utils.h"


typedef struct LinkedList {
    struct Node *head;
    struct Node *tail;
    int sizeOfType; //this field will be useful to know the size of the items in the linked list.
    int length;
} LinkedList;


LinkedList *linkedListInitialization(int sizeOfType);


void linkedListAddFirst(LinkedList *linkedList, void *item);


void linkedListAddLast(LinkedList *linkedList, void *item);


void linkedListAddAtIndex(LinkedList *linkedList, int index, void *item);


void linkedListDeleteFirst(LinkedList *linkedList);


void linkedListDeleteFirstWtFr(LinkedList *linkedList);


void linkedListDeleteLast(LinkedList *linkedList);


void linkedListDeleteLastWtFr(LinkedList *linkedList);


void linkedListDeleteAtIndex(LinkedList *linkedList, int index);


void linkedListDeleteAtIndexWtFr(LinkedList *linkedList, int index);


int linkedListContains(LinkedList *linkedList, void *item, int (*comparator)(const void *, const void *));


int linkedListGetIndex(LinkedList *linkedList, void *item, int (*comparator)(const void *, const void *));


void *linkedListGetItem(LinkedList *linkedList, void *item, int (*comparator)(const void *, const void *));


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