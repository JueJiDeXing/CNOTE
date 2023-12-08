// Author: 绝迹的星 
// Created on 2023/12/8


#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

#include "../Structures/树/Tree.c"


typedef struct QNode {
    TreeNode *data;
    struct QNode *next;

} QNode, *QueuePtr;

typedef struct {
    QueuePtr front;
    QueuePtr rear;
    int size;
} LinkedQueue;

void InitQueue(LinkedQueue *Q) {
    Q->front = malloc(sizeof(QNode));
    if (!Q->front) exit(-1);
    Q->rear = Q->front;
    Q->front->next = Q->rear->next = NULL;
    Q->size = 0;
}


bool QueueEmpty(LinkedQueue Q) {
    return Q.size == 0;
}

int QueueLength(LinkedQueue Q) {
    return Q.size;
}

void EnQueue(LinkedQueue *Q, TreeNode *e) {
    QueuePtr s = malloc(sizeof(QNode));
    if (!s) exit(-1);
    s->data = e;
    s->next = NULL;
    Q->rear->next = s;
    Q->rear = s;
    Q->size++;
}

void DeQueue(LinkedQueue *Q, TreeNode **e) {
    if (QueueEmpty(*Q)) exit(-1);
    QueuePtr p = Q->front->next;
    *e = p->data;

    Q->front->next = p->next;
    if (p == Q->rear) {
        Q->rear = Q->front;
    }
    free(p);
    Q->size--;
}

bool isComplete(Tree tree) {
    LinkedQueue queue;
    InitQueue(&queue);
    if (tree == NULL) {
        return true;
    }
    EnQueue(&queue, tree);
    bool seenNULL = false; // 是否遇见空节点

    while (!QueueEmpty(queue)) {
        TreeNode *curr;
        DeQueue(&queue, &curr);
        if (seenNULL && curr != NULL) { // 如果已经遇见空节点,还有右侧非空节点
            return false;
        }
        if (curr == NULL) {
            seenNULL = true; // 遇见空节点
        } else {
            // 将左右孩子节点入队
            EnQueue(&queue, curr->left);
            EnQueue(&queue, curr->right);
        }
    }
    return true;
}

int main() {
    /*测试1
        *    3
        *  4    5
        * 1 2
        */
    Tree tree1;
    CreateTree(&tree1, "341  2  5  ", 12);
    printf("测试1(应为true):%d", isComplete(tree1));
    printf("\n");
    /*测试2
       *    3
       *  4    5
       * 1    2
       */
    Tree tree2;
    char arr2[] = "341   52   ";
    CreateTree(&tree2, arr2, strlen(arr2));
    printf("测试2(应为false):%d", isComplete(tree2));
    printf("\n");

    /*测试3
      *    3
      *  4    5
      */
    Tree tree3;
    char arr3[] = "34  5  ";
    CreateTree(&tree3, arr3, strlen(arr3));
    printf("测试3(应为true):%d", isComplete(tree3));
    printf("\n");
}