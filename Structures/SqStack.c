// Author: 绝迹的星 
// Created on 2023/10/26
#include "Status.h"
#include "malloc.h"

/*
-Hello World.
-You are my world too.
*/

typedef struct {
    int *base;
    int *top;
    int size;
} Stack;

int getLength(Stack stack) {
    return stack.size;
}

Status init_SqStack(Stack *stack) {  //初始化栈
    stack->base = malloc(sizeof(int) * DEFAULT_CAPACITY);
    stack->size = DEFAULT_CAPACITY;
    if (!stack->base) exit(ERROR);
    stack->top = 0;
    return OK;
}

Status pop_SqStack(Stack *stack, int *e) { //弹栈
    if (stack->top == stack->base) exit(ERROR);
    stack->top--;
    *e = *stack->top;
    stack->size--;
    return OK;
}

Status push_SqStack(Stack *stack, int e) {
    if (stack->size == stack->top - stack->base) {
        exit(OVERFLOW); // 栈满, 退出
    }
    *stack->top = e;
    stack->top++;
    stack->size++;
    return OK;
}

Status peek_SqStack(Stack *stack, int *e) {
    if (stack->base == stack->top)
        exit(ERROR); // 空栈
    *e = *(stack->top - 1);
    return OK;
}

