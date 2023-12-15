// Author: 绝迹的星 
// Created on 2023/12/15


#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

#define EmptyValue (-1)
#define null NULL
typedef int E;
typedef struct BSTNode {
    int key;
    E *value;
    struct BSTNode *left, *right;
} BSTNode;

BSTNode *InitBSTNode(int key, E *value) {
    BSTNode *node = malloc(sizeof(BSTNode));
    node->key = key;
    node->value = value;
    node->left = NULL;
    node->right = NULL;
    return node;
}

BSTNode *InitBSTNodeAll(int key, E *value, BSTNode *left, BSTNode *right) {
    BSTNode *node = malloc(sizeof(BSTNode));
    node->key = key;
    node->value = value;
    node->left = left;
    node->right = right;
    return node;
}

/**
 Binary Search Tree 二叉搜索树
 */
typedef struct BSTree {
    BSTNode *root;//根节点
    int count;//节点个数
} BSTree;


void InitBSTree(BSTree *tree) {
    tree->root = NULL;
    tree->count = 0;
}

/**
 存储关键字对应的值

 @param key   关键字
 @param value 值
 */
void put(BSTree *tree, int key, E *value) {
    BSTNode *node = tree->root;
    BSTNode *parent = null;//新增节点的父节点
    while (node != null) {
        parent = node;
        if (key < node->key) {
            node = node->left;
        } else if (key > node->key) {
            node = node->right;
        } else {
            //有key则更新
            node->value = value;
            return;
        }
    }
    //没有key则新增节点
    BSTNode *added = InitBSTNode(key, value);
    if (parent == null) {
        tree->root = added;
        return;
    }
    if (key < parent->key) {
        parent->left = added;
    } else {
        parent->right = added;
    }
    tree->count++;
}

/**
 递归查找
 */
E doGet(BSTNode *node, int key) {
    if (node == null) {
        return EmptyValue;//没找到
    }
    if (key < node->key) {
        return doGet(node->left, key);//向左找,尾递归在java不支持自动优化,可以自己转写为非递归方法
    } else if (key > node->key) {
        return doGet(node->right, key);//向右找
    } else {
        return *node->value;//找到了
    }
}

/**
 查找key对应的值
 递归实现

 @param key 关键字
 @return 关键字对应的值
 */
E get2(BSTree tree, int key) {
    return doGet(tree.root, key);
}


/**
 查找key对应的值
 <b>非递归实现</b>

 @param key 关键字
 @return 关键字对应的值
 */
E get(BSTree tree, int key) {
    BSTNode *node = tree.root;
    while (node != null) {
        if (key < node->key) {
            node = node->left;
        } else if (key > node->key) {
            node = node->right;
        } else {
            return *node->value;
        }
    }
    return -1;
}

/**
 从某节点查找树最大关键字对应值

 @return 关键字对应的值
 */
E doMax(BSTNode *node) {
    if (node == null) {
        return -1;
    }
    BSTNode *p = node;
    while (p->right != null) {
        p = p->right;
    }
    return *p->value;
}

/**
 查找最大关键字对应值

 @return 关键字对应的值
 */
E max(BSTree tree) {
    return doMax(tree.root);
}


/**
 从某节点开始查找数最小关键字对应值

 @return 关键字对应的值
 */
E doMin(BSTNode *node) {
    if (node == null) {
        return EmptyValue;
    }
    BSTNode *p = node;
    while (p->left != null) {
        p = p->left;
    }
    return *p->value;
}

/**
 查找最小关键字对应值

 @return 关键字对应的值
 */
E min(BSTree tree) {
    return doMin(tree.root);
}


/**
 查找前驱

 @param key 关键字
 @return 前驱值
 */
E predecessor(BSTree tree, int key) {
    BSTNode *p = tree.root;
    BSTNode *ancestorFromLeft = null;
    while (p != null) {
        if (key < p->key) {
            p = p->left;
        } else if (key > p->key) {
            ancestorFromLeft = p;//记录最近一次自左而来的祖先
            p = p->right;
        } else {
            break;
        }
    }//查找key对应节点
    if (p == null) {//没找到
        return EmptyValue;
    }
    //找到节点
    if (p->left != null) {
        //如果节点有左子树,那么它的前驱为左子树里的最大值
        return doMax(p->left);
    }
    //如果没有左子树,那么它的前驱为离它最近的自左而来的祖先
    // (自左而来:节点处于某祖先节点的右子树,则将祖先称为自左而来)
    return ancestorFromLeft == null ? EmptyValue : *ancestorFromLeft->value;
}

/**
 查找后继

 @param key 关键字
 @return 后继值
 */
