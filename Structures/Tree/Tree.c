// Author: 绝迹的星
// Created on 2023/11/26


#include <stdio.h>
#include <stdbool.h>
#include <math.h>
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
 * @param T Tree
 * @param arr 数据源
 * @param length 总数据长度
 */
void CreateTree(Tree *T, char *arr, int length) {
    int curr = 0;
    create(T, arr, &curr, length);//递归函数
}

int getHeight(Tree node) {
    if (node == NULL) {
        return 0;
    }
    int leftH = getHeight(node->left);
    int rightH = getHeight(node->right);
    return (int) fmax(leftH, rightH) + 1;//返回子树高度
}

int getBalanceHeight(Tree node) {
    if (node == NULL) {
        return 0;
    }
    //判断左子树是否平衡
    int leftH = getBalanceHeight(node->left);
    if (leftH == -1) {
        return -1; // 不平衡提前退出，不再递归
    }
    //查看右子树是否平衡
    int rightH = getBalanceHeight(node->right);
    if (rightH == -1) {
        return -1;
    }
    //根据左右子树高度判断当前子树是否平衡
    if (abs(leftH - rightH) > 1) {
        return -1;
    }
    return (int) fmax(leftH, rightH) + 1;//平衡,返回子树高度
}

/**
 * 判断树是否平衡
 */
bool isBalance(Tree tree) {
    return getBalanceHeight(tree) != -1;
}
/**
 * 从根节点开始,判断subTree是否与tree相同
 */
bool isSubSame(Tree tree, Tree subTree) {
    if (subTree == NULL) {//比较完了,返回true
        return true;
    }
    if (tree == NULL || tree->val != subTree->val) {//不同
        return false;
    }
    //左右都需要相同
    return isSubSame(tree->left, subTree->left) && isSubSame(tree->right, subTree->right);
}
/**
 * 判断树中是否存在一颗子树
 * @param tree  Tree
 * @param subTree  子树
 * @return 如果存在返回true,否则返回false
 */
bool hasSub(Tree tree, Tree subTree) {
    if (subTree == NULL) {//判断完了,返回true
        return true;
    }
    if (tree == NULL) {//不同
        return false;
    }
    //判断当前节点开始是否相同
    if (isSubSame(tree, subTree)) {
        return true;
    }
    //不同在左右子树中搜索
    return hasSub(tree->left, subTree) || hasSub(tree->right, subTree);
}