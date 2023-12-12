cmake_minimum_required(VERSION 3.26)
project(C)

set(CMAKE_C_STANDARD 11)

add_executable(Prim Structures/Graph/MinSpanningTree/Prim.c)
add_executable(Krusal Structures/Graph/MinSpanningTree/Krusal.c)
add_executable(MinHeap Structures/Heap/MinHeap.c)
add_executable(dddd test/dddd.c)
add_executable(HashMap Structures/HashMap/HashMap.c)