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

boolean isEmpty(PriorityQueue queue) {
    return queue.size == 0;
}

boolean isFull(PriorityQueue queue) {
    return queue.size == queue.capacity;
}

bool offer(PriorityQueue *queue, int value, int priority) {
    if (isFull(*queue)) {
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

int poll(PriorityQueue *queue) {
    if (isEmpty(*queue)) {
        exit(-1);
    }
    int max = selectMax(queue);
    int value = queue->array[max].val;
    Remove(queue, max);
    return value;
}


int peek(PriorityQueue *queue) {
    if (isEmpty(*queue)) {
        exit(-1);
    }
    int index = selectMax(queue);
    return queue->array[index].val;
}
//TODO
int main() {

}