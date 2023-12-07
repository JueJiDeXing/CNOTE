// Author: 绝迹的星 
// Created on 2023/10/26


#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "Status.h"

typedef struct LNode {
    struct LNode *next;
    int val;
} LNode, *LinkStack;

Status InitStack(LinkStack *s) {
    *s = malloc(sizeof(LNode));
    if (!*s) exit(OVERFLOW);
    (*s)->next = NULL;
    return OK;
}

Status DestroyStack(LinkStack *s) {
    LinkStack p = (*s)->next;
    while (p) {
        LinkStack t = p;
        p = p->next;
        free(t);
    }
    return OK;
}

bool StackEmpty(LinkStack s) {
    return s->next == NULL;
}

int StackLength(LinkStack s) {
    int len = 0;
    LinkStack p = s->next;
    while (p) {
        len++;
        p = p->next;
    }
    return len;
}

int GetTop(LinkStack s) {
    return s->next->val;
}

Status Push(LinkStack *s, int e) {
    LinkStack p;
    p = malloc(sizeof(LNode));
    p->val = e;
    p->next = (*s)->next;
    (*s)->next = p;
    return OK;
}

Status Pop(LinkStack *s, int *e) {
    LinkStack p = (*s)->next;
    *e = p->val;
    (*s)->next = p->next;
    return OK;
}

Status Peek(LinkStack s, int *e) {
    *e = s->next->val;
    return OK;
}

void printList(LinkStack s) {
    LinkStack p = s->next;
    if (p == NULL) exit(ERROR);
    while (p->next != NULL) {
        printf("%d->", p->val);
        p = p->next;
    }
    printf("%d\n", p->val);
}
