// Author: 绝迹的星 
// Created on 2023/12/28


#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

#include <stdio.h>

void bubbleSort(int *arr, int len) {
    int i, j, temp;
    for (i = 0; i < len - 1; i++) {
        for (j = 0; j < len - 1 - i; j++) {
            if (arr[j] > arr[j + 1]) {// 交换位置
                temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
            }
        }
    }
}

#include <stdio.h>

void average(const double *grades, int numStudents, int numCourses) {
    double total;
    for (int i = 0; i < numStudents; i++) {
        total = 0.0;
        for (int j = 0; j < numCourses; j++) {
            total += *(grades + i * numCourses + j);
        }
        double average = total / numCourses;
        printf("学生 %d 的平均成绩为 %.2f\n", i + 1, average);
    }
}

#include <stdio.h>
#include <string.h>

int countSubstring(const char *str, const char *substr) {
    int count = 0;
    int strLen = strlen(str), substrLen = strlen(substr);

    for (int i = 0; i <= strLen - substrLen; i++) {
        const char *p = str + i;
        if (strncmp(p, substr, substrLen) == 0) {
            count++;
        }
    }

    return count;
}

int main() {
    const char *str = "ababababa";
    const char *substr = "aba";
    int count = countSubstring(str, substr);
    printf("在 '%s' 中 子串 '%s' 出现 %d 次 \n", str, substr, count);
    return 0;
}

