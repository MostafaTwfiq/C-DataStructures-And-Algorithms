cmake_minimum_required(VERSION 3.16)
project(C_DataStructures C)

set(CMAKE_C_STANDARD 99)

set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -lm")


add_executable(C_DataStructures

        #main.c

        "Unit Test/Tests/Tests.c"

        "Unit Test/CuTest"
        "Unit Test/CuTest/CuTest.c"
        "Unit Test/CuTest/CuTest.h"
        #"Unit Test/CuTest/AllTests.c"
        #"Unit Test/CuTest/CuTestTest.c"
        #"Unit Test/ErrorsTestStruct.h"

        DataStructure/Stacks/Sources/Stack.c
        DataStructure/Stacks/Headers/Stack.h

        DataStructure/LinkedLists/Sources/LinkedList.c
        DataStructure/LinkedLists/Headers/LinkedList.h

        DataStructure/LinkedLists/Sources/DoublyLinkedList.c
        DataStructure/LinkedLists/Headers/DoublyLinkedList.h

        DataStructure/Strings/Sources/String.c
        DataStructure/Strings/Headers/String.h

        DataStructure/Lists/Sources/ArrayList.c
        DataStructure/Lists/Headers/ArrayList.h

        DataStructure/Lists/Sources/Vector.c
        DataStructure/Lists/Headers/Vector.h

        DataStructure/Lists/Sources/Set.c
        DataStructure/Lists/Headers/Set.h

        DataStructure/Stacks/Sources/DLinkedListStack.c
        DataStructure/Stacks/Headers/DLinkedListStack.h

        DataStructure/Queues/Sources/LinkedListQueue.c
        DataStructure/Queues/Headers/LinkedListQueue.h

        DataStructure/Queues/Sources/Queue.c
        DataStructure/Queues/Headers/Queue.h

        DataStructure/Trees/Sources/BinaryTree.c
        DataStructure/Trees/Headers/BinaryTree.h

        DataStructure/Trees/Sources/AVLTree.c
        DataStructure/Trees/Headers/AVLTree.h

        DataStructure/Trees/Sources/SplayTree.c
        DataStructure/Trees/Headers/SplayTree.h

        System/Utils.h

        DataStructure/Trees/Sources/Trie.c
        DataStructure/Trees/Headers/Trie.h

        DataStructure/Queues/Sources/StackQueue.c
        DataStructure/Queues/Headers/StackQueue.h

        DataStructure/Tables/Sources/HashMap.c
        DataStructure/Tables/Headers/HashMap.h

        DataStructure/Queues/Sources/PriorityQueue.c
        DataStructure/Queues/Headers/PriorityQueue.h

        DataStructure/Queues/Sources/HPriorityQueue.c
        DataStructure/Queues/Headers/HPriorityQueue.h

        DataStructure/Tables/Sources/LinkedListHashMap.c
        DataStructure/Tables/Headers/LinkedListHashMap.h

        DataStructure/Trees/Sources/RedBlackTree.c
        DataStructure/Trees/Headers/RedBlackTree.h

        DataStructure/Trees/Sources/BinaryHeap.c
        DataStructure/Trees/Headers/BinaryHeap.h

        DataStructure/Tables/Sources/HashSet.c
        DataStructure/Tables/Headers/HashSet.h

        DataStructure/Graphs/Sources/DirectedGraph.c
        DataStructure/Graphs/Headers/DirectedGraph.h

        DataStructure/Deque/Sources/Deque.c
        DataStructure/Deque/Headers/Deque.h

        DataStructure/Graphs/Sources/UndirectedGraph.c
        DataStructure/Graphs/Headers/UndirectedGraph.h

        DataStructure/Deque/Sources/DLinkedListDeque.c
        DataStructure/Deque/Headers/DLinkedListDeque.h


        DataStructure/Matrices/Sources/Matrix.c
        DataStructure/Matrices/Headers/Matrix.h

        DataStructure/Pairs/Sources/Pair.c
        DataStructure/Pairs/Headers/Pair.h

        FilesHandler/Sources/TxtFileLoader.c
        FilesHandler/Headers/TxtFileLoader.h

        FilesHandler/Sources/InputScanner.c
        FilesHandler/Headers/InputScanner.h

        Algorithms/Sorting/Headers/Sorting.h
        Algorithms/Sorting/Sources/BubbleSort.c
        Algorithms/Sorting/Headers/BubbleSort.h
        Algorithms/Sorting/Sources/SwapFunction.c
        Algorithms/Sorting/Headers/SwapFunction.h
        Algorithms/Sorting/Sources/SelectionSort.c
        Algorithms/Sorting/Headers/SelectionSort.h
        Algorithms/Sorting/Sources/InsertionSort.c
        Algorithms/Sorting/Headers/InsertionSort.h
        Algorithms/Sorting/Sources/MergeSort.c
        Algorithms/Sorting/Headers/MergeSort.h
        Algorithms/Sorting/Sources/QuickSort.c
        Algorithms/Sorting/Headers/QuickSort.h
        Algorithms/Sorting/Sources/CountingSort.c
        Algorithms/Sorting/Headers/CountingSort.h
        Algorithms/Sorting/Sources/HeapSort.c
        Algorithms/Sorting/Headers/HeapSort.h

        Algorithms/Searching/Headers/Searching.h
        Algorithms/Searching/Sources/LinearSearch.c
        Algorithms/Searching/Headers/LinearSearch.h
        Algorithms/Searching/Sources/BinarySearch.c
        Algorithms/Searching/Headers/BinarySearch.h
        Algorithms/Searching/Sources/TernarySearch.c
        Algorithms/Searching/Headers/TernarySearch.h
        Algorithms/Searching/Sources/JumpSearch.c
        Algorithms/Searching/Headers/JumpSearch.h
        Algorithms/Searching/Sources/ExponentialSearch.c
        Algorithms/Searching/Headers/ExponentialSearch.h

        Algorithms/ArraysAlg/Sources/ArraysAlg.c
        Algorithms/ArraysAlg/Headers/ArraysAlg.h

        Algorithms/ArraysAlg/Sources/CharArrayAlg.c
        Algorithms/ArraysAlg/Headers/CharArrayAlg.h

        Algorithms/IntegersAlg/Sources/IntegerAlg.c
        Algorithms/IntegersAlg/Headers/IntegerAlg.h

        "Unit Test/Tests/DataStructuresTests/ListsTest/VectorTest/VectorTest.c"
        "Unit Test/Tests/DataStructuresTests/ListsTest/VectorTest/VectorTest.c"
        "Unit Test/Tests/DataStructuresTests/ListsTest/VectorTest/VectorTest.h"
        "Unit Test/Tests/DataStructuresTests/ListsTest/ArrayListTest/ArrayListTest.c"
        "Unit Test/Tests/DataStructuresTests/ListsTest/ArrayListTest/ArrayListTest.h"
        "Unit Test/Tests/DataStructuresTests/LinkedListsTest/LinkedListTest/LinkedListTest.c"
        "Unit Test/Tests/DataStructuresTests/LinkedListsTest/LinkedListTest/LinkedListTest.h"
        "Unit Test/Tests/DataStructuresTests/LinkedListsTest/DoublyLinkedListTest/DoublyLinkedListTest.c"
        "Unit Test/Tests/DataStructuresTests/LinkedListsTest/DoublyLinkedListTest/DoublyLinkedListTest.h"
        "Unit Test/Tests/DataStructuresTests/StacksTest/StackTest/StackTest.c"
        "Unit Test/Tests/DataStructuresTests/StacksTest/StackTest/StackTest.h"
        "Unit Test/Tests/DataStructuresTests/StacksTest/DLinkedListStackTest/DLinkedListStackTest.c"
        "Unit Test/Tests/DataStructuresTests/StacksTest/DLinkedListStackTest/DLinkedListStackTest.h"
        "Unit Test/Tests/DataStructuresTests/QueuesTest/QueueTest/QueueTest.c"
        "Unit Test/Tests/DataStructuresTests/QueuesTest/QueueTest/QueueTest.h"
        "Unit Test/Tests/DataStructuresTests/QueuesTest/StackQueueTest/StackQueueTest.c"
        "Unit Test/Tests/DataStructuresTests/QueuesTest/StackQueueTest/StackQueueTest.h"
        "Unit Test/Tests/DataStructuresTests/QueuesTest/LinkedListQueueTest/LinkedListQueueTest.c"
        "Unit Test/Tests/DataStructuresTests/QueuesTest/LinkedListQueueTest/LinkedListQueueTest.h"
        "Unit Test/Tests/DataStructuresTests/QueuesTest/PriorityQueueTest/PriorityQueueTest.c"
        "Unit Test/Tests/DataStructuresTests/QueuesTest/PriorityQueueTest/PriorityQueueTest.h"
        "Unit Test/Tests/DataStructuresTests/DequesTest/DequeTest/DequeTest.c"
        "Unit Test/Tests/DataStructuresTests/DequesTest/DequeTest/DequeTest.h"
        "Unit Test/Tests/DataStructuresTests/DequesTest/DoublyLinkedListDequeTest/DoublyLinkedListDequeTest.c"
        "Unit Test/Tests/DataStructuresTests/DequesTest/DoublyLinkedListDequeTest/DoublyLinkedListDequeTest.h"
        "Unit Test/Tests/DataStructuresTests/MatricesTest/MatrixTest/MatrixTest.c"
        "Unit Test/Tests/DataStructuresTests/MatricesTest/MatrixTest/MatrixTest.h"
        "Unit Test/Tests/DataStructuresTests/StringsTest/StringTest/StringTest.c"
        "Unit Test/Tests/DataStructuresTests/StringsTest/StringTest/StringTest.h"
        "Unit Test/Tests/DataStructuresTests/TablesTest/HashMapTest/HashMapTest.c"
        "Unit Test/Tests/DataStructuresTests/TablesTest/HashMapTest/HashMapTest.h"
        "Unit Test/Tests/DataStructuresTests/TablesTest/DounlyLinkedListHashMapTest/DoublyLinkedListHashMapTest.c"
        "Unit Test/Tests/DataStructuresTests/TablesTest/DounlyLinkedListHashMapTest/DoublyLinkedListHashMapTest.h"
        "Unit Test/Tests/DataStructuresTests/TablesTest/HashSetTest/HashSetTest.c"
        "Unit Test/Tests/DataStructuresTests/TablesTest/HashSetTest/HashSetTest.h"
        "Unit Test/Tests/DataStructuresTests/GraphsTest/DirectedGraphTest/DirectedGraphTest.c"
        "Unit Test/Tests/DataStructuresTests/GraphsTest/DirectedGraphTest/DirectedGraphTest.h"
        "Unit Test/Tests/DataStructuresTests/GraphsTest/UndirectedGraphTest/UndirectedGraphTest.c"
        "Unit Test/Tests/DataStructuresTests/GraphsTest/UndirectedGraphTest/UndirectedGraphTest.h"
        "Unit Test/Tests/DataStructuresTests/TreesTest/TrieTest/TrieTest.c"
        "Unit Test/Tests/DataStructuresTests/TreesTest/TrieTest/TrieTest.h"
        "Unit Test/Tests/DataStructuresTests/TreesTest/RedBlackTreeTest/RedBlackTreeTest.c"
        "Unit Test/Tests/DataStructuresTests/TreesTest/RedBlackTreeTest/RedBlackTreeTest.h"
        "Unit Test/Tests/AlgorithmsTests/SortAlgTests/SortAlgTest.c"
        "Unit Test/Tests/AlgorithmsTests/SortAlgTests/SortAlgTest.h"
        "Unit Test/Tests/AlgorithmsTests/SearchAlgTests/SearchAlgTest.c"
        "Unit Test/Tests/AlgorithmsTests/SearchAlgTests/SearchAlgTest.h"
        "Unit Test/Tests/AlgorithmsTests/IntegerAlgTest/IntegerAlgTest.c"
        "Unit Test/Tests/AlgorithmsTests/IntegerAlgTest/IntegerAlgTest.h"
        "Unit Test/Tests/FilesHandlersTests/InputScannerTest/InputScannerTest.c"
        "Unit Test/Tests/FilesHandlersTests/InputScannerTest/InputScannerTest.h"
        "Unit Test/Tests/AlgorithmsTests/ArraysAlgTest/ArraysAlgTest.c"
        "Unit Test/Tests/AlgorithmsTests/ArraysAlgTest/ArraysAlgTest.h"
        "Unit Test/Tests/FilesHandlersTests/TxtFileLoaderTest/TxtFileLoaderTest.c"
        "Unit Test/Tests/FilesHandlersTests/TxtFileLoaderTest/TxtFileLoaderTest.h"
        "Unit Test/Tests/AlgorithmsTests/CharArrayAlgTest/CharArrayAlgTest.c"
        "Unit Test/Tests/AlgorithmsTests/CharArrayAlgTest/CharArrayAlgTest.h"
        "Unit Test/Tests/DataStructuresTests/TreesTest/BinaryTreeTest/BinaryTreeTest.c"
        "Unit Test/Tests/DataStructuresTests/TreesTest/BinaryTreeTest/BinaryTreeTest.h"
        "Unit Test/Tests/DataStructuresTests/TreesTest/BinaryHeapTest/BinaryHeapTest.c"
        "Unit Test/Tests/DataStructuresTests/TreesTest/BinaryHeapTest/BinaryHeapTest.h"
        "Unit Test/Tests/DataStructuresTests/TreesTest/AVLTreeTest/AVLTreeTest.c"
        "Unit Test/Tests/DataStructuresTests/TreesTest/AVLTreeTest/AVLTreeTest.h"
        "Unit Test/Tests/DataStructuresTests/TreesTest/SplayTreeTest/SplayTreeTest.c"
        "Unit Test/Tests/DataStructuresTests/TreesTest/SplayTreeTest/SplayTreeTest.h"
        "Unit Test/Tests/DataStructuresTests/PairsTest/PairTest/PairTest.c"
        "Unit Test/Tests/DataStructuresTests/PairsTest/PairTest/PairTest.h"
        "Unit Test/Tests/DataStructuresTests/QueuesTest/HeapPriorityQueueTest/HeapPriorityQueueTest.c"
        "Unit Test/Tests/DataStructuresTests/QueuesTest/HeapPriorityQueueTest/HeapPriorityQueueTest.h"
        "Unit Test/Tests/DataStructuresTests/ListsTest/SetTest/SetTest.c"
        "Unit Test/Tests/DataStructuresTests/ListsTest/SetTest/SetTest.h"
        )

if (NOT WIN32)
    target_link_libraries(C_DataStructures PRIVATE m)
endif()
