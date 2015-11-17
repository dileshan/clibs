cmake_minimum_required(VERSION 3.3)
project(clibs)

set(CMAKE_CXX_FLAGS "$(CMAKE_CXX_FLAGS) -std=c++11")

set(LINKED_LIST_SOURCE_FILES LinkedList/include/*.h LinkedList/src/*.cpp LinkedList/*.cpp)
#add_library(lib_linked_list.a SHARED ${LINKED_LIST_SOURCE_FILES})
