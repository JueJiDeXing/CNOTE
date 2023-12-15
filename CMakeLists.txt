cmake_minimum_required(VERSION 3.26)
project(C)

set(CMAKE_C_STANDARD 11)

add_executable(SqTree Structures/Tree/SqTree.c)
add_executable(BSTree Structures/Tree/BSTree.c)