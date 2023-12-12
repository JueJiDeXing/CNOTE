// Author: 绝迹的星 
// Created on 2023/12/10


#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

#define DefaultSize 100
#define boolean bool

typedef struct Priority {
    int val;
    int priority;
} Priority;

typedef struct PriorityQueue {
    Priority array[DefaultSize];
    int size;
    int capacity;
} PriorityQueue;

void InitPriorityQueue(PriorityQueue *queue, int capacity) {
    queue->size = 0;
    queue->capacity = capacity;
}

boolean IsEmpty(PriorityQueue queue) {
    return queue.size == 0;
}

boolean IsFull(PriorityQueue queue) {
    return queue.size == queue.capacity;
}

bool Offer(PriorityQueue *queue, int value, int priority) {
    if (IsFull(*queue)) {
        return false;
    }
    Priority data = {value, priority};
    queue->array[queue->size++] = data;
    return true;
}

/**
 * @return 返回优先级最高的索引值
 */
int selectMax(PriorityQueue *queue) {
    int max = 0;
    for (int i = 0; i < queue->size; i++) {
        if (queue->array[i].priority > queue->array[max].priority) {
            max = i;
        }
    }
    return max;
}

void Remove(PriorityQueue *queue, int index) {
    for (int i = 0; i < queue->size - index - 1; i++) {
        queue->array[i + index] = queue->array[i + index + 1];
    }
    queue->size--;
}

int Poll(PriorityQueue *queue) {
    if (IsEmpty(*queue)) {
        exit(-1);
    }
    int max = selectMax(queue);
    int value = queue->array[max].val;
    Remove(queue, max);
    return value;
}


int Peek(PriorityQueue *queue) {
    if (IsEmpty(*queue)) {
        exit(-1);
    }
    int index = selectMax(queue);
    return queue->array[index].val;
}

int main1() {
    PriorityQueue queue;
    InitPriorityQueue(&queue, 10);
    Offer(&queue, 5, 5);
    Offer(&queue, 3, 3);
    Offer(&queue, 4, 4);
    Offer(&queue, 1, 1);
    Offer(&queue, 2, 2);
    while (!IsEmpty(queue)) {
        printf("%d,", Poll(&queue));//5,4,3,2,1 权重由大到小抛出
    }
    printf("\b");
    return 0;
}