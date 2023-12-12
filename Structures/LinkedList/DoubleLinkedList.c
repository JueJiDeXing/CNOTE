// Author: 绝迹的星 
// Created on 2023/12/12


#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

#include "DoubleLinkedList.h"

void InitLinkedList(LinkedList *L) {
    L->size = 0;
    L->first = NULL;
    L->last = NULL;
}

bool IsEmpty(LinkedList L) {
    return GetSize(L) == 0;
}

/**
 * Links e as first element.
 */

void linkFirst_(LinkedList *L, int e) {
    Node *f = L->first;
    Node *newNode = malloc(sizeof(Node));
    newNode->val = e;
    newNode->prev = NULL;
    newNode->next = f;
    L->first = newNode;
    if (f == NULL) {
        L->last = newNode;
    } else {
        f->prev = newNode;
    }
    L->size++;
}

/**
 * Links e as last element.
 */

void linkLast_(LinkedList *L, int e) {
    Node *l = L->last;
    Node *newNode = malloc(sizeof(Node));
    newNode->val = e;
    newNode->prev = l;
    newNode->next = NULL;
    L->last = newNode;
    if (l == NULL) {
        L->first = newNode;
    } else {
        l->next = newNode;
    }
    L->size++;
}

/**
 * Inserts element e before non-null Node succ.
 */
void linkBefore_(LinkedList *L, int e, Node *succ) {
    // assert succ != null;
    Node *pred = succ->prev;
    Node *newNode = malloc(sizeof(Node));
    newNode->val = e;
    newNode->prev = pred;
    newNode->next = succ;
    succ->prev = newNode;
    if (pred == NULL) {
        L->first = newNode;
    } else {
        pred->next = newNode;
    }
    L->size++;
}

/**
 * Unlinks non-null first node f.
 */
int unlinkFirst_(LinkedList *L, Node *f) {
// assert f == first && f != null;
    int element = f->val;
    Node *next = f->next;
    L->first = next;
    if (next == NULL) {
        L->last = NULL;
    } else {
        next->prev = NULL;
    }
    free(f);
    L->size--;
    return element;
}

/**
 * Unlinks non-null last node l.
 */
int unlinkLast_(LinkedList *L, Node *l) {
// assert l == last && l != null;
    int element = l->val;
    Node *prev = l->prev;
    L->last = prev;
    if (prev == NULL) {
        L->first = NULL;
    } else {
        prev->next = NULL;
    }
    free(l);
    L->size--;
    return element;
}

/**
 * Unlinks non-null node x.
 */
int unlink_(LinkedList *L, Node *x) {
    // assert x != null;
    int element = x->val;
    Node *next = x->next;
    Node *prev = x->prev;

    if (prev == NULL) {
        L->first = next;
    } else {
        prev->next = next;
    }

    if (next == NULL) {
        L->last = prev;
    } else {
        next->prev = prev;
    }
    free(x);
    L->size--;
    return element;
}

/**
 * Returns the first element in this list.
 *
 * @return the first element in this list
 * @throws NoSuchElementException if this list is empty
 */
int GetFirst(LinkedList L) {
    Node *f = L.first;
    if (f == NULL) exit(-1);
    return f->val;
}

/**
 * Returns the last element in this list.
 *
 * @return the last element in this list
 * @throws NoSuchElementException if this list is empty
 */
int GetLast(LinkedList L) {
    Node *l = L.last;
    if (l == NULL) exit(-1);
    return l->val;
}

/**
 * Removes and returns the first element from this list.
 *
 * @return the first element from this list
 * @throws NoSuchElementException if this list is empty
 */
int RemoveFirst(LinkedList *L) {
    Node *f = L->first;
    if (f == NULL) exit(-1);
    return unlinkFirst_(L, f);
}

/**
 * Removes and returns the last element from this list.
 *
 * @return the last element from this list
 * @throws NoSuchElementException if this list is empty
 */
int RemoveLast(LinkedList *L) {
    Node *l = L->last;
    if (l == NULL)exit(-1);
    return unlinkLast_(L, l);
}

/**
 * Inserts the specified element at the beginning of this list.
 *
 * @param e the element to add
 */
void AddFirst(LinkedList *L, int e) {
    linkFirst_(L, e);
}

/**
 * Appends the specified element to the end of this list.
 *
 * <p>This method is equivalent to {@link #add}.
 *
 * @param e the element to add
 */
void AddLast(LinkedList *L, int e) {
    linkLast_(L, e);
}

/**
 * Returns {@code true} if this list contains the specified element.
 * More formally, returns {@code true} if and only if this list contains
 * at least one element {@code e} such that
 * {@code Objects.equals(o, e)}.
 *
 * @param o element whose presence in this list is to be tested
 * @return {@code true} if this list contains the specified element
 */
