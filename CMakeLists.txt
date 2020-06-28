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

        Sources/Heap.c
        Headers/Heap.h

        Headers/Utils.h

        Sources/Trie.c Headers/Trie.h
        Sources/StackQueue.c Headers/StackQueue.h)
