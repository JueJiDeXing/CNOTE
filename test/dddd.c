// Author: 绝迹的星 
// Created on 2023/12/10


#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>


int stack() {
    int n;
    scanf("%d", &n);
    int arr[n];
    for (int i = 0; i < n; i++) {
        scanf("%d", &arr[i]);
    }
    int rightMin[n], leftMin[n];
    for (int i = 0; i < n; i++) {
        leftMin[i] = -1;
        rightMin[i] = -1;
    }
    int stack[n];
    int stackNum = 0;
    for (int i = 0; i < n; i++) {
        while (stackNum != 0 && arr[stack[stackNum - 1]] > arr[i]) {
            rightMin[stack[--stackNum]] = i;
        }
        stack[stackNum++] = i;
    }
    stackNum = 0;
    for (int j = n - 1; j >= 0; j--) {
        while (stackNum != 0 && arr[stack[stackNum - 1]] > arr[j]) {
            leftMin[stack[--stackNum]] = j;
        }
        stack[stackNum++] = j;
    }
    long count = n - 1;
    for (int i = 1; i < n - 1; i++) {
        int iLeft = leftMin[i] + 1;
        int iRight = rightMin[i] - 1;
        if (arr[i] < arr[iLeft] && arr[i] < arr[iRight]) {
            int d1 = i - iLeft;
            int d2 = iRight - i;
            count += d1 * d2;
        }
    }
    printf("%ld", count);
    return 0;
}

int max() {
    int n;
    scanf("%d", &n);
    int arr[n];
    for (int i = 0; i < n; i++) {
        scanf("%d", &arr[i]);
    }
    int count = n - 1;
    for (int i = 0; i < n - 2; i++) {
        for (int j = i + 2; j < n; j++) {
            int min = arr[i] <= arr[j] ? arr[i] : arr[j];
            int flag = 0;
            for (int k = i + 1; k < j; k++) {
                if (arr[k] > min) {
                    flag = 1;
                    break;

                }
            }
            if (flag == 0) {

                count++;
            }
        }
    }
    printf("%d", count);
    return 0;
}