bool Contains(LinkedList L, int o) {
    return IndexOf(L, o) >= 0;
}

/**
 * Returns the number of elements in this list.
 *
 * @return the number of elements in this list
 */
int GetSize(LinkedList L) {
    return L.size;
}

/**
 * Appends the specified element to the end of this list.
 *
 * <p>This method is equivalent to {@link #addLast}.
 *
 * @param e element to be appended to this list
 * @return {@code true} (as specified by {@link Collection#add})
 */
bool Add(LinkedList *L, int e) {
    linkLast_(L, e);
    return true;
}
/**
 * Removes the first occurrence of the specified element from this list,
 * if it is present.  If this list does not contain the element, it is
 * unchanged.  More formally, removes the element with the lowest index
 * {@code i} such that
 * {@code Objects.equals(o, get(i))}
 * (if such an element exists).  Returns {@code true} if this list
 * contained the specified element (or equivalently, if this list
 * changed as a result of the call).
 *
 * @param o element to be removed from this list, if present
 * @return {@code true} if this list contained the specified element
 */
bool RemoveObject(LinkedList *L, int o) {
//    if (o == NULL) {
//        for (Node* x =L-> first; x != NULL; x = x->next) {
//            if (x->val == NULL) {
//                unlink_(L,x);
//                return true;
//            }
//        }
//    }
    for (Node *x = L->first; x != NULL; x = x->next) {
        if (o == x->val) {
            unlink_(L, x);
            return true;
        }
    }
    return false;
}

/**
 * Removes all of the elements from this list.
 * The list will be empty after this call returns.
 */
void Clear(LinkedList *L) {
    // Clearing all of the links between nodes is "unnecessary", but:
    // - helps a generational GC if the discarded nodes inhabit
    //   more than one generation
    // - is sure to free memory even if there is a reachable Iterator
    for (Node *x = L->first; x != NULL;) {
        Node *next = x->next;
        free(x);
        x = next;
    }
    L->first = NULL;
    L->last = NULL;
    L->size = 0;
}

/**
 * Returns the element at the specified position in this list.
 *
 * @param index index of the element to return
 * @return the element at the specified position in this list
 * @throws IndexOutOfBoundsException {@inheritDoc}
 */
int Get(LinkedList L, int index) {
    checkElementIndex(L, index);
    return node(L, index)->val;
}

/**
 * Replaces the element at the specified position in this list with the
 * specified element.
 *
 * @param index index of the element to replace
 * @param element element to be stored at the specified position
 * @return the element previously at the specified position
 * @throws IndexOutOfBoundsException {@inheritDoc}
 */
int Set(LinkedList *L, int index, int element) {
    checkElementIndex(*L, index);
    Node *x = node(*L, index);
    int oldVal = x->val;
    x->val = element;
    return oldVal;
}

/**
 * Inserts the specified element at the specified position in this list.
 * Shifts the element currently at that position (if any) and any
 * subsequent elements to the right (adds one to their indices).
 *
 * @param index index at which the specified element is to be inserted
 * @param element element to be inserted
 * @throws IndexOutOfBoundsException {@inheritDoc}
 */
void AddByIndex(LinkedList *L, int index, int element) {
    checkPositionIndex(*L, index);

    if (index == L->size)
        linkLast_(L, element);
    else
        linkBefore_(L, element, node(*L, index));
}

/**
 * Removes the element at the specified position in this list.  Shifts any
 * subsequent elements to the left (subtracts one from their indices).
 * Returns the element that was removed from the list.
 *
 * @param index the index of the element to be removed
 * @return the element previously at the specified position
 * @throws IndexOutOfBoundsException {@inheritDoc}
 */
int RemoveByIndex(LinkedList *L, int index) {
    checkElementIndex(*L, index);
    return unlink_(L, node(*L, index));
}

/**
 * Tells if the argument is the index of an existing element.
 */
bool isElementIndex(LinkedList L, int index) {
    return index >= 0 && index < L.size;
}

/**
 * Tells if the argument is the index of a valid position for an
 * iterator or an add operation.
 */
bool isPositionIndex(LinkedList L, int index) {
    return index >= 0 && index <= L.size;
}

/**
 * Constructs an IndexOutOfBoundsException detail message.
 * Of the many possible refactorings of the error handling code,
 * this "outlining" performs best with both server and client VMs.
 */
char *outOfBoundsMsg(LinkedList L, int index) {
    char *str = malloc(sizeof(char) * 100);
    sprintf(str, "Index: %d, Size: %d", index, +L.size);
    return str;
}

