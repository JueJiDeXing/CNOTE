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
* ����һ���ն���Q
*/
Status InitQueue(LinkedQueue *Q);

/**
* ��ʼ����:����Q�Ѵ���
* �������:����Q������,���ٴ���
*/
Status DestroyQueue(LinkedQueue *Q);

/**
* ��ʼ����:����Q�Ѵ���
* �������:������Q��Ϊ��ջ
*/
Status ClearQueue(LinkedQueue *Q);

/**
* �ж�ջ�Ƿ�Ϊ��
*/
bool QueueEmpty(LinkedQueue Q);

/**
 * ����ջ�ĳ���
 * @param Q
 * @return
 */
int QueueLength(LinkedQueue Q);

Status GetRear(LinkedQueue Q, int *e);

Status GetFront(LinkedQueue Q, int *e);

/**
 * ����Ԫ��eΪQ���¶�βԪ��
 * enter the queue
 */
Status EnQueue(LinkedQueue *Q, int e);

/**
* ɾ��Q�Ķ�ͷԪ��,����e������ֵ
*/
Status DeQueue(LinkedQueue *Q, int *e);

/**
* �Ӷ�ͷ����β,һ�ζ�Q��ÿ������Ԫ�ص��ú���visit().һ��visitʧ�������ʧ��
*/
Status QueueTraverse(LinkedQueue *Q, int visit(int));

void PrintQueue(LinkedQueue Q); //��ӡ����

#endif //C_PROJECT_LINKEDQUEUE_H
