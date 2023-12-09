// Author: 绝迹的星 
// Created on 2023/10/26
#include "../Status.h"
#include "malloc.h"


typedef struct {
    char **base;
    char **top;
    int size;
} StringStack;


Status InitStack(StringStack *stack) {  //初始化栈
    stack->base = malloc(sizeof(char *) * DEFAULT_SIZE);
    for (int i = 0; i < DEFAULT_SIZE; i++) {
        stack->base[i] = malloc(sizeof(char) * DEFAULT_SIZE);
    }
    if (!stack->base) exit(ERROR);
    stack->size = DEFAULT_SIZE;
    stack->top = stack->base;
    return OK;
}

Status Pop(StringStack *stack, char **e) { //弹栈
    if (stack->top == stack->base) exit(ERROR);
    stack->top--;
    *e = *stack->top;
    return OK;
}

Status Push(StringStack *stack, char **e) {
    if (stack->size <= stack->top - stack->base)
        exit(OVERFLOW); // 栈满, 退出
    *stack->top = *e;
    stack->top++;
    return OK;
}

Status Peek(StringStack stack, char **e) {
    if (stack.base == stack.top)
        exit(ERROR); // 空栈
    *e = *(stack.top - 1);
    return OK;
}

