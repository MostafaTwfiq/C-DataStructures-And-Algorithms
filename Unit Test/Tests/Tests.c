#include "ListsTest/VectorTest/VectorTest.h"
#include "ListsTest/ArrayListTest/ArrayListTest.h"
#include "LinkedListsTest/LinkedListTest/LinkedListTest.h"
#include "LinkedListsTest/DoublyLinkedListTest/DoublyLinkedListTest.h"
#include "StacksTest/StackTest/StackTest.h"
#include "StacksTest/DLinkedListStackTest/DLinkedListStackTest.h"
#include "QueuesTest/QueueTest/QueueTest.h"
#include "QueuesTest/StackQueueTest/StackQueueTest.h"
#include "QueuesTest/LinkedListQueueTest/LinkedListQueueTest.h"
#include "QueuesTest/PriorityQueueTest/PriorityQueueTest.h"


int main(void) {

    vectorUnitTest();
    arrayListUnitTest();
    linkedListUnitTest();
    doublyLinkedListUnitTest();
    stackUnitTest();
    doublyLinkedListStackUnitTest();
    queueUnitTest();
    stackQueueUnitTest();
    linkedListQueueUnitTest();
    priorityQueueUnitTest();

    return 0;

}

