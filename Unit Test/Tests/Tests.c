#include "ListsTest/VectorTest/VectorTest.h"
#include "ListsTest/ArrayListTest/ArrayListTest.h"
#include "LinkedListsTest/LinkedListTest/LinkedListTest.h"
#include "LinkedListsTest/DoublyLinkedListTest/DoublyLinkedListTest.h"
#include "StacksTest/StackTest/StackTest.h"
#include "StacksTest/DLinkedListStackTest/DLinkedListStackTest.h"
#include "QueuesTest/QueueTest/QueueTest.h"


int main(void) {

    vectorUnitTest();
    arrayListUnitTest();
    linkedListUnitTest();
    doublyLinkedListUnitTest();
    stackUnitTest();
    doublyLinkedListStackUnitTest();
    queueUnitTest();

    return 0;

}

