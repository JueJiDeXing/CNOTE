// Author: 绝迹的星
// Created on 2023/11/26


#include <stdio.h>
#include <malloc.h>

typedef struct TreeNode {
    int val;
    struct TreeNode *left;
    struct TreeNode *right;
} TreeNode, *Tree;

//前序遍历
void PreOrderTraverse(Tree T) {
    if (T == NULL) {
        return;
    }
    printf("%c ", T->val);
    PreOrderTraverse(T->left);
    PreOrderTraverse(T->right);
}

//中序遍历
void InOrderTraverse(Tree T) {
    if (T == NULL) {
        return;
    }
    PreOrderTraverse(T->left);
    printf("%c ", T->val);
    PreOrderTraverse(T->right);
}

//后序遍历
void PostOrderTraverse(Tree T) {
    if (T == NULL) {
        return;
    }
    PreOrderTraverse(T->left);
    PreOrderTraverse(T->right);
    printf("%c ", T->val);
}


void CreateTreeByScanf(Tree *T) { //注意 这里使用二级指针，因为我们要修改指针的值
    char ch;
    scanf("%c", &ch);
    getchar();
    if (ch == ' ') {
        *T = NULL;
        return;
    }
    *T = (TreeNode *) malloc(sizeof(TreeNode));
    (*T)->val = ch;
    CreateTreeByScanf(&(*T)->left);
    CreateTreeByScanf(&(*T)->right);
}

/**
 * 递归建树
 * @param node 当前节点
 * @param arr 数据源
 * @param curr  当前索引
 * @param length 总数据长度
 */
void create(Tree *node, char *arr, int *curr, int length) {
    char ch = arr[(*curr)++];
    if (*curr == length || !('0' <= ch && ch <= '9')) {
        node = NULL;
        return;
    }
    *node = (TreeNode *) malloc(sizeof(TreeNode));
    (*node)->val = ch;
    (*node)->left = NULL;
    (*node)->right = NULL;
    create(&(*node)->left, arr, curr, length);
    create(&(*node)->right, arr, curr, length);
}

/**
 * 建树
 * @param T 树
 * @param arr 数据源
 * @param length 总数据长度
 */
void CreateTree(Tree *T, char *arr, int length) {
    int curr = 0;
    create(T, arr, &curr, length);//递归函数
}

int main() {
    /*
     *    1
     * 2    3
     */
    Tree T;
    CreateTree(&T, "12  3  ", 7);
    PreOrderTraverse(T);
    printf("\n");
    /*
     *      1
     *   2    4
     *  3    5 6
     */
    CreateTree(&T, "123   45  6  ", 13);
    PreOrderTraverse(T);
}