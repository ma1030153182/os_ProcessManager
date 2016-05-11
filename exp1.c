#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <errno.h>
#include <sys/ipc.h>
#include <semaphore.h>
#include <fcntl.h>
#include "Queue.h"
#include "const.h"
#define N 5
time_t end_time;
sem_t mutex,full,empty;
int fd;
Queue * qt;    //缓冲区
Elemtype p;
void consumer(void *arg);
void productor(void *arg);

int main(int argc, char *argv[])
{
pthread_t id1,id2,id3,id4,id5;
pthread_t mon_th_id;
int ret;
end_time = time(NULL)+30;
qt = InitQueue();
p.lNumber = 1000;
ret=sem_init(&mutex,0,1);    //初使化互斥信号量为１
ret=sem_init(&empty,0,N);    //初使化empty信号量为N
ret=sem_init(&full,0,0);    //初使化full信号量为０
if(ret!=0)
perror("sem_init");
ret=pthread_create(&id1,NULL,(void *)productor, NULL);    //生产者线程
if(ret!=0)
perror("pthread cread1");
ret=pthread_create(&id3,NULL,(void *)productor, NULL);    //生产者线程
if(ret!=0)
perror("pthread cread3");
ret=pthread_create(&id2,NULL,(void *)consumer, NULL);    //消费者线程
if(ret!=0)
perror("pthread cread2");
ret=pthread_create(&id5,NULL,(void *)productor, NULL);    //生产者线程
if(ret!=0)
perror("pthread cread5");
ret=pthread_create(&id4,NULL,(void *)consumer, NULL);    //消费者线程
if(ret!=0)
perror("pthread cread4");
pthread_join(id1,NULL);
pthread_join(id2,NULL);
pthread_join(id3,NULL);
pthread_join(id4,NULL);
pthread_join(id5,NULL);
exit(0);
}
void productor(void *arg)    //生产者线程
{
int i,nwrite;
while(time(NULL) < end_time)
{
sem_wait(&empty);    // p(empty)
sem_wait(&mutex);    // p(mutex)
if(TRUE==QueueFull(*qt))    //队满
{
printf("Productor:buffer is full ,please try to write  later.\n");
}
else
{
EnQueue(qt,p);
printf("Productor:write [%ld] to buffer \n",p.lNumber);
p.lNumber++;
}
sem_post(&full);    //v(full)
sem_post(&mutex);    //v(mutex)
sleep(1);
}
}    //生产者productor

void consumer(void *arg)    //消费者线程
{
int nolock=0;
int ret,nread;
Elemtype p2;
while((time(NULL) < end_time)||(FALSE==(QueueEmpty(*qt))))
{
sem_wait(&full);    //p(full)
sem_wait(&mutex);    //p(mutex)
if(TRUE==QueueEmpty(*qt))    //队空
{
printf("Consumer:the buffer is empty,please try to read later.\n");
}
else
{
DeQueue(qt,&p2);
printf("Consumer:read [%ld] from buffer.\n",p2.lNumber);
}
sem_post(&empty);    //v(empty)
sem_post(&mutex);    //v(mutex)
sleep(2);
}    //end of while((time(NULL) < end_time)||(FALSE==(QueueEmpty(*qt))))
}    //消费者consumer

