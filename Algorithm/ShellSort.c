// Author: 绝迹的星 
// Created on 2023/12/15


#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include "ArrayUtil.c"

/**
 * 希尔排序
 * 数据分组,每组间隙为gap(例如8个元素分4组,间隙为4,索引0与4 1与5 2与6 3与7)
 * 每组内插入排序,排序后gap变小,直到gap为1完成排序(每次除2)
 */
void shellSort(int *a, int len) {
    printf("开始排序:\n");
    for (int gap = len >> 1; gap >= 1; gap = gap >> 1) {//使用位运算代替除法
        //插入排序,但是不比较相邻元素,而是相隔gap的元素
        for (int low = gap; low < len; low++) {//low=gap,第一个元素视为已排;low++,排下一组
            int t = a[low];//当前未排序元素
            int i = low - gap;//同组的最右侧已排序元素索引
            while (0 <= i && t < a[i]) {//寻找插入位置
                a[i + gap] = a[i];//比待插入值大的右移,空出一个位置
                i -= gap;//同组的元素
            }
            if (i != low - gap) {//找到插入位置
                a[i + gap] = t;
            }
        }
        printArr(a, len);
    }
}