void checkElementIndex(LinkedList L, int index) {
    if (!isElementIndex(L, index)) {
        printf("%s", outOfBoundsMsg(L, index));
    }
}

void checkPositionIndex(LinkedList L, int index) {
    if (!isPositionIndex(L, index)) {
        printf("%s", outOfBoundsMsg(L, index));
    }
}

/**
 * Returns the (non-null) Node at the specified element index.
 */
Node *node(LinkedList L, int index) {
    // assert isElementIndex(index);

    if (index < (L.size >> 1)) {
        Node *x = L.first;
        for (int i = 0; i < index; i++)
            x = x->next;
        return x;
    } else {
        Node *x = L.last;
        for (int i = L.size - 1; i > index; i--)
            x = x->prev;
        return x;
    }
}

// Search Operations

/**
 * Returns the index of the first occurrence of the specified element
 * in this list, or -1 if this list does not contain the element.
 * More formally, returns the lowest index {@code i} such that
 * {@code Objects.equals(o, get(i))},
 * or -1 if there is no such index.
 *
 * @param o element to search for
 * @return the index of the first occurrence of the specified element in
 *         this list, or -1 if this list does not contain the element
 */
int IndexOf(LinkedList L, int o) {
    int index = 0;
//    if (o == NULL) {
//        for (Node *x = L.first; x != NULL; x = x->next) {
//            if (x.val == null)
//                return index;
//            index++;
//        }
//    }
    for (Node *x = L.first; x != NULL; x = x->next) {
        if (o == x->val)
            return index;
        index++;
    }
    return -1;
}

/**
 * Returns the index of the last occurrence of the specified element
 * in this list, or -1 if this list does not contain the element.
 * More formally, returns the highest index {@code i} such that
 * {@code Objects.equals(o, get(i))},
 * or -1 if there is no such index.
 *
 * @param o element to search for
 * @return the index of the last occurrence of the specified element in
 *         this list, or -1 if this list does not contain the element
 */
int lastIndexOf(LinkedList L, int o) {
    int index = L.size;
//    if (o == NULL) {
//        for (Node* x =L. last; x != NULL; x = x->prev) {
//            index--;
//            if (x->val == NULL)
//                return index;
//        }
//    }
    for (Node *x = L.last; x != NULL; x = x->prev) {
        index--;
        if (o == x->val)
            return index;
    }
    return -1;
}

// Queue operations.

/**
 * Retrieves, but does not remove, the head (first element) of this list.
 *
 * @return the head of this list, or {@code null} if this list is empty
 * @since 1.5
 */
int Peek(LinkedList L) {
    Node *f = L.first;
    return (f == NULL) ? -1 : f->val;
}

/**
 * Retrieves, but does not remove, the head (first element) of this list.
 *
 * @return the head of this list
 * @throws NoSuchElementException if this list is empty
 * @since 1.5
 */
int Element(LinkedList L) {
    return GetFirst(L);
}

/**
 * Retrieves and removes the head (first element) of this list.
 *
 * @return the head of this list, or {@code null} if this list is empty
 * @since 1.5
 */
int Poll(LinkedList *L) {
    Node *f = L->first;
    return (f == NULL) ? -1 : unlinkFirst_(L, f);
}

/**
 * Retrieves and removes the head (first element) of this list.
 *
 * @return the head of this list
 * @throws NoSuchElementException if this list is empty
 * @since 1.5
 */
int Remove(LinkedList *L) {
    return RemoveFirst(L);
}

/**
 * Adds the specified element as the tail (last element) of this list.
 *
 * @param e the element to add
 * @return {@code true} (as specified by {@link Queue#offer})
 * @since 1.5
 */
bool Offer(LinkedList *L, int e) {
    return Add(L, e);
}
/**
 * Inserts the specified element at the front of this list.
 *
 * @param e the element to insert
 * @return {@code true} (as specified by {@link Deque#offerFirst})
 * @since 1.6
 */
bool OfferFirst(LinkedList *L, int e) {
    AddFirst(L, e);
    return true;
}

/**
 * Inserts the specified element at the end of this list.
 *
 * @param e the element to insert
 * @return {@code true} (as specified by {@link Deque#offerLast})
 * @since 1.6
 */
bool OfferLast(LinkedList *L, int e) {
    AddLast(L, e);
    return true;
}

/**
 * Retrieves, but does not remove, the first element of this list,
 * or returns {@code null} if this list is empty.
 *
 * @return the first element of this list, or {@code null}
 *         if this list is empty
 * @since 1.6
 */
int PeekFirst(LinkedList *L) {
    Node *f = L->first;
    return (f == NULL) ? -1 : f->val;
}

/**
 * Retrieves, but does not remove, the last element of this list,
 * or returns {@code null} if this list is empty.
 *
 * @return the last element of this list, or {@code null}
 *         if this list is empty
 * @since 1.6
 */
