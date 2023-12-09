// Author: 绝迹的星 
// Created on 2023/12/9

#include <stdlib.h>
#include "../../DisJointSet/DisJointSet.c"

//6个顶点
#define N 6

//边
typedef struct Edge {
    int start, end, weight;//起点-终点-权重
} Edge;

void InitEdge(Edge *edge, int start, int end, int weight) {
    edge->start = start;
    edge->end = end;
    edge->weight = weight;
}

typedef struct MinHeap {
    Edge array[DefaultSize];
    int size;//当前元素个数
    int capacity;//最大容量
} MinHeap;

void InitHeapByCapacity(MinHeap *heap, int capacity) {
    heap->size = 0;
    heap->capacity = capacity;
}

void swap(MinHeap *heap, int i, int j) {
    Edge t = heap->array[i];
    heap->array[i] = heap->array[j];
    heap->array[j] = t;
}

/**
 * 大元素下潜
 * @param heap Heap
 * @param parent  父节点索引
 */
void down(MinHeap *heap, int parent) {
    int left = 2 * parent + 1;
    int right = left + 1;
    int min = parent;//寻找 父,左,右 三者最小的元素
    if (left < heap->size && heap->array[left].weight < heap->array[min].weight) {//按weight比较
        min = left;
    }
    if (right < heap->size && heap->array[right].weight < heap->array[min].weight) {
        min = right;
    }
    if (min != parent) {//如果子节点比父节点优先级大
        swap(heap, parent, min);// 交换
        down(heap, min);//递归,直到max==parent(父节点大于左右子节点)时停止
    }
}

/**
 * 添加元素到堆底,然后开始上浮
 */
void up(MinHeap *heap, Edge offered) {
    int child = heap->size;
    int parent = (child - 1) / 2;
    while (child > 0 && offered.weight < heap->array[parent].weight) {
        heap->array[child] = heap->array[parent];//offered比父节点大,将offered上浮
        child = parent;
        parent = (parent - 1) / 2;
    }
    heap->array[child] = offered;//插入
}

/**
 * 添加元素到堆中
 */
void Offer(MinHeap *heap, Edge offered) {
    up(heap, offered);
    heap->size++;
}

/**
 * 抛出堆顶元素(堆内的最小值)
 */
Edge Poll(MinHeap *heap) {
    swap(heap, 0, heap->size - 1);//交换头元素与尾元素再将尾元素抛出
    heap->size--;
    Edge value = heap->array[heap->size];
    down(heap, 0);//下潜
    return value;
}

/**
 <h1>Kruskal 最小生成树算法</h1>
 1.将所有顶点设为"不连通" (使用并查集表达连通状态)<br>
 2.将所有边按边权升序<br>
 3.每次选择最小权边,如果两端是不连通的,则将两端连通<br>

 @param queue 小顶堆,使用优先级队列存储边,每次获取权重最小的边
 */
Edge *doKruskal(MinHeap queue) {
    Edge *path = malloc(sizeof(Edge) * (N - 1));
    int edgeNum = 0;
    DisJointSet set;
    InitDisJoinSet(&set);//使用并查集进行连通操作
    while (edgeNum < N - 1) {//n个顶点要连接n-1条边
        Edge poll = Poll(&queue);//获取权重最小的边
        int i = Find(&set, poll.start);//查找集合的老大
        int j = Find(&set, poll.end);
        if (i != j) {//在一个集合里的所有元素的老大都是相等的,如果ij不等,说明start和end在两个集合中
            //没有连通
            Union(&set, i, j);//将i,j集合设为连通
            path[edgeNum++] = poll;//加这条边
        }
    }
    return path;
}

Edge *kruskal(int graph[][N]) {
    MinHeap queue;
    InitHeapByCapacity(&queue, N);
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            if (graph[i][j] != 0) {
                Edge edge;
                InitEdge(&edge, i, j, graph[i][j]);
                Offer(&queue, edge);
            }
        }
    }
    return doKruskal(queue);
}

int main_1() {//测试
    /*
                   2                              2
              v1------ v3                     v1 ---- v3
            1/  6\  4/  2\                  1/          2\
           v0     v2     v4                v0     v2     v4
            5\    4\   /2                          4\   /2
               ----- v5                               v5

         */
    int n = 6;
    int graph[][6] = {{0, 1, 0, 0, 0, 5},
                      {1, 0, 6, 2, 0, 0},
                      {0, 6, 0, 4, 0, 4},
                      {0, 2, 4, 0, 2, 0},
                      {0, 0, 0, 2, 0, 2},
                      {5, 0, 4, 0, 2, 0}};

    Edge *path = kruskal(graph);
    for (int i = 0; i < n - 1; i++) {
        printf("%d-%d,", path[i].start, path[i].end);//0-1,1-3,3-4,4-5,5-2
    }
    printf("\b");
    return 0;
}