// Author: 绝迹的星 
// Created on 2023/12/23


#include <stdio.h>
#include <stdlib.h>
#include "ArrayUtil.h"

void countSort(int *a, int len) {
    //求最大最小值
    int max = a[0], min = a[0];
    for (int i = 1; i < len; i++) {
        if (a[i] > max) max = a[i];
        if (a[i] < min) min = a[i];
    }
    //计数
    int L = max - min + 1;
    int *count = malloc(sizeof(int) * L);
    for (int i = 0; i < L; i++) {
        count[i] = 0;
    }
    for (int i = 0; i < len; i++) {
        count[a[i] - min]++;//原元素值-最小值=索引
    }
    //根据计数排序
    int k = 0;
    for (int i = 0; i < L; i++) {
        while (count[i] > 0) {
            a[k++] = i + min;//索引+最小值=原元素值
            count[i]--;
        }
    }
    free(count);
}

int main2acw() {
    printf("测试1:\n");
    int arr1[] = {3, 5, 4, 17, 4, 6, 8, 2};
    int len1 = sizeof(arr1) / sizeof(int);
    printf("开始排序:\n");
    countSort(arr1, len1);
    printArr(arr1, len1);
    return 0;
}