cmake_minimum_required(VERSION 3.16)
project(C_DataStructures C)

set(CMAKE_C_STANDARD 99)

add_executable(C_DataStructures main.c

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

        DataStructure/Queues/Sources/ArrayQueue.c
        DataStructure/Queues/Headers/ArrayQueue.h

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


        #[["Unit Test/CuTest"
        "Unit Test/testExample.c"
       # "Unit Test/CuTest/AllTests.c"
        "Unit Test/CuTest/CuTest.c"
        "Unit Test/CuTest/CuTestTest.c"
        "Unit Test/CuTest/CuTest.h"
]]
        DataStructure/Deque/Sources/Deque.c DataStructure/Deque/Headers/Deque.h DataStructure/Graphs/Sources/UndirectedGraph.c DataStructure/Graphs/Headers/UndirectedGraph.h DataStructure/Deque/Sources/DLinkedListDeque.c DataStructure/Deque/Headers/DLinkedListDeque.h)
