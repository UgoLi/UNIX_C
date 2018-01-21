/*************************************************************************
	> File Name: p_c_cond_2.c
	> Author:UgoLi 
	> Mail: 2653920896@qq.com
	> Created Time: 2017年08月21日 星期一 10时05分37秒
 ************************************************************************/

#include<stdio.h>
#include<pthread.h>
#include<time.h>
#include<stdlib.h>
#include<unistd.h>

typedef struct node{
    int data;
    struct node *next;
}node_t;

typedef node_t *link_t;
link_t head=NULL;

pthread_mutex_t mutex=PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t cond=PTHREAD_COND_INITIALIZER;



//生产者
void *product(void *argv){
    node_t *p;
    while(1){
        //生产一个新节点
        p=(node_t *)malloc(sizeof(node_t *));
        p->data=rand()%1000+1;
        printf("product p:%d\n",p->data);
        //+锁
        pthread_mutex_lock(&mutex);
        p->next=head;
        head=p;
        //-锁
        pthread_mutex_unlock(&mutex);
        //通知消费者
        pthread_cond_signal(&cond);
        //sleep(rand()%10+1);
        sleep(10);
    }
    return NULL;
}
//消费者
void *consume(void *argv){
    while(1){
        //+锁
        pthread_mutex_lock(&mutex);
        if(head==NULL){
            //等待  
            struct timespec timeout;
            timeout.tv_sec=time(0)+5;
            timeout.tv_nsec=0;
            pthread_cond_timedwait(&cond,&mutex,&timeout);
        }
        node_t *tmp=head;
        head=head->next;
        //-锁
        pthread_mutex_unlock(&mutex);
        //消费节点
        printf("consume :%d\n",tmp->data);
        free(tmp);
        tmp=NULL;
        sleep(rand()%5+1);
    }
    return NULL;
}


int main(void){
    pthread_t pid,cid;
    srand(time(0));
    //创建两个线程，用于生产者和消费者
    pthread_create(&pid,NULL,product,NULL);
    pthread_create(&cid,NULL,consume,NULL);
    //进程汇合
    pthread_join(pid,NULL);
    pthread_join(cid,NULL);
    pthread_mutex_destroy(&mutex);
    pthread_cond_destroy(&cond);
    return 0;
}











