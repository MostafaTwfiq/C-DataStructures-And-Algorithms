cmake_minimum_required(VERSION 3.16)
project(C_DataStructures C)

set(CMAKE_C_STANDARD 99)

add_executable(C_DataStructures #main.c

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

        DataStructure/Trees/Sources/BinaryMinHeap.c
        DataStructure/Trees/Headers/BinaryMinHeap.h

        DataStructure/Trees/Sources/BinaryMaxHeap.c
        DataStructure/Trees/Headers/BinaryMaxHeap.h

        System/Utils.h

        DataStructure/Trees/Sources/Trie.c
        DataStructure/Trees/Headers/Trie.h

        DataStructure/Queues/Sources/StackQueue.c
        DataStructure/Queues/Headers/StackQueue.h

        DataStructure/Tables/Sources/HashMap.c
        DataStructure/Tables/Headers/HashMap.h

        DataStructure/Queues/Sources/PriorityQueue.c
        DataStructure/Queues/Headers/PriorityQueue.h

        DataStructure/Tables/Sources/LinkedListHashMap.c
        DataStructure/Tables/Headers/LinkedListHashMap.h

        DataStructure/Trees/Sources/RedBlackTree.c
        DataStructure/Trees/Headers/RedBlackTree.h

        DataStructure/Tables/Sources/HashSet.c
        DataStructure/Tables/Headers/HashSet.h

        DataStructure/Graphs/Sources/DirectedGraph.c
        DataStructure/Graphs/Headers/DirectedGraph.h


        "Unit Test/CuTest"
        #"Unit Test/testExample.c"
        #"Unit Test/CuTest/AllTests.c"
        "Unit Test/CuTest/CuTest.c"
        "Unit Test/CuTest/CuTestTest.c"
        "Unit Test/CuTest/CuTest.h"
        "Unit Test/Tests/ListsTest/VectorTest/VectorTest.c"

        DataStructure/Deque/Sources/Deque.c
        DataStructure/Deque/Headers/Deque.h
        DataStructure/Graphs/Sources/UndirectedGraph.c
        DataStructure/Graphs/Headers/UndirectedGraph.h
        DataStructure/Deque/Sources/DLinkedListDeque.c
        DataStructure/Deque/Headers/DLinkedListDeque.h

        Algorithms/Sorting/Headers/Sorting.h
        Algorithms/Searching/Headers/Searching.h
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
        Algorithms/Sorting/Sources/HeapSort.c 
        Algorithms/Sorting/Headers/HeapSort.h
        Files/Sources/TxtFileLoader.c
        Files/Headers/TxtFileLoader.h
        Files/Sources/InputScanner.c
        Files/Headers/InputScanner.h
        DataStructure/Matrices/Sources/Matrix.c
        DataStructure/Matrices/Headers/Matrix.h
        "Unit Test/Tests/ListsTest/VectorTest/VectorTest.c"
        "Unit Test/Tests/ListsTest/VectorTest/VectorTest.h"
        "Unit Test/Tests/Tests.c"
        "Unit Test/Tests/ListsTest/ArrayListTest/ArrayListTest.c" "Unit Test/Tests/ListsTest/ArrayListTest/ArrayListTest.h" "Unit Test/Tests/LinkedListsTest/LinkedListTest/LinkedListTest.c" "Unit Test/Tests/LinkedListsTest/LinkedListTest/LinkedListTest.h" "Unit Test/Tests/LinkedListsTest/DoublyLinkedListTest/DoublyLinkedListTest.c" "Unit Test/Tests/LinkedListsTest/DoublyLinkedListTest/DoublyLinkedListTest.h" "Unit Test/Tests/StacksTest/StackTest/StackTest.c" "Unit Test/Tests/StacksTest/StackTest/StackTest.h" "Unit Test/Tests/StacksTest/DLinkedListStackTest/DLinkedListStackTest.c" "Unit Test/Tests/StacksTest/DLinkedListStackTest/DLinkedListStackTest.h" "Unit Test/Tests/QueuesTest/QueueTest/QueueTest.c" "Unit Test/Tests/QueuesTest/QueueTest/QueueTest.h" "Unit Test/Tests/QueuesTest/StackQueueTest/StackQueueTest.c" "Unit Test/Tests/QueuesTest/StackQueueTest/StackQueueTest.h" "Unit Test/Tests/QueuesTest/LinkedListQueueTest/LinkedListQueueTest.c" "Unit Test/Tests/QueuesTest/LinkedListQueueTest/LinkedListQueueTest.h" "Unit Test/Tests/QueuesTest/PriorityQueueTest/PriorityQueueTest.c" "Unit Test/Tests/QueuesTest/PriorityQueueTest/PriorityQueueTest.h" "Unit Test/Tests/DequesTest/DequeTest/DequeTest.c" "Unit Test/Tests/DequesTest/DequeTest/DequeTest.h" "Unit Test/Tests/DequesTest/DoublyLinkedListDequeTest/DoublyLinkedListDequeTest.c" "Unit Test/Tests/DequesTest/DoublyLinkedListDequeTest/DoublyLinkedListDequeTest.h" "Unit Test/Tests/MatricesTest/MatrixTest/MatrixTest.c" "Unit Test/Tests/MatricesTest/MatrixTest/MatrixTest.h" "Unit Test/Tests/StringsTest/StringTest/StringTest.c" "Unit Test/Tests/StringsTest/StringTest/StringTest.h" "Unit Test/Tests/TablesTest/HashMapTest/HashMapTest.c" "Unit Test/Tests/TablesTest/HashMapTest/HashMapTest.h" "Unit Test/Tests/TablesTest/DounlyLinkedListHashMapTest/DoublyLinkedListHashMapTest.c" "Unit Test/Tests/TablesTest/DounlyLinkedListHashMapTest/DoublyLinkedListHashMapTest.h" "Unit Test/Tests/TablesTest/HashSetTest/HashSetTest.c" "Unit Test/Tests/TablesTest/HashSetTest/HashSetTest.h" "Unit Test/Tests/GraphsTest/DirectedGraphTest/DirectedGraphTest.c" "Unit Test/Tests/GraphsTest/DirectedGraphTest/DirectedGraphTest.h" "Unit Test/Tests/GraphsTest/UndirectedGraphTest/UndirectedGraphTest.c" "Unit Test/Tests/GraphsTest/UndirectedGraphTest/UndirectedGraphTest.h" "Unit Test/Tests/TreesTest/TrieTest/TrieTest.c" "Unit Test/Tests/TreesTest/TrieTest/TrieTest.h" "Unit Test/Tests/TreesTest/RedBlackTreeTest/RedBlackTreeTest.c" "Unit Test/Tests/TreesTest/RedBlackTreeTest/RedBlackTreeTest.h" "Unit Test/Tests/SortAlgTests/SortAlgTest.c" "Unit Test/Tests/SortAlgTests/SortAlgTest.h")