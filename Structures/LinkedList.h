//
// Created by 绝迹的星 on 2023/10/19.
//
#pragma once
#ifndef PROJECT_LINKEDLIST_H
#define PROJECT_LINKEDLIST_H

typedef struct LNode { //结点类型
    int data;
    struct LNode *next;
} LNode, *LinkedList;

#include "Status.h"

Status init_LinkedList(LinkedList *L);

int getLength_LinkedList(LinkedList L);

Status insert_LinkedList(LinkedList *L, int n, int e);

Status getElem_LinkedList(LinkedList L, int n, int *e);

void create_LinkedList(LinkedList *L, int n);

void clear_LinkedList(LinkedList *L);

bool isEmpty_LinkedList(LinkedList L);

int locateElem_LinkedList(LinkedList L, int e, bool(*compare)(int, int));

Status priorElem_LinkedList(LinkedList L, int cur_e, int *pre_e);

Status nextElem_LinkedList(LinkedList L, int cur_e, int *nex_e);

Status insertByVal_LinkedList(LinkedList *L, int e, int insertVal);

Status delete_LinkedList(LinkedList *L, int e);

Status merge_LinkedList(LinkedList *La, LinkedList *Lb);

Status reverse_LinkedList(LinkedList *L);

void printLinkedList(LinkedList L);

Status append_LinkedList(LinkedList *L, int e);

#endif //PROJECT_LINKEDLIST_H
