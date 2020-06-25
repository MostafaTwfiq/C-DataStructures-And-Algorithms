cmake_minimum_required(VERSION 3.16)
project(C_DataStructures C)

set(CMAKE_C_STANDARD 99)

add_executable(C_DataStructures main.c Sources/LinkedList.c Headers/LinkedList.h)