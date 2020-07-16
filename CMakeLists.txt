cmake_minimum_required(VERSION 3.16)
project(C_DataStructures C)

set(CMAKE_C_STANDARD 99)

add_executable(C_DataStructures main.c

        Sources/Stack.c
        Headers/Stack.h

        Sources/LinkedList.c
        Headers/LinkedList.h

        Sources/DoublyLinkedList.c
        Headers/DoublyLinkedList.h

        Sources/String.c
        Headers/String.h

        Sources/ArrayList.c
        Headers/ArrayList.h

        Sources/Vector.c
        Headers/Vector.h

        Sources/DLinkedListStack.c
        Headers/DLinkedListStack.h

        Sources/LinkedListQueue.c
        Headers/LinkedListQueue.h

        Sources/ArrayQueue.c
        Headers/ArrayQueue.h

        Sources/BinaryTree.c
        Headers/BinaryTree.h

        Sources/AVLTree.c
        Headers/AVLTree.h

        Sources/SplayTree.c
        Headers/SplayTree.h

        Sources/BinaryMinHeap.c
        Headers/BinaryMinHeap.h

        Sources/BinaryMaxHeap.c
        Headers/BinaryMaxHeap.h

        Headers/Utils.h

        Sources/Trie.c
        Headers/Trie.h

        Sources/StackQueue.c
        Headers/StackQueue.h

        Sources/HashMap.c
        Headers/HashMap.h

        Sources/PriorityQueue.c
        Headers/PriorityQueue.h

        Sources/LinkedListHashMap.c
        Headers/LinkedListHashMap.h

        Sources/RedBlackTree.c
        Headers/RedBlackTree.h

        Sources/ArrayDeque.c
        Headers/ArrayDeque.h

        Sources/HashSet.c
        Headers/HashSet.h

        Sources/DirectedGraph.c
        Headers/DirectedGraph.h

        #[["Unit Test/CuTest"
        "Unit Test/testExample.c"
        "Unit Test/CuTest/AllTests.c"
        "Unit Test/CuTest/CuTest.c"
        "Unit Test/CuTest/CuTestTest.c"
        "Unit Test/CuTest/CuTest.h"
]]
        )
