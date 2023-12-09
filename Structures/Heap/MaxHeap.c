// Author: 绝迹的星 
// Created on 2023/12/9


#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

#define DefaultSize 100
//大顶堆,每个节点都比它的孩子节点大,堆顶始终为最大值
typedef struct MaxHeap {
    int array[DefaultSize];
    int size;//当前元素个数
    int capacity;//最大容量
} MaxHeap;

void down(MaxHeap *heap, int parent);

void up(MaxHeap *heap, int offer);

void Heapify(MaxHeap *heap);

void InitHeapByCapacity(MaxHeap *heap, int capacity) {
    heap->size = 0;
    heap->capacity = capacity;
    for (int i = 0; i < capacity; i++) {
        heap->array[i] = 0;
    }
}

bool IsEmpty(MaxHeap heap) {
    return heap.size == 0;
}

bool IsFull(MaxHeap heap) {
    return heap.size == heap.capacity;
}

void swap(MaxHeap *heap, int i, int j) {
    int t = heap->array[i];
    heap->array[i] = heap->array[j];
    heap->array[j] = t;
}

/**
 * 传入一个数组,将其建成大顶堆堆
 */
void InitHeap(MaxHeap *heap, const int arr[], int len, int capacity) {
    heap->size = len;
    heap->capacity = capacity;
    for (int i = 0; i < len; i++) {
        heap->array[i] = arr[i];
    }
    Heapify(heap);
}

/**
 <h1>弗洛伊德 建堆算法</h1>
 1. 找到最后一个非叶子节点<br>
 2. 从后往前依次找非叶子节点进行下潜<br>
 <h2>时间复杂度:</h2>
 总交换次数:最底层交换0次,倒数第二层交换1次,...,第i层交换i-1次<br>
 [i=1 ~ h] ∑ ( (2^h / 2^i) * (i - 1) ) = 2^h - h - 1  <br>
 由于2^h ≈ n, h≈ log_2_ n ,所以时间复杂度为O(n)
 */
void Heapify(MaxHeap *heap) {
    for (int i = heap->size / 2 - 1; i >= 0; i--) {
        down(heap, i);
    }
}

/**
 * 小元素下潜
 * @param heap Heap
 * @param parent  父节点索引
 */
void down(MaxHeap *heap, int parent) {
    int left = 2 * parent + 1;
    int right = left + 1;
    int max = parent;//寻找 父,左,右 三者最大的元素
    if (left < heap->size && heap->array[left] > heap->array[max]) {
        max = left;
    }
    if (right < heap->size && heap->array[right] > heap->array[max]) {
        max = right;
    }
    if (max != parent) {//如果子节点比父节点优先级大
        swap(heap, parent, max);// 交换
        down(heap, max);//递归,直到max==parent(父节点大于左右子节点)时停止
    }
}

/**
 * 添加元素到堆底,然后开始上浮
 */
void up(MaxHeap *heap, int offered) {
    int child = heap->size;
    int parent = (child - 1) / 2;
    while (child > 0 && offered > heap->array[parent]) {
        heap->array[child] = heap->array[parent];//offered比父节点大,将offered上浮
        child = parent;
        parent = (parent - 1) / 2;
    }
    heap->array[child] = offered;//插入
}

bool Offer(MaxHeap *heap, int offered) {
    if (IsFull(*heap)) {
        return false;
    }
    up(heap, offered);
    heap->size++;
    return true;
}

/**
 * 获取堆顶元素(堆内的最大值)
 */
int Peek(MaxHeap heap) {
    if (IsEmpty(heap)) {
        exit(-1);
    }
    return heap.array[0];//返回堆顶元素
}

/**
 * 抛出堆顶元素(堆内的最大值)
 */
int Poll(MaxHeap *heap) {
    if (IsEmpty(*heap)) {
        exit(-1);
    }
    swap(heap, 0, heap->size - 1);//交换头元素与尾元素再将尾元素抛出
    heap->size--;
    int value = heap->array[heap->size];
    down(heap, 0);//下潜
    return value;
}

/**
 * 替换堆顶元素
 * @param replaced 要替换的值
 */
void Replace(MaxHeap *heap, int replaced) {
    if (IsEmpty(*heap)) {
        exit(-1);
    }
    heap->array[0] = replaced;
    down(heap, 0);//下潜维持大顶堆的特性
}

int main1() {//测试
    MaxHeap heap;
    int arr[] = {1, 3, 4, 2, 5, 6};
    int len = sizeof(arr) / sizeof(int);
    InitHeap(&heap, arr, len, len);
    while (!IsEmpty(heap)) {
        printf("%d,", Poll(&heap));//6,5,4,3,2,1,
    }
    return 0;
}

int main2() {//测试2
    MaxHeap heap;
    int arr[] = {1, 3, 8, 2, 5, 6};
    int len = sizeof(arr) / sizeof(int);
    InitHeap(&heap, arr, len, 10);
    Offer(&heap, 7);
    Offer(&heap, 4);
    while (!IsEmpty(heap)) {
        printf("%d,", Poll(&heap));//8,7,6,5,4,3,2,1,
    }
    return 0;
}