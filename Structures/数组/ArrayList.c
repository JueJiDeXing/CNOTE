// Created by 绝迹的星 on 2023/10/17.

#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
#include "../Status.h"

typedef struct {
    int *elem; //存储空间基址
    int length; //当前存储长度
    int capacity;//当前分配的存储容量
} ArrayList;
#define LIST_INIT_SIZE 50  // 线性表存储空间的初始分配量

/**
 * 初始化顺序表
 * @param L 顺序表数组
 * @return 状态码
 */
Status init_ArrayList(ArrayList *L) {
    L->elem = malloc(sizeof(int) * LIST_INIT_SIZE);
    if (!L->elem) exit(OVERFLOW);
    L->length = 0;
    L->capacity = DEFAULT_CAPACITY;
    return OK;
}

/**
 * 销毁线性表
 * @param L 顺序表数组
 * @return 返回函数状态码
 */
Status destroy_ArrayList(ArrayList *L) {
    free(L->elem);
    return OK;
}

/**
 * 将L置为空表
 * @param L
 * @return 函数状态码
 */
Status clear_ArrayList(ArrayList *L) {
    L->length = 0;
    return OK;
}
/**
 * 若L为空表，则返回TRUE，否则返回FALSE
 * @param L 顺序表
 * @return bool
 */
bool isEmpty_Array(ArrayList *L) {
    if (!L->elem) true;
    return false;
}

bool isFull_Array(ArrayList *L) {
    if (!L->elem) exit(ERROR);
    return L->length == L->capacity;

}

/**
 * 返回L中元素个数
 * @param L 顺序表
 * @return 元素个数
 */
int getLength_Array(ArrayList *L) {
    return L->length;
}

/**
 * 获取L中索引i元素的值
 * @param L
 * @param i 索引
 * @param elem 被赋值的变量
 * @return 函数状态
 */
Status getElem_Array(ArrayList *L, int i, int *elem) {
    if (i < 0 || i >= L->length)
        return ERROR;
    *elem = L->elem[i];
    return OK;
}
/**
 * 判断某元素值是否存在
 * @param L
 * @param e
 * @return
 */
bool contain_Array(ArrayList *L, int e) {
    for (int i = 0; i < L->length; i++) {
        if (L->elem[i] == e) {
            return true;
        }
    }
    return false;
}

/**
 * 按自定义方法获取元素索引
 * @param L
 * @param e 被比较的值
 * @param compare 比较方法
 * @return
 */
int locateElem_Array(ArrayList *L, int e, bool (*compare)(int, int)) {
    for (int i = 0; i < L->length; i++)
        if (compare(e, L->elem[i]))
            return i;
    return 0;
}

/**
 * @param L
 * @param cur_elem 查找的值
 * @param pre_elem 前驱值
 * @return
 */
Status priorElem_Array(ArrayList *L, int cur_elem, int *pre_elem) {
    if (cur_elem == L->elem[0])
        return ERROR;
    for (int k = 1; k < L->length; k++)
        if (cur_elem == L->elem[k]) {
            *pre_elem = L->elem[k - 1];
            return OK;
        }
    return ERROR;
}

/**
 *
 * @param L
 * @param cur_elem
 * @param nex_elem 后继值
 * @return
 */
Status nextElem_Array(ArrayList *L, int cur_elem, int *nex_elem) {
    if (cur_elem == L->elem[L->length - 1])
        return ERROR;
    for (int k = 0; k < L->length - 1; k++)
        if (cur_elem == L->elem[k]) {
            *nex_elem = L->elem[k + 1];
            return OK;
        }
    return ERROR;
}

/**
 * 插入
 * @param L
 * @param e 插入值
 * @param i 插入索引
 * @return
 */
Status insert_Array(ArrayList *L, int e, int i) {
    if (i < 0 || i > L->length)//索引越界
        return ERROR;
    if (isFull_Array(L)) {
        return ERROR;
    }
    for (int j = L->length - 1; j >= i; j--)//把插入位置及以后的元素向后移动一位
        L->elem[j + 1] = L->elem[j];
    L->elem[i] = e;//插入
    L->length++;
    return OK;
}

/**
 * 删除L的第i个元素,并利用e返回其值,L的长度减一
 * @param L
 * @param e
 * @param i 索引
 * @return
 */
Status delete_Array(ArrayList *L, int *e, int i) {
    if (i < 0 || i >= L->length)
        return ERROR;
    *e = L->elem[i];
    for (int j = i; j < L->length; j++)
        L->elem[j] = L->elem[j + 1];
    L->length--;
    return OK;
}

Status travers_Array(ArrayList *L, int (*visit)(int)) {
    for (int i = 0; i < L->length; i++)
        L->elem[i] = visit(L->elem[i]);
    return OK;
}

Status append_Array(ArrayList *L, int elem) {
    L->elem[L->length] = elem;
    L->length++;
    return OK;
}


// 将两个线性表取并集,L1并L2 = L1
//将所有在线性表L2但不在L1的数据元素插入到L1
void unite_Array(ArrayList *L1, ArrayList *L2) {
    int len2 = getLength_Array(L2);
    int e = 0;
    for (int i = 1; i <= len2; i++) {
        getElem_Array(L2, i, &e);
        if (!contain_Array(L1, e))
            append_Array(L1, e);
    }
}

// 将两个线性表合并成一个新线性表
void merge_Array(ArrayList L1, ArrayList L2, ArrayList *L3) {
    int len1 = getLength_Array(&L1);
    int len2 = getLength_Array(&L2);
    int i = 0, j = 0;
    int e1 = 0, e2 = 0;

    while (i < len1 && j < len2) {
        getElem_Array(&L1, i, &e1);
        getElem_Array(&L2, j, &e2);
        if (e1 <= e2) {
            append_Array(L3, e1);
            i++;
        } else {
            append_Array(L3, e1);
            j++;
        }
    }
    while (i < len1) {
        getElem_Array(&L1, i++, &e1);
        append_Array(L3, e1);
    }
    while (j < len2) {
        getElem_Array(&L2, j++, &e2);
        append_Array(L3, e2);
    }
}

void printArrayList(ArrayList L) {
    printf("[");
    for (int i = 0; i < L.length; i++) {
        printf("%d", L.elem[i]);
        if (i != L.length - 1)printf(", ");
    }
    printf("]\n");
}