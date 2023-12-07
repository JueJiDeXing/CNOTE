// Author: 绝迹的星 
// Created on 2023/11/8


#include <stdio.h>
#include "Status.c"
#include "stdlib.h"
#include "stdbool.h"

typedef struct SqQueue {
    int head;
    int tail;
    int *elem;
} SqQueue;

/**
 * 初始化队列(循环数组)
 * @param queue
 * @return
 */
Status InitQueue(SqQueue *queue) {
    queue->elem = malloc(sizeof(int) * DEFAULT_SIZE);
    if (!queue->elem) {
        exit(ERROR);
    }
    queue->head = 0;
    queue->tail = 0;
    return OK;
}
/**
 * 判断队列是否已满
 * @param queue
 * @return
 */
bool IsFull(SqQueue queue) {
    return (queue.tail + 1) % DEFAULT_SIZE == queue.head;
}
/**
 * 判断队列是否为空
 * @param queue
 * @return
 */
bool IsEmpty(SqQueue queue) {
    return queue.head == queue.tail;
}

/**
 * 添加元素到队列尾部
 * @param queue
 * @param e
 * @return
 */
Status Offer(SqQueue *queue, int e) {
    if (IsFull(*queue)) {
        exit(ERROR);
    }
    queue->elem[queue->tail] = e;
    queue->tail = (queue->tail + 1) % DEFAULT_SIZE;
    return OK;
}

/**
 * 弹出队列头部元素
 * @param queue
 * @param e
 * @return
 */
Status Poll(SqQueue *queue, int *e) {
    if (IsEmpty(*queue)) {
        exit(ERROR);
    }
    *e = queue->elem[queue->head];
    queue->head = (queue->head + 1) % DEFAULT_SIZE;
    return OK;
}

/**
 * 获取队列头部元素
 * @param queue
 * @return
 */
int Peek(SqQueue queue) {
    if (IsEmpty(queue)) {
        exit(ERROR);

    }
    return queue.elem[queue.head];
}

int GetTail(SqQueue queue) {
    if (IsEmpty(queue)) {
        exit(ERROR);
    }
    return queue.elem[queue.tail];
}

/**
 * 获取队列元素个数
 * @param queue
 * @return
 */
int GetLength(SqQueue queue) {
    return (queue.tail + DEFAULT_SIZE - queue.head) % DEFAULT_SIZE;
}

/**
 * 打印队列
 * @param queue
 */
void PrintQueue(SqQueue queue) {
    int len = GetLength(queue);
    printf("[");
    for (int i = 0; i < len; i++) {
        printf("%d", queue.elem[(i + queue.head) % DEFAULT_SIZE]);
        if (i != len - 1) {
            printf(",");
        }
    }
    printf("]\n");
}

void ClearQueue(SqQueue *queue) {
    queue->head = queue->tail = 0;
    free(queue->elem);
}