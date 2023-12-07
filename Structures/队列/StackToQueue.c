// Author: 绝迹的星 
// Created on 2023/11/10


#include <stdio.h>
#include "../栈/SqStack.c"

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
Status _InitQueue(MyQueue *queue) {
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
Status _Offer(MyQueue *queue, int e) {
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
Status _Poll(MyQueue *queue, int *e) {
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
int _Peek(MyQueue queue) {
    while (!IsEmpty(queue.s1)) {
        int elemInS1;
        Pop(&queue.s1, &elemInS1);
        Push(&queue.s2, elemInS1);
    }
    int e;
    Peek(&queue.s2,&e);
    return e;
}

/**
 * 获取队列内的元素个数
 * @param queue 队列
 * @return
 */
int _GetLength(MyQueue queue) {
    return GetLength(queue.s1) + GetLength(queue.s2);
}

/**
 * 打印队列
 * @param queue 队列
 */
void _PrintQueue(MyQueue *queue) {
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
void _DestroyQueue(MyQueue *queue) {
    Clear(&queue->s1);
    Clear(&queue->s2);
}


int main(void) {
    MyQueue q;
    _InitQueue(&q);
    _Offer(&q, 1);
    _Offer(&q, 2);
    _Offer(&q, 3);
    _Offer(&q, 4);
    _PrintQueue(&q);//队头->队尾:[1,2,3,4]
    int e;
    _Poll(&q, &e);
    printf("出队元素为:%d\n", e);//1
    _PrintQueue(&q);//队头->队尾:[2,3,4]
    printf("当前队列长度为:%d\n", _GetLength(q));//3
    printf("此时队头元素为:%d\n", _Peek(q));//2
    _DestroyQueue(&q);
}