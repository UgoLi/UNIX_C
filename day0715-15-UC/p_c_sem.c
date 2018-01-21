/*************************************************************************
	> File Name: p_c_sem.c
	> Author:UgoLi 
	> Mail: 2653920896@qq.com
	> Created Time: 2017年07月21日 星期五 19时03分40秒
 ************************************************************************/

#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<pthread.h>
#include<semaphore.h>
#include<time.h>

int queue[5];
/*
int front=-1;
int rear=-1;
*/
sem_t sem_p,sem_c;//sem_p 可生产的个数，sem_c 可消费资源数


/*生产者,生产添加到队列中*/
void *pro(void *arg){
    int p=0;
    while(1){
        //lock sem_p--
        sem_wait(&sem_p);
        queue[p]=rand()%1000+1;//生产一个数
        printf("pro %d\n",queue[p]);
        printf("仓库：%d %d %d %d %d\n",queue[0],\
               queue[1],queue[2],queue[3],queue[4]);
        //unlock sem_c++
        sem_post(&sem_c);
        p=(p+1)%5;
        sleep(3);
    }
    return NULL;
}
/*消费者,从队列中消费*/
void *con(void *arg){
    int c=0;
    while(1){
        //lock sem_c--
        sem_wait(&sem_c);
        printf("con %d\n",queue[c]);
        queue[c]=0;
        //unlock sem_p++
        sem_post(&sem_p);
        c=(c+1)%5;//数组循环写法
        sleep(4);
    }
    return NULL;
}

int main(void){
    pthread_t pid,cid;
    srand(time(0));
    //初始化信号量
    sem_init(&sem_p,0,5);//初始化生产可用资源5,即仓库目前可接受新生产5个新资源;
    sem_init(&sem_c,0,0);//初始化消费可用资源0,即仓库可消费资源数为0;
    //创建两个线程
    pthread_create(&cid,NULL,con,NULL);
    pthread_create(&pid,NULL,pro,NULL);
    //阻塞等待线程的汇合
    pthread_join(cid,NULL);
    pthread_join(pid,NULL);
    //销毁信号量
    sem_destroy(&sem_p);
    sem_destroy(&sem_c);
    return 0;
}


















