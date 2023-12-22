// Author: �������� 
// Created on 2023/12/6


#include <stdio.h>
#include <stdbool.h>
#include "../Status.h"
#include "../Queue/LinkedQueue.c"

#define MAX_VERTEX_NUM 20                  // ��󶥵���

//Graph
typedef struct {
    int vertexVal[MAX_VERTEX_NUM];  //��������
    int matrix[MAX_VERTEX_NUM][MAX_VERTEX_NUM];     //�ڽӾ���
    int numOfVertex, numOfEdge; // �������ͻ���
} MGraph;

/**
 * ���ݶ���ֵ���Ҷ�������
 */
int LocateVex(MGraph G, int val) {
    for (int i = 0; i < G.numOfVertex; i++) {
        if (G.vertexVal[i] == val) return i;
    }
    return ERROR;
}

/**
 * �ڽӾ���ͼ
 */
Status CreateUDN(MGraph *G) {
    // ��������(�ڽӾ���)��ʾ��,��������ͼG
    printf("Enter: vexnum, arcnum:\n");
    scanf("%d %d", &(G->numOfVertex), &(G->numOfEdge));
    printf("�����붥������:\n");
    for (int i = 0; i < G->numOfVertex; i++)
        scanf("%d", &G->vertexVal[i]);              //������������

    for (int i = 0; i < G->numOfVertex; i++)     // ��ʼ���ڽӾ���
        for (int j = 0; j < G->numOfVertex; j++) {
            G->matrix[i][j] = 0;
        }

    for (int k = 0; k < G->numOfEdge; k++) {   // �����ڽӾ���
        printf("�������%d���������Ķ����Լ�Ȩֵ:\n", k + 1);
        int v1, v2, w;
        scanf("%d %d %d", &v1, &v2, &w); //�ǵ�����ڼ�������
        G->matrix[v1 - 1][v2 - 1] = w;   // ��<v1, v2>��Ȩֵ
        G->matrix[v2 - 1][v1 - 1] = w;  // �Գƻ�
    }
    return OK;
}

/**
 *
 * �ڽӾ���ͼ
 * @param values ��������,values[i]=v ��ʾ����i��ֵΪv
 * @param n ������
 * @param edges  ������,edges[i]=[start,end,weight]��ʾ ��i���� Ϊ ����start->end ��ȨΪweight
 * @param numOfEdges  ����
 */
Status CreateGraph(MGraph *G, const int *values, int n, int *edges, int numOfEdges) {
    G->numOfVertex = n;
    G->numOfEdge = numOfEdges;

    for (int i = 0; i < n; i++) {//��������
        G->vertexVal[i] = values[i];
    }

    for (int i = 0; i < G->numOfVertex; i++) {    // ��ʼ���ڽӾ���
        for (int j = 0; j < G->numOfVertex; j++) {
            G->matrix[i][j] = 0;
        }
    }
    for (int k = 0; k < G->numOfEdge; k++) {   // �����ڽӾ���
        int *start = edges + k * 3,
                *end = start + 1,
                *weight = end + 1;
        G->matrix[*start][*end] = *weight;   // ��<v1, v2>��Ȩֵ
        G->matrix[*end][*start] = *weight;  // �Գƻ�
    }
    return OK;
}

/**
 * ���Ҷ���v�ĵ�һ���ھ�����
 * @return ���û���ھ�,����-1
 */
int FirstAdjVex(MGraph G, int v) {
    for (int j = 0; j < G.numOfVertex; j++) {
        if (G.matrix[v][j] != 0) return j;  //��������
    }
    return -1;//û���ھ�
}

/**
 * ���Ҷ���v����һ���ھ�����
 * @param curr ��ǰ�ھ�����
 * @return ���û����һ���ھ���,����-1
 */
int NextAdjVex(MGraph G, int v, int curr) {
    for (int j = curr + 1; j < G.numOfVertex; j++) { // ����������һ����ʼ
        if (G.matrix[v][j] != 0) return j;
    }
    return -1;//û����һ���ھ���
}


Status visit(int v) {
    printf("%d -> ", v);
    return OK;
}

// ��������Ȩͼ
void BFSTraverse(MGraph G, Status (*visit)(int v)) {
    LinkedQueue Q;//ʹ�ö���
    InitQueue(&Q);

    bool isVisited[G.numOfVertex];
    for (int i = 1; i < G.numOfVertex; i++) {
        isVisited[i] = false;
    }
    //�ӽڵ�0��ʼ�����������
    EnQueue(&Q, 0);
    int v = 0;
    visit(v);
    isVisited[v] = true;
    while (!QueueEmpty(Q)) {
        //ÿ�γ���һ���ڵ�
        DeQueue(&Q, &v);
        //���������ھӲ����
        for (int w = FirstAdjVex(G, v); w >= 0; w = NextAdjVex(G, v, w)) {
            if (isVisited[w]) continue;
            visit(w);
            isVisited[w] = true;
            EnQueue(&Q, w);
        }
    }
}

void DFS(MGraph G, int curr, bool isVisited[]) {
    //���ʵ�ǰ�����Ľڵ�
    isVisited[curr] = true;
    visit(curr);
    //�������������ھӽڵ�
    for (int w = FirstAdjVex(G, curr); w >= 0; w = NextAdjVex(G, curr, w)) {
        if (!isVisited[w]) {
            DFS(G, w, isVisited);
        }
    }
}

void DFSTraverse(MGraph G, Status (*visit)(int v)) {
    //��ʼ��isVisited����
    bool isVisited[G.numOfVertex];
    for (int v = 0; v < G.numOfVertex; v++) {
        isVisited[v] = false;
    }
    DFS(G, 0, isVisited);//�����0��ʼ�����������
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