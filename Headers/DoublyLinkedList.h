#ifndef C_DATASTRUCTURES_DOUBLYLINKEDLIST_H
#define C_DATASTRUCTURES_DOUBLYLINKEDLIST_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>


typedef struct DoublyLinkedList {
    struct Node *head;
    struct Node *tail;
    int sizeOfType; //this field will be useful to know the size of the items in the linked list.
    int length;
} DoublyLinkedList;



DoublyLinkedList *doublyLinkedListInitialization(int sizeOfType);


void doublyLinkedListAddFirst(DoublyLinkedList *linkedList, void *item);


void doublyLinkedListAddLast(DoublyLinkedList *linkedList, void *item);


void doublyLinkedListAddAtIndex(DoublyLinkedList *linkedList, int index, void *item);


void doublyLinkedListDeleteFirst(DoublyLinkedList *linkedList);


void doublyLinkedListDeleteLast(DoublyLinkedList *linkedList);


void doublyLinkedListDeleteAtIndex(DoublyLinkedList *linkedList, int index);


int doublyLinkedListContains(DoublyLinkedList *linkedList, void *item, int (*comparator)(const void *, const void *));


int doublyLinkedListGetIndex(DoublyLinkedList *linkedList, void *item, int (*comparator)(const void *, const void *));


void *doublyLinkedListGetItem(DoublyLinkedList *linkedList, void *item, int (*comparator)(const void *, const void *));


void *doublyLinkedListGetFirst(DoublyLinkedList *linkedList);


void *doublyLinkedListGetLast(DoublyLinkedList *linkedList);


void *doublyLinkedListToArray(DoublyLinkedList *linkedList);


void *doublyLinkedListGet(DoublyLinkedList *linkedList, int index);


int doublyLinkedListGetLength(DoublyLinkedList *linkedList);


int doublyLinkedListIsEmpty(DoublyLinkedList *linkedList);


void printDoublyLinkedList(DoublyLinkedList *linkedList, void (*printFun) (const void *));


void doublyLinkedListClear(DoublyLinkedList *linkedList);


void destroyDoublyLinkedList(DoublyLinkedList *linkedList);

#endif //C_DATASTRUCTURES_DOUBLYLINKEDLIST_H
