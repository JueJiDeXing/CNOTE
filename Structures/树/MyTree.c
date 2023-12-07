// Author: 绝迹的星 
// Created on 2023/11/26


#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "../Status.h"

#define STACK_INIT_SIZE 100
#define STACKINCREMENT 10

typedef char TElemType;
typedef struct BiTNode {
    TElemType data;
    struct BiTNode *left, *right; // 左右孩子指针
} BiTNode, *BiTree;

typedef struct {
    BiTree *top;
    BiTree *base;
    int stacksize;
} SqStack;


Status InitStack(SqStack *s) {
    s->base = malloc(sizeof(BiTree) * STACK_INIT_SIZE);
    if (!s->base) exit(ERROR);
    s->top = s->base;
    s->stacksize = STACK_INIT_SIZE;
    return OK;
}


bool StackIsEmpty(SqStack s) {
    return s.base == s.top;
}

int StackLength(SqStack s) {
    return s.top - s.base;
}

Status Push(SqStack *s, BiTree e) {
    if (s->stacksize == s->top - s->base) { //栈满,追加存储空间
        s->base = realloc(s->base, sizeof(int) * (s->stacksize + STACKINCREMENT));
        if (!s->base) exit(ERROR); // 存储分配失败
        s->top = s->base + STACKINCREMENT;
        s->stacksize = s->stacksize + STACKINCREMENT;
    }
    *s->top++ = e;
    return OK;
}

Status Pop(SqStack *s, BiTree *e) {
    if (StackLength(*s) == 0) exit(ERROR);
    *e = *--s->top;
    return OK;
}

BiTree GetTop(SqStack s) {
    if (s.base == s.top) exit(ERROR);
    return *(s.top - 1);
}

//前序遍历,递归实现
Status PreOderTraverse(BiTree T, Status (*visit)(TElemType e)) {
    if (T) {
        if (visit(T->data))
            if (PreOderTraverse(T->left, visit))
                if (PreOderTraverse(T->right, visit)) return OK;
        return ERROR;
    }
    return OK;
}

// 非递归
Status PreOderTraverse2(BiTree T, Status (*visit)(TElemType e)) {
    SqStack S;
    InitStack(&S);
    BiTree p = T;
    while (p || !StackIsEmpty(S)) {
        if (p) {
            if (!visit(p->data)) exit(ERROR);
            Push(&S, p);
            p = p->left;
        } else {
            Pop(&S, &p);
            p = p->right;
        }
    }
    return OK;
}

//中序
Status InOderTraverse(BiTree T, Status (*visit)(TElemType e)) {
    if (T) {
        if (InOderTraverse(T->left, visit))
            if (visit(T->data))
                if (InOderTraverse(T->right, visit))
                    return OK;
        return ERROR;
    }
    return OK;
}

// 非递归
Status InOderTraverse2(BiTree T, Status (*visit)(TElemType e)) {
    SqStack S;
    InitStack(&S);
    BiTree p = T;
    while (p || !StackIsEmpty(S)) {
        if (p) {
            Push(&S, p);
            p = p->left;
        } else {
            Pop(&S, &p);
            if (!visit(p->data)) exit(ERROR);
            p = p->right;
        }
    }
    return OK;
}

Status PostOderTraverse(BiTree T, Status (*visit)(TElemType e)) {
    if (!T) {
        return OK;
    }
    if (!PostOderTraverse(T->left, visit))return ERROR;
    if (!PostOderTraverse(T->right, visit))return ERROR;
    return visit(T->data);

}

// 非递归
Status PostOderTraverse2(BiTree T, Status (*visit)(TElemType e)) {
    SqStack S;
    InitStack(&S);
    BiTree p = T, record = 0;
    while (p || !StackIsEmpty(S)) {
        if (p) {
            Push(&S, p);
            p = p->left;
        } else {
            Pop(&S, &p);
            if (p->right && p->right != record) {
                Push(&S, p);
                p = p->right;
            } else {
                if (!visit(p->data)) exit(ERROR);
                record = p;
                p = NULL;
            }
        }
    }
    return OK;
}

//创建二叉树
Status CreateBiTree(BiTree *T) {
    // 按先序次序输入二叉树中结点的值,(一个字符),空格字符表示空树
    // 构造二叉树表表示的二叉树T
    char ch;
    scanf("%c", &ch);
    if (ch == ' ') {
        *T = NULL;
        return OK;
    }
    if (!(*T = malloc(sizeof(BiTNode)))) {
        exit(ERROR);
    }
    (*T)->data = ch;  //生成根节点
    CreateBiTree(&(*T)->left);  // 构造左子树
    CreateBiTree(&(*T)->right);  // 构造右子树
    return OK;
}


/**
 * 统计节点数量
 */
int CountBiTNodes(BiTree T) {
    return T ? CountBiTNodes(T->left) + CountBiTNodes(T->right) + 1 : 0;
}

int CountLeafNodes(BiTree T) {
    if (!T) {
        return 0;
    }
    if (!T->right && !T->left) {
        return 1;
    }
    return CountLeafNodes(T->right) + CountLeafNodes(T->left);
}

int BiTreeDepth(BiTree T) {
    if (T) {
        int leftDepth = BiTreeDepth(T->left);
        int rightDepth = BiTreeDepth(T->right);
        return leftDepth > rightDepth ? leftDepth + 1 : rightDepth + 1;
    }
    return 0;
}
