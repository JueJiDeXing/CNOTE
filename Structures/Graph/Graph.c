// Author: 绝迹的星 
// Created on 2023/12/6


#include <stdio.h>
#include <stdbool.h>
#include "../Status.h"
#include "../Queue/LinkedQueue.c"

#define MAX_VERTEX_NUM 20                  // 最大顶点数

//Graph
typedef struct {
    int vertexVal[MAX_VERTEX_NUM];  //顶点向量
    int matrix[MAX_VERTEX_NUM][MAX_VERTEX_NUM];     //邻接矩阵
    int numOfVertex, numOfEdge; // 顶点数和弧数
} MGraph;

/**
 * 根据顶点值查找顶点索引
 */
int LocateVex(MGraph G, int val) {
    for (int i = 0; i < G.numOfVertex; i++) {
        if (G.vertexVal[i] == val) return i;
    }
    return ERROR;
}

/**
 * 邻接矩阵建图
 */
Status CreateUDN(MGraph *G) {
    // 采用数组(邻接矩阵)表示法,构造无网图G
    printf("Enter: vexnum, arcnum:\n");
    scanf("%d %d", &(G->numOfVertex), &(G->numOfEdge));
    printf("请输入顶点向量:\n");
    for (int i = 0; i < G->numOfVertex; i++)
        scanf("%d", &G->vertexVal[i]);              //构建顶点向量

    for (int i = 0; i < G->numOfVertex; i++)     // 初始化邻接矩阵
        for (int j = 0; j < G->numOfVertex; j++) {
            G->matrix[i][j] = 0;
        }

    for (int k = 0; k < G->numOfEdge; k++) {   // 构造邻接矩阵
        printf("请输入第%d条边依附的顶点以及权值:\n", k + 1);
        int v1, v2, w;
        scanf("%d %d %d", &v1, &v2, &w); //记得输入第几个顶点
        G->matrix[v1 - 1][v2 - 1] = w;   // 弧<v1, v2>的权值
        G->matrix[v2 - 1][v1 - 1] = w;  // 对称弧
    }
    return OK;
}

/**
 *
 * 邻接矩阵建图
 * @param values 顶点数组,values[i]=v 表示顶点i的值为v
 * @param n 顶点数
 * @param edges  边数组,edges[i]=[start,end,weight]表示 第i条边 为 顶点start->end 边权为weight
 * @param numOfEdges  边数
 */
Status CreateGraph(MGraph *G, const int *values, int n, int *edges, int numOfEdges) {
    G->numOfVertex = n;
    G->numOfEdge = numOfEdges;

    for (int i = 0; i < n; i++) {//顶点向量
        G->vertexVal[i] = values[i];
    }

    for (int i = 0; i < G->numOfVertex; i++) {    // 初始化邻接矩阵
        for (int j = 0; j < G->numOfVertex; j++) {
            G->matrix[i][j] = 0;
        }
    }
    for (int k = 0; k < G->numOfEdge; k++) {   // 构造邻接矩阵
        int *start = edges + k * 3,
                *end = start + 1,
                *weight = end + 1;
        G->matrix[*start][*end] = *weight;   // 弧<v1, v2>的权值
        G->matrix[*end][*start] = *weight;  // 对称弧
    }
    return OK;
}

/**
 * 查找顶点v的第一个邻居索引
 * @return 如果没有邻居,返回-1
 */
int FirstAdjVex(MGraph G, int v) {
    for (int j = 0; j < G.numOfVertex; j++) {
        if (G.matrix[v][j] != 0) return j;  //返回索引
    }
    return -1;//没有邻居
}

/**
 * 查找顶点v的下一个邻居索引
 * @param curr 当前邻居索引
 * @return 如果没有下一个邻居了,返回-1
 */
int NextAdjVex(MGraph G, int v, int curr) {
    for (int j = curr + 1; j < G.numOfVertex; j++) { // 从索引的下一个开始
        if (G.matrix[v][j] != 0) return j;
    }
    return -1;//没有下一个邻居了
}


Status visit(int v) {
    printf("%d -> ", v);
    return OK;
}

// 这里是无权图
void BFSTraverse(MGraph G, Status (*visit)(int v)) {
    LinkedQueue Q;//使用队列
    InitQueue(&Q);

    bool isVisited[G.numOfVertex];
    for (int i = 1; i < G.numOfVertex; i++) {
        isVisited[i] = false;
    }
    //从节点0开始广度优先搜索
    EnQueue(&Q, 0);
    int v = 0;
    visit(v);
    isVisited[v] = true;
    while (!QueueEmpty(Q)) {
        //每次出队一个节点
        DeQueue(&Q, &v);
        //遍历它的邻居并入队
        for (int w = FirstAdjVex(G, v); w >= 0; w = NextAdjVex(G, v, w)) {
            if (isVisited[w]) continue;
            visit(w);
            isVisited[w] = true;
            EnQueue(&Q, w);
        }
    }
}

void DFS(MGraph G, int curr, bool isVisited[]) {
    //访问当前搜索的节点
    isVisited[curr] = true;
    visit(curr);
    //搜索它的所有邻居节点
    for (int w = FirstAdjVex(G, curr); w >= 0; w = NextAdjVex(G, curr, w)) {
        if (!isVisited[w]) {
            DFS(G, w, isVisited);
        }
    }
}

void DFSTraverse(MGraph G, Status (*visit)(int v)) {
    //初始化isVisited数组
    bool isVisited[G.numOfVertex];
    for (int v = 0; v < G.numOfVertex; v++) {
        isVisited[v] = false;
    }
    DFS(G, 0, isVisited);//从起点0开始深度优先搜索
}

int main() {
    int edges[9][3] = {
            {0, 1, 1},
            {0, 5, 2},
            {1, 2, 5},
            {2, 4, 1},
            {1, 3, 4},
            {4, 3, 3},
            {5, 6, 2},
            {5, 7, 6},
            {6, 7, 3},
    };
    int values[8] = {0, 1, 2, 3, 4, 5, 6, 7};
    MGraph graph;
    CreateGraph(&graph, values, 8, (int *) edges, sizeof(edges) / sizeof(edges[0]));
    DFSTraverse(graph, visit);
    printf("\n");
    BFSTraverse(graph, visit);
}