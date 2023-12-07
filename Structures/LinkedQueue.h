#ifndef C_PROJECT_LINKEDQUEUE_H
#define C_PROJECT_LINKEDQUEUE_H

#include <stdbool.h>
#include "Status.h"

typedef struct QNode {
    int data;
    struct QNode *next;
} QNode, *QueuePtr;

typedef struct {
    QueuePtr front;
    QueuePtr rear;
} LinkedQueue;

/**
* 创建一个空队列Q
*/
Status InitQueue(LinkedQueue *Q);

/**
* 初始条件:队列Q已存在
* 操作结果:队列Q被销毁,不再存在
*/
Status DestroyQueue(LinkedQueue *Q);

/**
* 初始条件:队列Q已存在
* 操作结果:将队列Q清为空栈
*/
Status ClearQueue(LinkedQueue *Q);

/**
* 判断栈是否为空
*/
bool QueueEmpty(LinkedQueue Q);

/**
 * 返回栈的长度
 * @param Q
 * @return
 */
int QueueLength(LinkedQueue Q);

Status GetRear(LinkedQueue Q, int *e);

Status GetFront(LinkedQueue Q, int *e);

/**
 * 插入元素e为Q的新队尾元素
 * enter the queue
 */
Status EnQueue(LinkedQueue *Q, int e);

/**
* 删除Q的队头元素,并用e返回其值
*/
Status DeQueue(LinkedQueue *Q, int *e);

/**
* 从队头到队尾,一次队Q的每个数据元素调用函数visit().一旦visit失败则操作失败
*/
Status QueueTraverse(LinkedQueue *Q, int visit(int));

void PrintQueue(LinkedQueue Q); //打印队列

#endif //C_PROJECT_LINKEDQUEUE_H
