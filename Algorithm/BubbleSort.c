// Author: 绝迹的星 
// Created on 2023/12/15


#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include "ArrayUtil.c"

/**
 * 冒泡排序,每轮比较相邻元素
 * 如果前一个元素大于后一个元素,则交换
 */
void bubbleSort1(int *a, int len) {
    printf("开始排序:\n");
    for (int i = 0; i < len - 1; i++) {
        for (int j = 0; j < len - i - 1; j++) {
            if (a[j] > a[j + 1]) {
                //交换元素值
                swap(a, j, j + 1);
            }
        }
        printArr(a, len);
    }
}

/**
 * 冒泡排序优化
 * 加入一个指针x,记录本轮的最后一次交换位置
 * 减少了比较次数
 */
void bubbleSort2(int *a, int len) {
    printf("开始排序:\n");
    int j = len - 1;
    do {
        int x = 0;
        for (int i = 0; i < j; i++) {//遍历0~j的元素
            if (a[i] > a[i + 1]) {
                swap(a, i, i + 1);
                x = i;//x记录一次遍历中最后一次交换的位置(无序的右边界)
            }
        }
        j = x;
        printArr(a, len);
    } while (j != 0);
}

