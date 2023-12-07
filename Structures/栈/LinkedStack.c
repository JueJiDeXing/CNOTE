// Author: 绝迹的星 
// Created on 2023/11/8


#include <stdio.h>
#include "../Status.h"
#include "stdbool.h"
#include "stdlib.h"

typedef struct Node {
    int data;
    struct Node *next;
} Node, *LinkedStack;

Status InitLinkedList(LinkedStack *L) {
    *L = malloc(sizeof(Node));
    if (!*L)exit(ERROR);
    (*L)->data = -1;
    (*L)->next = NULL;
    return OK;
}

bool IsEmpty(LinkedStack L) {
    return L->next == NULL;
}

Status Push(LinkedStack L, int e) {
    Node *added = malloc(sizeof(Node));
    added->data = e;
    added->next = L->next;
    L->next = added;
    return OK;
}


Status Pop(LinkedStack *L, int *e) {
    if (IsEmpty(*L)) {
        exit(ERROR);
    }
    Node *p = (*L)->next;
    *e = p->data;
    (*L)->next = p->next;
    free(p);
    return OK;
}

int GetLength(LinkedStack L) {
    Node *p = L->next;
    int len = 0;
    while (p) {
        len++;
        p = p->next;
    }
    return len;
}


Status Clear(LinkedStack *L) {
    Node *p = (*L)->next;
    while (p) {
        Node *n = p->next;
        free(p);
        p = n;
    }
    (*L)->next = NULL;
    return OK;
}

Status Destroy(LinkedStack *L) {
    Clear(L);
    free(L);
    return OK;
}
