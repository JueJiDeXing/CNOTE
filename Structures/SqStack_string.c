// Author: 绝迹的星 
// Created on 2023/10/26
#include "Structure/Status.h"
#include "malloc.h"


typedef struct {
    char **base;
    char **top;
    int size;
} StringStack;


Status init_SqStack(StringStack *stack) {  //初始化栈
    stack->base = malloc(sizeof(char *) * DEFAULT_CAPACITY);
    for (int i = 0; i < DEFAULT_CAPACITY; i++) {
        stack->base[i] = malloc(sizeof(char) * DEFAULT_CAPACITY);
    }
    if (!stack->base) exit(ERROR);
    stack->size = DEFAULT_CAPACITY;
    stack->top = stack->base;
    return OK;
}

Status pop_SqStack(StringStack *stack, char **e) { //弹栈
    if (stack->top == stack->base) exit(ERROR);
    stack->top--;
    *e = *stack->top;
    return OK;
}

Status push_SqStack(StringStack *stack, char **e) {
    if (stack->size <= stack->top - stack->base)
        exit(OVERFLOW); // 栈满, 退出
    *stack->top = *e;
    stack->top++;
    return OK;
}

Status peek_SqStack(StringStack stack, char **e) {
    if (stack.base == stack.top)
        exit(ERROR); // 空栈
    *e = *(stack.top - 1);
    return OK;
}

