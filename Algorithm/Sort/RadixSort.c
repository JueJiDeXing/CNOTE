// Author: 绝迹的星 
// Created on 2023/12/23


#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include "ArrayUtil.h"
//基数排序
void RadixSort(int *arr, int n) {
    //max为数组中最大值,循环次数为最大数的位数
    int max = arr[0];
    for (int i = 0; i < n; i++) {
        if (arr[i] > max) {
            max = arr[i];
        }
    }
    int *tmp = (int *) malloc(sizeof(int) * n);//临时数组
    int base = 1;
    while (max / base > 0) {
        int bucket[10] = {0}; // 0~9
        for (int i = 0; i < n; i++) {
            int k = arr[i] / base % 10;
            bucket[k]++;//统计数位为k的有多少个
        }
        for (int i = 1; i < 10; i++) {
            bucket[i] += bucket[i - 1];//累加和,统计数位为k的前面有多少数字
        }
        //开始放数到临时数组tmp
        for (int i = n - 1; i >= 0; i--) {
            int k = arr[i] / base % 10;
            int index = bucket[k] - 1;//要放到temp数组的位置
            tmp[index] = arr[i];
            bucket[k]--;
        }
        //拷贝回原数组
        for (int i = 0; i < n; i++) {
            arr[i] = tmp[i];
        }
        base *= 10;//排下一位
    }
    free(tmp);
}

int main() {
    printf("测试1:\n");
    int arr1[] = {43, 18, 69, 27, 15, 36, 4, 12, 76, 28, 2};
    int len1 = sizeof(arr1) / sizeof(int);
    printf("开始排序:\n");
    RadixSort(arr1, len1);
    printArr(arr1, len1);
    return 0;
}