// Author: 绝迹的星 
// Created on 2023/12/15


#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

void printArr(const int *arr, int len) {
    for (int i = 0; i < len; i++) {
        printf("%d,", arr[i]);
    }
    printf("\b\n");
}

void swap(int *a, int i, int j) {
    int t = a[i];
    a[i] = a[j];
    a[j] = t;
}
