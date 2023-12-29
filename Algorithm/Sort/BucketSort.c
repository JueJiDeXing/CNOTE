// Author: 绝迹的星 
// Created on 2023/12/23


#include "InsertSort.c"
#include <math.h>
#include "../../Structures/Array/ArrayList.c"


void bucketSort(int *a, int len) {
    int range = (int) sqrt(len);//桶的最大容量,根据最大最小值和容量确定桶的个数
    //求最大最小值
    int max = a[0], min = a[0];
    for (int i = 1; i < len; i++) {
        if (a[i] > max) max = a[i];
        if (a[i] < min) min = a[i];
    }
    // 准备桶
    int L = (max - min) / range + 1;
    ArrayList buckets[L];
    for (int i = 0; i < L; i++) {
        InitArrayList(&buckets[i]);
    }

    //放入数据
    for (int i = 0; i < len; i++) {
        int n = a[i];
        Append(&buckets[(n - min) / range], n);
    }

    int k = 0;
    for (int i = 0; i < L; i++) {//桶为分区升序
        ArrayList bucket = buckets[i];
        //排序桶内元素
        insertSort(bucket.elem, bucket.length);
        //放入原数组
        for (int j = 0; j < bucket.length; j++) {
            a[k++] = bucket.elem[j];
        }
    }
}

int main() {
    printf("测试1:\n");
    int arr1[] = {3, 5, 4, 18, 6, 8, 2};
    int len1 = sizeof(arr1) / sizeof(int);
    printf("开始排序:\n");
    bucketSort(arr1, len1);
    printArr(arr1, len1);
    return 0;
}