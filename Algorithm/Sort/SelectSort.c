// Author: 绝迹的星 
// Created on 2023/12/23


#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include "ArrayUtil.h"

/**
 <div color=rgb(155,200,80)>
 <h1>选择排序</h1>
 </div>
 */
void selectSort(int *arr, int len) {
    // 选择轮数:length-1
    // 交换位置(right) 初始length-1,每次递减
    for (int right = len - 1; right > 0; right--) {
        int max = right;//循环前面未排序区域,找到最大值的索引
        for (int i = 0; i < right; i++) {
            if (arr[i] > arr[max]) {
                max = i;
            }
        }
        if (max != right) {
            swap(arr, max, right);//交换
        }
    }
}

int main1asc() {
    printf("测试1:\n");
    int arr1[] = {3, 15, 5, 1, 6, 8, 19, 2};
    int len1 = sizeof(arr1) / sizeof(int);
    printf("开始排序:\n");
    selectSort(arr1, len1);
    printArr(arr1, len1);
    return 0;
}