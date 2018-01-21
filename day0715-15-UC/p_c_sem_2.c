/*************************************************************************
	> File Name: p_c_sem_2.c
	> Author:UgoLi 
	> Mail: 2653920896@qq.com
	> Created Time: 2017年08月21日 星期一 14时05分05秒
 ************************************************************************/

#include<stdio.h>
#include<pthread.h>
#include<semaphore.h>
#include<stdlib.h>
#include<time.h>
#include<unistd.h>

int queue[5];

sem_t p,c;

void *product(void *arg){
    int rear=0;
    while(1){
        sem_wait(&p);//生产资源--
        
        queue[rear]=rand()%1000+1;  /*共享资源被访问*/
        printf("p:%d\n",queue[rear]);
        
        sem_post(&c);//消费资源++
        
        rear=(rear+1)%5;
        sleep(rand()%5);
    }
}
void *consume(void *arg){
    int front=0; 
    int tmp;
    while(1){
        sem_wait(&c);//等待资源，有资源立即返回，没有阻塞
        
        tmp=queue[front];
        queue[front]=-1;
        
        sem_post(&p);
        
        printf("c:%d\n",tmp);
        front=(front+1)%5;
        
        sleep(rand()%5);
    }
}




int main(void){
    pthread_t pid,cid; 

    sem_init(&p,0,5);//初始化多线程，生产资源数5
    sem_init(&c,0,0);//...,消费资源数0

    pthread_create(&pid,NULL,product,NULL);
    pthread_create(&cid,NULL,consume,NULL);

    pthread_join(pid,NULL);
    pthread_join(cid,NULL);

    sem_destroy(&p);
    sem_destroy(&c);

    return 0;
}