E successor(BSTree tree, int key) {
    BSTNode *p = tree.root;
    BSTNode *ancestorFromRight = null;
    while (p != null) {
        if (key < p->key) {
            ancestorFromRight = p;//记录最近一次自右而来的祖先
            p = p->left;
        } else if (key > p->key) {
            p = p->right;
        } else {
            break;
        }
    }//查找key对应节点
    if (p == null) {//没找到
        return EmptyValue;
    }
    //找到节点
    if (p->right != null) {
        //如果节点有右子树,那么它的后继为右子树里的最小值
        return doMin(p->right);
    }
    //如果没有右子树,那么它的后继为离它最近的自右而来的祖先
    // (自右而来:节点处于某祖先节点的左子树,则将祖先称为自右而来)
    return ancestorFromRight == null ? EmptyValue : *ancestorFromRight->value;
}

/**
 托孤方法

 @param parent  父节点
 @param deleted 被删除的节点
 @param child   要托孤的孩子节点
 */
void shift(BSTree *tree, BSTNode *parent, BSTNode *deleted, BSTNode *child) {
    if (parent == null) {//被删除的节点为根节点
        tree->root = child;
    } else if (parent->left == deleted) {
        parent->left = child;
    } else {
        parent->right = child;
    }
}


/**
 根据key删除

 @param key 关键字
 @return 被删除的值
 */
E delete(BSTree *tree, int key) {
    /*
    情况分析:
    1. 被删除的节点只有左孩子或右孩子,将左孩子或右孩子托孤给parent(如果没有孩子将null托孤)
    2. 被删除的节点有左右孩子,设它的后继节点为next,next的父亲为nextP (这里也可以去寻找前驱节点)
        2.1 如果nextP就是被删除的节点,则将next托孤给parent
        2.2 如果nextP不是被删除的节点,则将next的后任托孤给nextP,再将next托孤给parent
     */
    BSTNode *deleted = tree->root;//被删除的节点
    BSTNode *parent = null;//记录父节点
    while (deleted != null) {
        if (key < deleted->key) {
            parent = deleted;
            deleted = deleted->left;
        } else if (key > deleted->key) {
            parent = deleted;
            deleted = deleted->right;
        } else {
            break;
        }
    }
    if (deleted == null) {
        return EmptyValue;//没找到
    }
    //找到,执行删除操作
    if (deleted->left == null) {//孩子数<=1
        shift(tree, parent, deleted, deleted->right);
    } else if (deleted->right == null) {
        shift(tree, parent, deleted, deleted->left);
    } else {//有左右孩子
        //查找后继
        BSTNode *next = deleted->right;
        BSTNode *nextP = null;//后继节点的父节点
        while (next->left != null) {
            nextP = next;
            next = next->left;
        }
        //如果删除节点与后继节点不相邻,处理后继的后任
        if (deleted != nextP) {
            //这里不需要考虑左后任,因为后继是子树里的最小值,它不可能有左孩子,只可能有右孩子
            shift(tree, nextP, next, next->right);
            next->right = deleted->right;
        }
        //后继取代被删除节点
        shift(tree, parent, deleted, next);
        next->left = deleted->left;
    }
    tree->count--;
    return *deleted->value;
}

/**
 @param node   起点
 @param key    被删除的节点的key
 @param result 保存需要返回的value值
 @return 被删除的节点的孩子
 */
BSTNode *doDelete(BSTree *tree, BSTNode *node, int key, E *result, int *count) {
    if (node == null) {
        return null;
    }
    if (key < node->key) {//删除的节点在左子树
        node->left = doDelete(tree, node->left, key, result, count);//在左子树里去删
        return node;
    }
    if (key > node->key) {
        node->right = doDelete(tree, node->right, key, result, count);
        return node;
    }
    // 已经找到要删除的节点node
    result[*count++] = *node->value;
    // 1.孩子数<=1,返回删除节点的孩子
    if (node->left == null) {
        return node->right;
    }
    if (node->right == null) {
        return node->left;
    }
    // 2.有左右孩子
    //查找后继
    BSTNode *next = node->right;
    while (next->left != null) {
        next = next->left;
    }
    //调整后继的孩子关系,然后返回后继节点
    E *newResult = malloc(sizeof(E) * tree->count);
    int newCount = 0;
    next->right = doDelete(tree, node->right, next->key, newResult, &newCount);//处理后继的后任,相当于在右子树里删除后继,再将这个子树作为后继的右孩子
    next->left = node->left;//接替node的左孩子
    return next;
}

/**
 根据key删除  递归实现

 @param key 关键字
 @return 被删除的值
 */
