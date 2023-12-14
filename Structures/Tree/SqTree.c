// Author: 绝迹的星 
// Created on 2023/11/8
// - Hello World.
// - You are my world too.

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>


typedef struct Tree {
    int *nodes;
    int n;
    int capacity;
} Tree;

void InitTree(Tree *tree, int capacity) {
    tree->capacity = capacity + 1;
    tree->n = 1;//第0位不放节点
    tree->nodes = malloc(sizeof(int) * tree->capacity);
}

void put(Tree *tree, int v) {
    if (tree->n == tree->capacity) {
        return;
    }
    tree->nodes[tree->n++] = v;
}

enum {
    prev, in, post
};

/**
 前序遍历<br>
 左孩子索引=父索引*2 ; 右孩子索引=父索引*2+1
 */
void doOrder(int start, Tree *tree, int method) {
    if (start >= tree->n) return;

    if (method == prev) printf("%d,", tree->nodes[start]);//前序
    int leftIndex = start <<1;
    doOrder(leftIndex, tree, method);//左
    if (method == in)printf("%d,", tree->nodes[start]);//中序
    doOrder(leftIndex | 1, tree, method);//右
    if (method == post) printf("%d,", tree->nodes[start]);//后序

}

/**
 前序遍历
 */
void prevOrder(Tree *tree) {
    doOrder(1, tree, prev);
    printf("\b\n");
}

/**
 前序遍历
 */
void inOrder(Tree *tree) {
    doOrder(1, tree, in);
    printf("\b\n");
}

/**
 前序遍历
 */
void postOrder(Tree *tree) {
    doOrder(1, tree, post);
    printf("\b\n");
}

int main() {
    Tree tree;
    InitTree(&tree, 16);
    /*
     *  [x,1,2,3,4,5,6,7]
     *       1
     *    2    3
     *   4 5  6 7
     *   前:1,2,4,5,3,6,7
     *   中:4,2,5,1,6,3,7
     *   后:4,5,2,6,7,3,1
     */
    put(&tree, 1);
    put(&tree, 2);
    put(&tree, 3);
    put(&tree, 4);
    put(&tree, 5);
    put(&tree, 6);
    put(&tree, 7);
    prevOrder(&tree);//1,2,4,5,3,6,7
    inOrder(&tree);//4,2,5,1,6,3,7
    postOrder(&tree);//4,5,2,6,7,3,1
}