// Author: 绝迹的星 
// Created on 2023/10/26
#include "../Status.h"
#include "malloc.h"
#include <stdbool.h>
#include <stdio.h>

typedef struct {
    int *base;
    int *top;
    int capacity;
} Stack;

int GetLength(Stack stack) {
    return stack.top - stack.base;
}

bool IsEmpty(Stack stack) {
    return stack.top == stack.base;
}

bool IsFull(Stack stack) {
    return stack.top - stack.base == stack.capacity;
}

Status InitStack(Stack *stack) {  //初始化栈
    stack->base = malloc(sizeof(int) * DEFAULT_SIZE);
    stack->capacity = DEFAULT_SIZE;
    if (!stack->base) exit(ERROR);
    stack->top = 0;
    return OK;
}

Status Pop(Stack *stack, int *e) { //弹栈
    if (stack->top == stack->base) exit(ERROR);
    stack->top--;
    *e = *stack->top;
    return OK;
}

Status Push(Stack *stack, int e) {
    if (stack->capacity == stack->top - stack->base) {
        exit(OVERFLOW); // 栈满, 退出
    }
    *stack->top = e;
    stack->top++;
    stack->capacity++;
    return OK;
}

Status Peek(Stack *stack, int *e) {
    if (stack->base == stack->top)
        exit(ERROR); // 空栈
    *e = *(stack->top - 1);
    return OK;
}


Status Clear(Stack *stack) {
    stack->top = stack->base;
    return OK;
}

Status Destroy(Stack *stack) {
    free(stack->base);
    return OK;
}

void PrintStack(Stack stack) {
    for (int *i = stack.base; i < stack.top; i++) {
        printf("%d ", *i);
    }
}