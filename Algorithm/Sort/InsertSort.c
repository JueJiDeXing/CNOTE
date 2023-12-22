// Author: 绝迹的星 
// Created on 2023/12/15


#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

#include "ArrayUtil.h"
/**
 * 插入排序
 * 将数组分为两部分,已排序[0,low-1]和未排序[low,length-1]
 * 每次从未排区取出low位置的元素,寻找插入位置
 * @param a 待排序数组
 * @param len 数组长度
 */
void insertSort(int *a, int len) {
    printf("开始排序:\n");
    for (int low = 1; low < len; low++) {
        int t = a[low];
        int i = low - 1;
        //寻找插入位置
        while (0 <= i && t < a[i]) {
            a[i + 1] = a[i];//比待插入值大的右移,空出一个位置
            i--;
        }
        if (i != low - 1) {//找到插入位置
            a[i + 1] = t;
        }
        printArr(a, len);
    }
}
