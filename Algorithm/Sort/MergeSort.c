// Author: 绝迹的星 
// Created on 2023/12/22


#include <stdlib.h>
#include "ArrayUtil.h"

/**
 合并两个有序数组

 @param a1   数据源
 @param i    第一个数组的起始索引
 @param iEnd 第一个数组的结束索引
 @param j    第二个数组的起始索引
 @param jEnd 第二个数组的结束索引
 @param a2   临时数组
 */
void merge(int *a1, int i, int iEnd, int j, int jEnd, int *a2) {
    int k = 0;
    while (i <= iEnd && j <= jEnd) {
        if (a1[i] < a1[j]) {
            a2[k] = a1[i];
            i++;
        } else {
            a2[k] = a1[j];
            j++;
        }
        k++;
    }
    //处理剩余没放入a2的部分
    if (i > iEnd) {
        for (int l = j; l <= jEnd; l++) {
            a2[k++] = a1[l];
        }

    }
    if (j > jEnd) {
        for (int l = i; l <= iEnd; l++) {
            a2[k++] = a1[l];
        }
    }

}

/**
 * 分治
 */
void split(int *a1, int left, int right, int *a2, int len) {

    // 2.治
    if (left == right) {
        return;
    }
    // 1.分
    int m = (left + right) >> 1;//从中间分隔
    split(a1, left, m, a2, len);
    split(a1, m + 1, right, a2, len);

    // 3.合
    merge(a1, left, m, m + 1, right, a2);//合并两个有序区域到a2
    for (int i = 0; i < right - left + 1; i++) {
        a1[i + left] = a2[i];//将合并后的再存入a1
    }
    printArr(a1, len);
}

void mergeSort(int *a1, int len) {
    int *a2 = malloc(sizeof(int) * len);//临时数组,在合并时将数据放入
    split(a1, 0, len - 1, a2, len);
    free(a2);
}
int main1_1() {
    printf("测试1:\n");
    int arr1[] = {3, 5, 4, 1, 6, 8, 2};
    int len1 = sizeof(arr1) / sizeof(int);
    printf("开始排序:\n");
    mergeSort(arr1, len1);

    printf("测试2:\n");
    int arr2[] = {51, 3, 5, 10, 16, 20, 4, 1, 72, 6, 8, 2};
    int len2 = sizeof(arr2) / sizeof(int);
    printf("开始排序:\n");
    mergeSort(arr2, len2);
    return 0;
}