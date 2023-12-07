// Author: 绝迹的星 
// Created on 2023/11/8
// - Hello World.
// - You are my world too.

#include "Status.c"
#include "stdlib.h"
#include "stdbool.h"

typedef struct SqList {
    int *elem;
    int size;
} SqList;

Status InitSqList(SqList *L) {
    L->elem = malloc(sizeof(int) * DEFAULT_SIZE);
    if (!L->elem)exit(ERROR);
    L->size = 0;
    return OK;
}

bool IsFull(SqList L) {
    return L.size == DEFAULT_SIZE;
}

bool IsEmpty(SqList L) {
    return L.size == 0;
}

Status Add(SqList *L, int e) {
    if (IsFull(*L)) {
        exit(ERROR);
    }
    L->elem[L->size++] = e;
    return OK;
}

Status Delete(SqList *L, int index, int *e) {
    if (IsEmpty(*L)) {
        exit(ERROR);
    }
    if (index < 0 || index > L->size) {
        exit(ERROR);
    }
    *e = L->elem[index];

    for (int i = index; i < L->size - 1; i++) {
        L->elem[i] = L->elem[i + 1];
    }
    L->elem[L->size - 1] = 0;
    L->size--;
    return OK;
}

Status Insert(SqList *L, int index, int e) {
    if (IsFull(*L)) {
        exit(ERROR);
    }
    if (index < 0 || index > L->size) {
        exit(ERROR);
    }
    for (int i = L->size; i > index; i--) {
        L->elem[i] = L->elem[i - 1];
    }
    L->elem[index] = e;
    L->size++;
    return OK;
}

int GetLength(SqList L) {
    return L.size;
}

Status Clear(SqList *L) {
//    for (int i = 0; i < L->size; i++) {
//        L->elem[i] = 0;
//    }
    L->size = 0;
    return OK;
}

Status Destroy(SqList *L) {
    free(L->elem);
    return OK;
}

int GetElem(SqList L, int index) {
    if (index < 0 || index >= L.size) {
        exit(ERROR);
    }
    return L.elem[index];
}

int FindElem(SqList L, int e) {
    for (int i = 0; i < L.size; i++) {
        if (L.elem[i] == e) {
            return i;
        }
    }
    return -1;
}

Status Travel(SqList L, int *visit(int)) {
    for (int i = 0; i < L.size; i++) {
        visit(L.elem[i]);
    }
    return OK;
}

Status Union(SqList *LA, SqList LB) {//合并数组

    int lenB = GetLength(LB);
    for (int i = 0; i < lenB; i++) {
        int e = GetElem(LB, i);
        if (FindElem(*LA, e) == -1) {
            Add(LA, e);
        }
    }
    return OK;
}

Status Merge(SqList La, SqList Lb, SqList *Lc) {//合并升序数组
    InitSqList(Lc);
    int lenA = GetLength(La);
    int lenB = GetLength(Lb);
    int i = 0, j = 0;
    while (i < lenA && j < lenB) {
        int ea = GetElem(La, i);
        int eb = GetElem(Lb, i);
        if (ea < eb) {
            Add(Lc, ea);
            i++;
        } else {
            Add(Lc, eb);
            j++;
        }
    }
    while (i < lenA) {
        int ea = GetElem(La, i);
        Add(Lc, ea);
        i++;
    }
    while (j < lenB) {
        int eb = GetElem(Lb, i);
        Add(Lc, eb);
        j++;
    }
    return OK;
}