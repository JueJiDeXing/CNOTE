// Author: 绝迹的星 
// Created on 2023/12/22


#include "ArrayUtil.h"

//大顶堆

//下潜
void down(int *array, int parent, int size) {//小的元素下潜
    int left = 2 * parent + 1;
    int right = left + 1;
    int max = parent;//寻找 父,左,右 三者较大的
    if (left < size && array[left] > array[max]) {
        max = left;
    }
    if (right < size && array[right] > array[max]) {
        max = right;
    }
    if (max != parent) {//如果子节点比父节点优先级大
        swap(array, parent, max);// 交换
        down(array, max, size);//递归,直到max==parent,父节点大于左右子节点时停止
    }
}

//建堆
void heapify(int *array, int size) {
    for (int i = size / 2 - 1; i >= 0; i--) {
        down(array, i, size);//数组前一半的元素进行下潜
    }
}

void heapSort(int *arr, int len) {
    heapify(arr, len);//建堆
    for (int right = len - 1; right > 0; right--) {
        //交换第一个元素(大顶堆第一个元素为最大元素)与未排序区域最右侧元素
        // 并重新下潜排序(范围到未排序区域的最右侧)
        swap(arr, 0, right);
        down(arr, 0, right);
    }
}

int main435(){
    printf("测试1:\n");
    int arr1[] = {3, 5, 4, 1, 6, 8, 2};
    int len1 = sizeof(arr1) / sizeof(int);
    printf("开始排序:\n");
    heapSort(arr1, len1);
    printArr(arr1,len1);
    return 0;
}



