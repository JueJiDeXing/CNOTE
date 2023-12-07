//
// Created by 绝迹的星 on 2023/10/17.
//
#include<stdio.h>
#include<stdlib.h>
#include <stdbool.h>
#include "LinkedList.h"



Status init_LinkedList(LinkedList *L) {
    *L = malloc(sizeof(LNode));
    if (!*L) exit(OVERFLOW);
    (*L)->next = NULL;
    return OK;
}

int getLength_LinkedList(LinkedList L) {
    LinkedList p = L->next;
    int len = 0;
    while (p) {
        len++;
        p = p->next;
    }
    return len;
}
Status append_LinkedList(LinkedList *L, int e){
    LinkedList p=(*L);
    while(p->next){
        p=p->next;
    }
    LNode* added= malloc(sizeof (LNode));
    added->data=e;
    added->next=NULL;
    p->next=added;
    return OK;
}
/**
 * 按索引插入元素到链表
 * @param L
 * @param n 索引
 * @param e 插入的元素
 * @return
 */
Status insert_LinkedList(LinkedList *L, int n, int e) {
    LinkedList p = (*L);
    for (int i = 0; i < n; i++){
        p = p->next;
        if (!p) return INFEASIBLE;
    }
    LinkedList s = malloc(sizeof(LNode));
    s->data = e;
    s->next = p->next;
    p->next = s;
    return OK;
}

Status getElem_LinkedList(LinkedList L, int n, int *e) {
    LinkedList p = L->next;
    int i;
    for (i = 1; i < n; i++)
        p = p->next;
    if (!p || i > n) return ERROR;

    *e = p->data;
    return OK;
}

/**
 * 初始化一个含n个节点的链表,节点值在控制台输入,节点顺序与输入顺序相反
 * @param L
 * @param n
 */
void create_LinkedList(LinkedList *L, int n) {
    (*L) = malloc(sizeof(LNode));
    if (!*L) exit(OVERFLOW);
    (*L)->next = NULL;

    for (int i = n; i > 0; i--) {
        LinkedList p = malloc(sizeof(LNode));
        scanf_s("%d", &p->data);
        p->next = (*L)->next;
        (*L)->next = p;
    }
}

void clear_LinkedList(LinkedList *L) {
    LinkedList p = (*L)->next;
    while (p != NULL) {
        LinkedList q = p;
        p = p->next;
        free(q);
    }
    (*L)->next = NULL;
}

bool isEmpty_LinkedList(LinkedList L) {
    return !L->next;
}

int locateElem_LinkedList(LinkedList L, int e, bool(*compare)(int, int)) {
    LinkedList p = L->next;
    int i = 1;
    while (p) {
        if (compare(e, p->data))
            return i;
        i++;
        p = p->next;
    }
    return ERROR;
}

/**
 * 获取前驱
 * @param L
 * @param cur_e
 * @param pre_e
 * @return
 */
Status priorElem_LinkedList(LinkedList L, int cur_e, int *pre_e) {
    LinkedList p = L->next;
    LinkedList q = L;
    while (p && p->data != cur_e) {
        q = q->next;
        p = p->next;
    }
    if (!p) exit(ERROR);
    *pre_e = q->data;
    return OK;
}
/**
 * 获取后继
 * @param L
 * @param cur_e
 * @param nex_e
 * @return
 */
Status nextElem_LinkedList(LinkedList L, int cur_e, int *nex_e) {
    LinkedList p = L;
    while (p->next && p->data != cur_e)
        p = p->next;
    if (!p->next) exit(ERROR);
    *nex_e = p->next->data;
    return OK;
}
/**
 * 插入节点到链表元素值为e的节点前
 * @param L
 * @param e
 * @param insertVal
 * @return
 */
Status insertByVal_LinkedList(LinkedList *L, int e, int insertVal) {
    LinkedList p = (*L)->next;
    LinkedList prev = *L;
    while (p && p->data != e) {
        p = p->next;
        prev = prev->next;
    }
    if (!p) exit(ERROR);
    LinkedList s = malloc(sizeof(LNode));
    s->data = insertVal;
    s->next = p;
    prev->next = s;
    return OK;
}
/**
 * 按值删除元素
 * @param L
 * @param e 要删除的元素值
 * @return
 */
Status delete_LinkedList(LinkedList *L, int e) {
    LinkedList p = (*L)->next;
    LinkedList prev = *L;

    while (p && p->data != e) {//找到删除节点以及它的前驱
        p = p->next;
        prev = prev->next;
    }
    if (!p) exit(ERROR);
    prev->next = p->next;
    free(p);
    return OK;
}
/**
 * 合并升序链表Lb到升序链表La
 * @param La
 * @param Lb
 * @return
 */
Status merge_LinkedList(LinkedList *La, LinkedList *Lb) { //用于非递减链表
    LinkedList p = *La;
    LinkedList Pa = (*La)->next;
    LinkedList Pb = (*Lb)->next;
    while (Pa && Pb) {
        if (Pa->data > Pb->data) {
            p->next = Pb;
            p = Pb;
            Pb = Pb->next;
        } else {
            p->next = Pa;
            p = Pa;
            Pa = Pa->next;
        }
    }
    p->next = Pa ? Pa : Pb; // 插入剩余段
    free(Lb);       //释放Lb的头节点
    return OK;
}
/**
 * 链表反转
 * @param L
 * @return
 */
Status reverse_LinkedList(LinkedList *L) {
    LinkedList curr = (*L)->next;
    LinkedList prev = NULL, next = NULL;
    while (curr) {
        next = curr->next;
        curr->next = prev;
        prev = curr;
        curr = next;
    }
    (*L)->next = prev;
    return OK;
}

void printLinkedList(LinkedList L) {
    LinkedList p = L->next;
    while (p != NULL) {
        printf("%d->", p->data);
        p = p->next;
    }
    printf("null\n");
}
