// Author: 绝迹的星 
// Created on 2023/12/13


#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>


void fun(int p, int *s) {}

int main(void) {
    int a[50], n;
    fun(n, &a[9]);

    return 0;
}