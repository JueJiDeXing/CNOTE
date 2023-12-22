// Author: 绝迹的星 
// Created on 2023/12/15


#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include "ArrayUtil.h"


/**
 * 随机基准点分区
 */
int partition(int *a, int left, int right) {
    int index = rand() % (right - left + 1) + left;
    swap(a, index, left);
    int pv = a[left];//基准点元素值
    int i = left;
    int j = right;
    while (i < j) {
        while (i < j && a[j] > pv) {
            //寻找小的
            j--;
        }
        while (i < j && pv >= a[i]) {//内层循环也要判断i<j
            //寻找大的
            i++;
        }
        //找到则交换
        swap(a, i, j);
    }
    swap(a, left, i);
    return i;
}

void quick(int *a, int len, int left, int right) {
    //递归主函数
    if (left >= right) {
        return;
    }
    //快排核心方法:分区
    // 找基准点,小的放左边,大的放右边
    int p = partition(a, left, right);
    printf("分区元素的元素值:%d  分区后数组:",p);
    printArr(a, len);
    quick(a, len, left, p - 1);//对两个区域再次分区排序
    quick(a, len, p + 1, right);
}


void quickSort(int *a, int len) {
    printf("开始排序:\n");
    quick(a, len, 0, len - 1);

}

/**
 * 选择排序
 * 每次在未排序区域选择最小元素放在数组排序区域的末端
 */
void selectSort(int *a, int len) {
    printf("开始排序:\n");
    for (int i = 0; i < len - 1; i++) {
        //在未排序区寻找最小元素
        int min = i;
        for (int j = i + 1; j < len; j++) {
            if (a[j] < a[min]) {
                min = j;
            }
        }
        swap(a, i, min);
        printArr(a, len);
    }
}

int main() {

}