E delete2(BSTree *tree, int key) {
    E *result = malloc(sizeof(E) * tree->count);//保存值
    int count = 0;
    tree->root = doDelete(tree, tree->root, key, result, &count);
    tree->count--;
    return count == 0 ? EmptyValue : result[0];
}

// 根据key的范围查找---核心思想:中序遍历

/**
 查找小于key的节点值
 (-∞,key) -> list:values
 */
E *less(BSTree tree, int key, int *resultLength) {
    E *result = malloc(sizeof(E) * tree.count);
    *resultLength = 0;
    BSTNode *p = tree.root;
    BSTNode *stack[tree.count];
    int stackLength = 0;
    while (p != null || stackLength != 0) {
        if (p != null) {//向左子树走到头
            stack[stackLength++] = p;
            p = p->left;
        } else {//走到头往回走处理右子树
            BSTNode *pop = stack[--stackLength];
            if (pop->key < key) {
                result[*resultLength++] = *pop->value;
            } else {//已经大于key了就不用再查找了(节点的右子树都是大于这个节点的)
                break;
            }
            p = pop->right;
        }
    }
    return result;
}

/**
 查找大于key的节点的key
 (key,+∞) -> list:values
 */
E *greater(BSTree tree, int key, int *resultLength) {
    E *result = malloc(sizeof(E) * tree.count);
    *resultLength = 0;
    BSTNode *p = tree.root;
    BSTNode *stack[tree.count];
    int stackLength = 0;
    while (p != null || stackLength != 0) {
        if (p != null) {
            stack[stackLength++] = p;
            p = p->right;//倒序中序遍历,在查找大值时可以提前退出
        } else {
            BSTNode *pop = stack[--stackLength];
            if (pop->key > key) {
                result[*resultLength++] = *pop->value;
            } else {
                break;
            }
            p = pop->left;
        }
    }
    return result;
}

/**
 查找所有处于key1与key2之间的节点的value<br>
 [key1,key2] -> list:values
 */
E *between(BSTree tree, int key1, int key2, int *resultLength) {
    E *result = malloc(sizeof(E) * tree.count);
    *resultLength = 0;
    BSTNode *p = tree.root;
    int stackLength = 0;
    BSTNode *stack[tree.count];
    while (p != null || stackLength != 0) {
        if (p != null) {
            stack[stackLength++] = p;
            p = p->left;
        } else {
            BSTNode *pop = stack[--stackLength];
            if (key1 <= pop->key && pop->key <= key2) {
                result[*resultLength++] = *pop->value;
            } else if (pop->key > key2) {
                break;
            }
            p = pop->right;
        }
    }
    return result;
}

enum {
    prev, in, post
};

/*
 * 遍历*/
void doOrder(BSTNode *node, int method) {
    if (node == NULL) {
        return;
    }
    if (method == prev) {
        printf("%d,", *node->value);
    }

    doOrder(node->left, method);
    if (method == in) {
        printf("%d,", *node->value);
    }
    doOrder(node->right, method);
    if (method == post) {
        printf("%d,", *node->value);
    }
}

void preOrder(BSTree tree) {
    doOrder(tree.root, prev);
    printf("\b\n");
}

void inOrder(BSTree tree) {
    doOrder(tree.root, in);
    printf("\b\n");
}

void postOrder(BSTree tree) {
    doOrder(tree.root, post);
    printf("\b\n");
}
/**
 * 层序遍历
 */
void levelOrder(BSTree tree) {
    BSTNode *queue[tree.count + 1];
    int head = 0, tail = 0;
    queue[tail] = tree.root;
    tail++;
    while (head != tail) {
        BSTNode *node = queue[head];
        printf("%d,", *node->value);
        head++;
        if (node->left != NULL) {
            queue[tail] = node->left;
            tail++;
        }
        if (node->right != NULL) {
            queue[tail] = node->right;
            tail++;
        }
    }
    printf("\b\n");
}

int main() {
    BSTree tree;
    InitBSTree(&tree);
    /*
     *      2
     *    1   4
     *       3  5
     */
    E value2 = 2;
    put(&tree, value2, &value2);
    E value1 = 1;
    put(&tree, value1, &value1);
    E value4 = 4;
    put(&tree, value4, &value4);
    E value3 = 3;
    put(&tree, value3, &value3);
    E value5 = 5;
    put(&tree, value5, &value5);
    preOrder(tree);//2,1,4,3,5
    inOrder(tree);//1,2,3,4,5
    postOrder(tree);//1,3,5,4,2
    levelOrder(tree);//2,1,4,3,5
    printf("%d", predecessor(tree, 3));
}