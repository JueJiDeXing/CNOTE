
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "../Status.h"

typedef struct QNode {
    int data;
    struct QNode *next;
} QNode, *QueuePtr;

typedef struct {
    QueuePtr front;
    QueuePtr rear;
} LinkedQueue;
Status InitQueue(LinkedQueue *Q) {
    Q->front = malloc(sizeof(QNode));
    if (!Q->front) exit(OVERFLOW);
    Q->rear = Q->front;
    Q->front->next = Q->rear->next = NULL;
    return OK;
}

Status DestroyQueue(LinkedQueue *Q) {
    while (Q->front) {
        Q->rear = Q->front->next;
        free(Q->front);
        Q->front = Q->rear;
    }
    return OK;
}

Status ClearQueue(LinkedQueue *Q) {
    QueuePtr p1 = Q->front;
    QueuePtr p2 = p1->next;
    while (p2) {
        p1 = p2;
        p2 = p2->next;
        free(p1);
    }
    Q->rear = Q->front;
    Q->front->next = NULL;
    return OK;
}

bool QueueEmpty(LinkedQueue Q) {
    return Q.front == Q.rear;
}

int QueueLength(LinkedQueue Q) {
    QueuePtr p = Q.front->next;
    int count = 0;
    while (p) {
        count++;
        p = p->next;
    }
    return count;
}


Status GetRear(LinkedQueue Q, int *e) {
    if (QueueEmpty(Q)) exit(ERROR);
    *e = Q.rear->data;
    return OK;
}

Status GetFront(LinkedQueue Q, int *e) {
    if (QueueEmpty(Q)) exit(ERROR);
    *e = Q.front->next->data;
    return OK;
}


Status EnQueue(LinkedQueue *Q, int e) {
    QueuePtr s = malloc(sizeof(QNode));
    if (!s) exit(OVERFLOW);
    s->data = e;
    s->next = NULL;
    Q->rear->next = s;
    Q->rear = s;
    return OK;
}

Status DeQueue(LinkedQueue *Q, int *e) {
    if (QueueEmpty(*Q)) exit(OVERFLOW);
    QueuePtr p = Q->front->next;
    *e = p->data;

    Q->front->next = p->next;
    if (p == Q->rear) {
        Q->rear = Q->front;
    }
    free(p);
    return OK;
}

Status QueueTraverse(LinkedQueue *Q, int visit(int)) {
    QueuePtr p = Q->front->next;
    while (p) {
        visit(p->data);
        p = p->next;
    }
    return OK;
}

void PrintQueue(LinkedQueue Q) {
    QueuePtr p = Q.front->next;
    printf("Queue:");
    while (p) {
        printf("%d ", p->data);
        p = p->next;
    }
    printf("\n");
}