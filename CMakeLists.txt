cmake_minimum_required(VERSION 3.26)
project(C)

set(CMAKE_C_STANDARD 11)

add_executable(test1 test/test1.c)
add_executable(test2 test/test2.c)
add_executable(test3 test/test3.c)
add_executable(DisjoinSet Structures/并查集/DisJoinSet.c)