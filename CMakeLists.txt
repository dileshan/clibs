cmake_minimum_required(VERSION 3.3)
project(clibs)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(LINKED_LIST_SOURCE_FILES LinkedList/include/BasicLinkedList.h LinkedList/src/BasicLinkedList.cpp LinkedList/include/Stack.h LinkedList/src/Stack.cpp)
set(TEST_MAIN LinkedList/main.cpp LinkedList/signal_handler.cpp)

add_library(LinkedList SHARED ${LINKED_LIST_SOURCE_FILES})
add_executable(main ${TEST_MAIN})