//
// Created by 绝迹的星 on 2023/10/19.
//
#ifndef PROJECT_ARRAYLIST_H
#define PROJECT_ARRAYLIST_H

#include "Status.h"

typedef struct {
    int *elem; //存储空间基址
    int length; //当前存储长度
    int capacity;//当前分配的存储容量
} ArrayList;
#define LIST_INIT_SIZE 50  // 线性表存储空间的初始分配量


Status init_ArrayList(ArrayList *L);

Status destroy_ArrayList(ArrayList *L);

Status clear_ArrayList(ArrayList *L);

bool isEmpty_Array(ArrayList *L);

bool isFull_Array(ArrayList *L);

int getLength_Array(ArrayList *L);

Status getElem_Array(ArrayList *L, int i, int *elem);

bool contain_Array(ArrayList *L, int e);

int locateElem_Array(ArrayList *L, int e, bool (*compare)(int, int));

Status priorElem_Array(ArrayList *L, int cur_elem, int *pre_elem);

Status nextElem_Array(ArrayList *L, int cur_elem, int *nex_elem);

Status insert_Array(ArrayList *L, int e, int i);

Status delete_Array(ArrayList *L, int *e, int i);

Status travers_Array(ArrayList *L, int (*visit)(int));

Status append_Array(ArrayList *L, int elem);

void unite_Array(ArrayList *L1, ArrayList *L2);

void merge_Array(ArrayList L1, ArrayList L2, ArrayList *L3);

void printArrayList(ArrayList L);

#endif //PROJECT_ARRAYLIST_H
