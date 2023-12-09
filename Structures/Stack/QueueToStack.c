// Author: 绝迹的星 
// Created on 2023/11/9


#include <stdio.h>
#include "../队列/SqQueue.c"

//使用单队列模拟栈
typedef struct MyStack {
    SqQueue q;//队列头->栈顶,队列尾->栈底
    /*
     * 队头           队尾
     * -----------------
     *  q
     * -----------------
     * 栈顶           栈底
     */
} MyStack;

Status InitStack(MyStack *s) {
    InitQueue(&s->q);
    return OK;
}

/**
 * 压栈
 * @param s Stack
 * @param e 要添加的元素值
 * @return
 */
Status Push(MyStack *s, int e) {
    if (IsFull(s->q)) {
        exit(ERROR);
    }
    //添加元素到队列头部,先添加元素到尾部,再把前面的所有元素都移到尾部
    int len = GetLength(s->q);//前面的元素个数
    Offer(&s->q, e);//压栈
    for (int i = 0; i < len; i++) {//前面的移到队尾
        int prev;
        Poll(&s->q, &prev);
        Offer(&s->q, prev);
    }
    return OK;
    /*
     * 添加元素e到栈顶的演示:
     *
     * 队头     队尾        队头     队尾       队头     队尾
     * -----------       -------------       -------------
     * e1 e2        -->   e1 e2 e       -->   e e1 e2
     * -----------       -------------       -------------
     * 栈顶    栈底         栈顶    栈底        栈顶    栈底
     */
}

/**
 * 弹栈
 * @param s Stack
 * @param e 用于存储弹出元素值
 * @return
 */
Status Pop(MyStack *s, int *e) {
    if (IsEmpty(s->q)) {
        exit(ERROR);
    }
    Poll(&s->q, e);//弹出队头即可
    return OK;
}

/**
 * 获取栈顶元素
 * @param s Stack
 * @return
 */
int GetTop(MyStack s) {
    if (IsEmpty(s.q)) {
        exit(ERROR);
    }
    return Peek(s.q);
}

/**
 * 获取栈内元素个数
 * @param s Stack
 * @return
 */
int GetStackLength(MyStack s) {
    return GetLength(s.q);
}

/**
 * 打印栈内元素
 * @param s
 */
void PrintStack(MyStack s) {
    printf("栈顶->栈底:");
    PrintQueue(s.q);
}


/**
 * 销毁栈
 * @param s Stack
 */
void DestroyStack(MyStack *s) {
    ClearQueue(&s->q);
}

int main(void) {
    MyStack s;
    InitStack(&s);
    Push(&s, 1);
    Push(&s, 2);
    Push(&s, 3);
    Push(&s, 4);
    PrintStack(s);// [4,3,2,1]
    int e;
    Pop(&s, &e);
    printf("弹出的元素为:%d\n", e);//4
    PrintStack(s);//[3,2,1]
    int len = GetStackLength(s);
    printf("弹出一个元素后的长度为:%d\n", len);//3
    printf("此时栈顶元素为:%d\n", GetTop(s));//3
    DestroyStack(&s);
}