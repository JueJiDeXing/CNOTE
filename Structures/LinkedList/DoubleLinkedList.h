// Author: 绝迹的星 
// Created on 2023/12/12


#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>


#ifndef C_DOUBLELINKEDLIST_H
#define C_DOUBLELINKEDLIST_H
typedef struct Node {
    struct Node *prev;
    int val;
    struct Node *next;
} Node;
typedef struct LinkedList {
    int size;
    Node *first;
    Node *last;
} LinkedList;

void InitLinkedList(LinkedList *L);
bool IsEmpty(LinkedList L);
void linkFirst_(LinkedList *L, int e);

void linkLast_(LinkedList *L, int e);

void linkBefore_(LinkedList *L, int e, Node *succ);

int unlinkFirst_(LinkedList *L, Node *f);

int unlinkLast_(LinkedList *L, Node *l);

int unlink_(LinkedList *L, Node *x);

int GetFirst(LinkedList L);

int GetLast(LinkedList L);

int RemoveFirst(LinkedList *L);

int RemoveLast(LinkedList *L);

void AddFirst(LinkedList *L, int e);

void AddLast(LinkedList *L, int e);

bool Contains(LinkedList L, int o);

int GetSize(LinkedList L);

bool Add(LinkedList *L, int e);

bool RemoveObject(LinkedList *L, int o);

void Clear(LinkedList *L);

int Get(LinkedList L, int index);

int Set(LinkedList *L, int index, int element);

void AddByIndex(LinkedList *L, int index, int element);

int RemoveByIndex(LinkedList *L, int index);

bool isElementIndex(LinkedList L, int index);

bool isPositionIndex(LinkedList L, int index);

char *outOfBoundsMsg(LinkedList L, int index);

void checkElementIndex(LinkedList L, int index);

void checkPositionIndex(LinkedList L, int index);

Node *node(LinkedList L, int index);

int IndexOf(LinkedList L, int o);

int lastIndexOf(LinkedList L, int o);

int Peek(LinkedList L);

int Element(LinkedList L);

int Poll(LinkedList *L);

int Remove(LinkedList *L);

bool Offer(LinkedList *L, int e);

bool OfferFirst(LinkedList *L, int e);

bool OfferLast(LinkedList *L, int e);

int PeekFirst(LinkedList *L);

int PeekLast(LinkedList *L);

int PollFirst(LinkedList *L);

int PollLast(LinkedList *L);

void Push(LinkedList *L, int e);

int Pop(LinkedList *L);

#endif //C_DOUBLELINKEDLIST_H