int PeekLast(LinkedList *L) {
    Node *l = L->last;
    return (l == NULL) ? -1 : l->val;
}

/**
 * Retrieves and removes the first element of this list,
 * or returns {@code null} if this list is empty.
 *
 * @return the first element of this list, or {@code null} if
 *     this list is empty
 * @since 1.6
 */
int PollFirst(LinkedList *L) {
    Node *f = L->first;
    return (f == NULL) ? -1 : unlinkFirst_(L, f);
}

/**
 * Retrieves and removes the last element of this list,
 * or returns {@code null} if this list is empty.
 *
 * @return the last element of this list, or {@code null} if
 *     this list is empty
 * @since 1.6
 */
int PollLast(LinkedList *L) {
    Node *l = L->last;
    return (l == NULL) ? -1 : unlinkLast_(L, l);
}

/**
 * Pushes an element onto the stack represented by this list.  In other
 * words, inserts the element at the front of this list.
 *
 * <p>This method is equivalent to {@link #addFirst}.
 *
 * @param e the element to push
 * @since 1.6
 */
void Push(LinkedList *L, int e) {
    AddFirst(L, e);
}

/**
 * Pops an element from the stack represented by this list.  In other
 * words, removes and returns the first element of this list.
 *
 * <p>This method is equivalent to {@link #removeFirst()}.
 *
 * @return the element at the front of this list (which is the top
 *         of the stack represented by this list)
 * @throws NoSuchElementException if this list is empty
 * @since 1.6
 */
int Pop(LinkedList *L) {
    return RemoveFirst(L);
}
/**
 * Removes the first occurrence of the specified element in this
 * list (when traversing the list from head to tail).  If the list
 * does not contain the element, it is unchanged.
 *
 * @param o element to be removed from this list, if present
 * @return {@code true} if the list contained the specified element
 * @since 1.6
 */
bool removeFirstOccurrence(LinkedList *L, int o) {
    return RemoveObject(L, o);
}

/**
 * Removes the last occurrence of the specified element in this
 * list (when traversing the list from head to tail).  If the list
 * does not contain the element, it is unchanged.
 *
 * @param o element to be removed from this list, if present
 * @return {@code true} if the list contained the specified element
 * @since 1.6
 */
bool removeLastOccurrence(LinkedList *L, int o) {
//    if (o == NULL) {
//        for (Node* x = L->last; x != NULL; x = x->prev) {
//            if (x->val== NULL) {
//                unlink_(L,x);
//                return true;
//            }
//        }
//    }
    for (Node *x = L->last; x != NULL; x = x->prev) {
        if (o == x->val) {
            unlink_(L, x);
            return true;
        }
    }

    return false;
}

int *toArray(LinkedList L, int *len) {
    int *result = malloc(sizeof(int) * L.size);
    int i = 0;
    *len = L.size;
    for (Node *x = L.first; x != NULL; x = x->next)
        result[i++] = x->val;
    return result;
}

void PrintList(LinkedList L) {
    Node *p = L.first;
    printf("[");
    while (p != NULL) {
        printf("%d,", p->val);
        p = p->next;
    }
    printf("\b]\n");
}

int main1() {//链表
    LinkedList list;
    InitLinkedList(&list);
    Add(&list, 1);
    Add(&list, 4);
    Add(&list, 3);
    Add(&list, 2);
    Add(&list, 5);
    PrintList(list);//[1,4,3,2,5]
    Remove(&list);
    PrintList(list);//[4,3,2,5]
    RemoveLast(&list);//[4,3,2]
    PrintList(list);//[4,3,2]
    RemoveByIndex(&list, 1);
    PrintList(list);//[4,2]
    RemoveObject(&list, 2);
    PrintList(list);//[2]
    Clear(&list);
    return 0;
}

int main2() {//栈
    LinkedList stack;
    InitLinkedList(&stack);
    Push(&stack, 3);
    Push(&stack, 1);
    Push(&stack, 4);
    Push(&stack, 2);
    printf("%d\n", Peek(stack));//2
    while (!IsEmpty(stack)) {
        printf("%d,", Pop(&stack));//2,4,1,3
    }
    printf("\b\n");
    return 0;
}

int main3() {//队列
    LinkedList queue;
    InitLinkedList(&queue);
    Offer(&queue, 3);
    Offer(&queue, 1);
    Offer(&queue, 4);
    Offer(&queue, 2);
    printf("%d\n", Element(queue));//3
    while (!IsEmpty(queue)) {
        printf("%d,", Poll(&queue));//3,1,4,2
    }
    printf("\b\n");
    return 0;
}