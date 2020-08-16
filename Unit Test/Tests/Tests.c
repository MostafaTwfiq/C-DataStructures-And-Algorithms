#include "DataStructuresTests/ListsTest/VectorTest/VectorTest.h"
#include "DataStructuresTests/ListsTest/ArrayListTest/ArrayListTest.h"
#include "DataStructuresTests/ListsTest/SetTest/SetTest.h"
#include "DataStructuresTests/LinkedListsTest/LinkedListTest/LinkedListTest.h"
#include "DataStructuresTests/LinkedListsTest/DoublyLinkedListTest/DoublyLinkedListTest.h"
#include "DataStructuresTests/StacksTest/StackTest/StackTest.h"
#include "DataStructuresTests/StacksTest/DLinkedListStackTest/DLinkedListStackTest.h"
#include "DataStructuresTests/QueuesTest/QueueTest/QueueTest.h"
#include "DataStructuresTests/QueuesTest/StackQueueTest/StackQueueTest.h"
#include "DataStructuresTests/QueuesTest/LinkedListQueueTest/LinkedListQueueTest.h"
#include "DataStructuresTests/QueuesTest/PriorityQueueTest/PriorityQueueTest.h"
#include "DataStructuresTests/QueuesTest/HeapPriorityQueueTest/HeapPriorityQueueTest.h"
#include "DataStructuresTests/DequesTest/DequeTest/DequeTest.h"
#include "DataStructuresTests/DequesTest/DoublyLinkedListDequeTest/DoublyLinkedListDequeTest.h"
#include "DataStructuresTests/MatricesTest/MatrixTest/MatrixTest.h"
#include "DataStructuresTests/PairsTest/PairTest/PairTest.h"
#include "DataStructuresTests/StringsTest/StringTest/StringTest.h"
#include "DataStructuresTests/TablesTest/HashMapTest/HashMapTest.h"
#include "DataStructuresTests/TablesTest/DounlyLinkedListHashMapTest/DoublyLinkedListHashMapTest.h"
#include "DataStructuresTests/TablesTest/HashSetTest/HashSetTest.h"
#include "DataStructuresTests/GraphsTest/DirectedGraphTest/DirectedGraphTest.h"
#include "DataStructuresTests/GraphsTest/UndirectedGraphTest/UndirectedGraphTest.h"
#include "DataStructuresTests/TreesTest/TrieTest/TrieTest.h"
#include "DataStructuresTests/TreesTest/RedBlackTreeTest/RedBlackTreeTest.h"
#include "DataStructuresTests/TreesTest/BinaryTreeTest/BinaryTreeTest.h"
#include "DataStructuresTests/TreesTest/BinaryHeapTest/BinaryHeapTest.h"
#include "DataStructuresTests/TreesTest/AVLTreeTest/AVLTreeTest.h"
#include "DataStructuresTests/TreesTest/SplayTreeTest/SplayTreeTest.h"
#include "AlgorithmsTests/SortAlgTests/SortAlgTest.h"
#include "AlgorithmsTests/SearchAlgTests/SearchAlgTest.h"
#include "AlgorithmsTests/IntegerAlgTest/IntegerAlgTest.h"
#include "FilesHandlersTests/InputScannerTest/InputScannerTest.h"
#include "AlgorithmsTests/ArraysAlgTest/ArraysAlgTest.h"
#include "FilesHandlersTests/TxtFileLoaderTest/TxtFileLoaderTest.h"
#include "AlgorithmsTests/CharArrayAlgTest/CharArrayAlgTest.h"


int main(void) {

    // Data structure tests:
    vectorUnitTest();
    arrayListUnitTest();
    setUnitTest();
    linkedListUnitTest();
    doublyLinkedListUnitTest();
    stackUnitTest();
    doublyLinkedListStackUnitTest();
    queueUnitTest();
    stackQueueUnitTest();
    linkedListQueueUnitTest();
    priorityQueueUnitTest();
    heapPriorityQueueUnitTest();
    dequeUnitTest();
    doublyLinkedListDequeUnitTest();
    matrixUnitTest();
    pairUnitTest();
    stringUnitTest();
    hashMapUnitTest();
    doublyLinkedListHashMapUnitTest();
    hashSetUnitTest();
    directedGraphUnitTest();
    undirectedGraphUnitTest();
    trieUnitTest();
    redBlackTreeUnitTest();
    binaryTreeUnitTest();
    binaryHeapUnitTest();
    avlTreeUnitTest();
    splayTreeUnitTest();


    // Sorting and searching tests:
    sortAlgUnitTest();
    searchAlgUnitTest();


    // Integer algorithms test:
    integerAlgUnitTest();


    // Arrays algorithms tests:
    arraysAlgUnitTest();
    charArrayAlgUnitTest();


    // FilesHandler Handlers tests:
    txtFileLoaderAlgUnitTest();
    inputScannerUnitTest();

    return 0;

}

