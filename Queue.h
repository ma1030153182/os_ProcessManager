#ifndef QUEUE_H_LY
#define QUEUE_H_LY
#include "Typedefine.h"

Queue * InitQueue();    //初使化队列信息
int EnQueue(Queue *Q,Elemtype x);    //进队（因为没有队满的情况,所以没有返回值）
int DeQueue(Queue *Q,Elemtype *x);    //出队，x为出队结点的数据域，返回1成功/0失败
int QueueEmpty(Queue Q);    //判断队列空1（不空）/0（为空）
int QueueCount(Queue *HQ);    //统计一个栈链中的元素的个数
boolean QueueFull(Queue Q);    //判断队列是否为满，满返回TRUE，非满返回FALSE
#endif
