// Author: 绝迹的星 
// Created on 2023/12/9

#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

//6个顶点
#define N 6

int chooseMinDistanceVertex(const int *distance, const bool *isVisited, int n) {
    int min = INT_MAX;
    int minIndex = 0;
    for (int i = 0; i < n; i++) {
        if (distance[i] == 0 || isVisited[i]) continue;
        if (distance[i] < min) {
            min = distance[i];
            minIndex = i;
        }
    }
    return minIndex;
}

void updateNeighboursDistance(int graph[][N], int *distance, const bool *isVisited, int v, int n) {
    int *edges = graph[v];
    for (int i = 0; i < n; i++) {//遍历顶点v的所有邻居
        if (edges[i] == 0 || isVisited[i]) continue; // list.contains(n)
        //更新最短路径
        if (edges[i] < distance[i]) {//距离不累加,直接表示为与上一个顶点的距离
            distance[i] = edges[i];
        }
    }
}

/**
 <h1>Prim 最小生成树算法-邻接矩阵格式输入</h1>
 1.将所有顶点标记为未访问<br>
 2.设置临时距离:起点设为0,其余设为无穷大<br>
 3.每次选择最小临时距离的未访问点作为当前顶点<br>
 4.遍历当前顶点邻居,更新邻居的距离值 min(邻居距离,边权)<br>
 5.当前顶点处理完所有邻居后当前顶点设为已访问<br>
 与Dijkstra算法仅在第4步不同,距离不累加,而是表示距离上一个节点的距离

 @param graph 输入,无向带权图,邻接矩阵 大小 n * n
 @param n 输入,顶点个数
 @param path 输出, 边集path[i]=[start,end] ,大小 (n-1) * 2
 */
void prim(int graph[][N], int path[N - 1][2]) {
    int pathNum = 0;
    bool isVisited[N];
    for (int i = 0; i < N; i++) {
        isVisited[i] = false;
    }
    int numOfVisit = 0;
    int distance[N];
    for (int i = 1; i < N; i++) {
        distance[i] = INT_MAX;
    }
    distance[0] = 0;//起点临时距离设为0
    int prev = 0;//上次选择的节点
    while (numOfVisit < N) {
        int current = chooseMinDistanceVertex(distance, isVisited, N);//选择最小的临时距离的未访问点
        updateNeighboursDistance(graph, distance, isVisited, current, N);//更新它的邻居的距离
        if (numOfVisit != 0) {//第一个不记录,因为第一个是 起点-起点
            path[pathNum][0] = prev;
            path[pathNum][1] = current;//记录路径
            pathNum++;
        }
        prev = current;
        isVisited[current] = true;//设为已访问
        numOfVisit++;
    }
}

int main1() {//测试
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
    int path[n - 1][2];
    prim(graph, path);
    for (int i = 0; i < n - 1; i++) {
        printf("%d-%d,", path[i][0], path[i][1]);//0-1,1-3,3-4,4-5,5-2
    }
    printf("\b");
    return 0;
}