// Author: 绝迹的星 
// Created on 2023/11/8
// - Hello World.
// - You are my world too.




#include "Status.c"
#include "stdlib.h"
#include "stdbool.h"

typedef struct Node {
    int data;
    struct Node *left;
    struct Node *right;
} Node;

typedef struct Tree {
    Node *root;
} Tree;

Status InitTree(Tree *tree) {
    tree = malloc(sizeof(Tree));
    if (!tree) {
        exit(ERROR);
    }
    (*tree).root = malloc(sizeof(Node));
    if (!(*tree).root) {
        exit(ERROR);
    }
    (*tree).root = NULL;
    return OK;
}

bool IsEmpty(Tree tree) {
    return tree.root == NULL;
}

Status Put(Tree *tree) {
    Node *p = tree->root;

}