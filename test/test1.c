// Author: 绝迹的星 
// Created on 2023/12/8


#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include "../Structures/树/Tree.c"
/**
 * 从根节点开始,判断subTree是否与tree相同
 */
bool isSame(Tree tree, Tree subTree) {
    if (subTree == NULL) {//比较完了,返回true
        return true;
    }
    if (tree == NULL || tree->val != subTree->val) {//不同
        return false;
    }
    //左右都需要相同
    return isSame(tree->left, subTree->left) && isSame(tree->right, subTree->right);
}
/**
 * 判断树中是否存在一颗子树
 * @param tree  树
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
    if(isSame(tree, subTree)){
        return true;
    }
    //不同在左右子树中搜索
    return hasSub(tree->left, subTree) || hasSub(tree->right, subTree);

}

int main() {
    /*测试1
     *    3
     *  4    5     4
     * 1 2        1 2
     */
    Tree tree1, subTree1;
    char *arr1 = "341  2  5  ", *subArr1 = "41  2  ";
    CreateTree(&tree1, arr1, strlen(arr1));
    CreateTree(&subTree1, subArr1, strlen(subArr1));
    printf("测试1(应为true):%d", hasSub(tree1, subTree1));
    printf("\n");

    /*测试2
     *    3
     *  4    5     4
     * 1 2        1 3
     */
    Tree tree2, subTree2;
    char *arr2 = "341  2  5  ", *subArr2 = "41  3  ";
    CreateTree(&tree2, arr2, strlen(arr2));
    CreateTree(&subTree2, subArr2, strlen(subArr2));
    printf("测试2(应为false):%d", hasSub(tree2, subTree2));
    printf("\n");
    /*测试3
     *    3
     *  4    5     4
     * 1 2        1
     */
    Tree tree3, subTree3;
    char *arr3 = "341  2  5  ", *subArr3 = "41    ";
    CreateTree(&tree3, arr3, strlen(arr3));
    CreateTree(&subTree3, subArr3, strlen(subArr3));
    printf("测试3(应为true):%d", hasSub(tree3, subTree3));
    printf("\n");
}