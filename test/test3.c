// Author: 绝迹的星 
// Created on 2023/12/8


#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include "../Structures/树/Tree.c"

int getTreeHeight(Tree node) {
    if (node == NULL) {
        return 0;
    }
    //判断左子树是否平衡
    int leftH = getTreeHeight(node->left);
    if (leftH == -1) {
        return -1; // 不平衡提前退出，不再递归
    }
    //查看右子树是否平衡
    int rightH = getTreeHeight(node->right);
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
bool isBalanceTree(Tree tree) {
    return getTreeHeight(tree) != -1;
}

int main() {
    /*测试1
     *    3
     *  4    5
     * 1 2
     */
    Tree tree1;
    char *arr1 = "341  2  5  ";
    CreateTree(&tree1, arr1, strlen(arr1));
    printf("测试1(应为true):%d", isBalance(tree1));
    printf("\n");
    /*测试2
       *    3
       *  4
       * 1
       */
    Tree tree2;
    char *arr2 = "341    ";
    CreateTree(&tree2, arr2, strlen(arr2));
    printf("测试2(应为false):%d", isBalance(tree2));
    printf("\n");

    /*测试3
      *    3
      *  4    5
      */
    Tree tree3;
    char *arr3 = "34  5  ";
    CreateTree(&tree3, arr3, strlen(arr3));
    printf("测试3(应为true):%d", isBalance(tree3));
    printf("\n");
}