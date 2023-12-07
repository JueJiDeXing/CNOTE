// Author: 绝迹的星 
// Created on 2023/11/10


#include <stdio.h>
#include "SqStack.c"

//使用双栈模拟队列
typedef struct MyQueue {
    Stack s1;//栈1底->队头
    Stack s2;//栈2底->队尾
    //栈2为空时,栈1顶->队尾
    //栈1为空时,栈2顶->队头
    /*
     * 队头                  队尾
     * ----------       -----------
     * | s1                     s2 |
     * ----------       -----------
     */
} MyQueue;

/**
 * 初始化队列
 * @param queue
 * @return
 */
Status InitQueue(MyQueue *queue) {
    InitStack(&queue->s1);
    InitStack(&queue->s2);
    return OK;
}

/**
 * 添加元素到队尾
 * @param queue 队列
 * @param e 要添加的元素
 * @return
 */
Status Offer(MyQueue *queue, int e) {
    //添加元素到队尾
    // 先把栈2的元素全部转移至栈1
    // 此时栈1顶即为队头,添加元素到栈1即可
    while (!IsEmpty(queue->s2)) {
        int elemInS2;
        Pop(&queue->s2, &elemInS2);
        Push(&queue->s1, elemInS2);
    }
    Push(&queue->s1, e);//入栈1
    return OK;
    /*
     *添加元素e到队列尾的演示:
     *
     * 队头                  队尾
     * ------------     ------------
     * | e1                  e2 e3 |
     * ------------     ------------
     * =>
     * 队头                  队尾
     * ------------     ------------
     * | e1 e2 e3                  |
     * ------------     ------------
     * =>
     * 队头                  队尾
     * ------------     ------------
     * | e1 e2 e3 e                 |
     * ------------     ------------
     */
}

/**
 * 弹出队头元素
 * @param queue 队列
 * @param e 用于存储弹出的值
 * @return
 */
Status Poll(MyQueue *queue, int *e) {
    // 先把栈1的元素全部转移至栈2
    // 此时栈2顶即为队头,弹出栈2顶部元素即可
    while (!IsEmpty(queue->s1)) {
        int elemInS1;
        Pop(&queue->s1, &elemInS1);
        Push(&queue->s2, elemInS1);
    }
    Pop(&queue->s2, e);
    return OK;
}

/**
 * 获取队列头部元素
 * @param queue 队列
 * @return
 */
int Peek(MyQueue queue) {
    while (!IsEmpty(queue.s1)) {
        int elemInS1;
        Pop(&queue.s1, &elemInS1);
        Push(&queue.s2, elemInS1);
    }
    return GetTop(queue.s2);
}

/**
 * 获取队列内的元素个数
 * @param queue 队列
 * @return
 */
int GetQueueLength(MyQueue queue) {
    return GetLength(queue.s1) + GetLength(queue.s2);
}

/**
 * 打印队列
 * @param queue 队列
 */
void PrintQueue(MyQueue *queue) {
    while (!IsEmpty(queue->s2)) {//先全部转到s1中再调用栈的打印方法
        int elemInS2;
        Pop(&queue->s2, &elemInS2);
        Push(&queue->s1, elemInS2);
    }
    printf("队头->队尾:");
    PrintStack(queue->s1);
}


/**
 * 销毁队列
 * @param queue 队列
 */
void DestroyQueue(MyQueue *queue) {
    ClearStack(&queue->s1);
    ClearStack(&queue->s2);
}


int main(void) {
    MyQueue q;
    InitQueue(&q);
    Offer(&q, 1);
    Offer(&q, 2);
    Offer(&q, 3);
    Offer(&q, 4);
    PrintQueue(&q);//队头->队尾:[1,2,3,4]
    int e;
    Poll(&q, &e);
    printf("出队元素为:%d\n", e);//1
    PrintQueue(&q);//队头->队尾:[2,3,4]
    printf("当前队列长度为:%d\n", GetQueueLength(q));//3
    printf("此时队头元素为:%d\n", Peek(q));//2
    DestroyQueue(&q);
}