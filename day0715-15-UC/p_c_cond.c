/*************************************************************************
	> File Name: p_c_cond.c
	> Author:UgoLi 
	> Mail: 2653920896@qq.com
	> Created Time: 2017年07月21日 星期五 15时30分19秒
 ************************************************************************/

#include<stdio.h>
#include<pthread.h>
#include<stdlib.h>
#include<unistd.h>

typedef struct node_t{
    int data;
    struct node_t *next;
}node_t;

//初始化链表为空
node_t *head=NULL;
//静态初始化
pthread_mutex_t mutex=PTHREAD_MUTEX_INITIALIZER;
//初始化一个条件变量，用于通知消费者
pthread_cond_t cond=PTHREAD_COND_INITIALIZER;

/*生产者线程*/
void *pro(void *arg){
    node_t *new;
    while(1){
        //生产一个新的节点
        new=(node_t *)malloc(sizeof(node_t));
        new->data=rand()%1000+1;
        new->next=NULL;
        printf("pro %d\n",new->data);
        
        //加锁
        pthread_mutex_lock(&mutex);
        //将新节点插入到链表头部
        new->next=head;
        head=new;
        //解锁
        pthread_mutex_unlock(&mutex);
        //通知消费者，新节点生产出来了
        pthread_cond_signal(&cond);
        usleep(rand()%1000);
    }
    return NULL;
}
/*消费者线程*/
void *con(void *arg){
    node_t *tmp;
    while(1){
        //加锁
        pthread_mutex_lock(&mutex);
        //等待生产者生产新节点
        if(head==NULL){
            //等待生产新节点
            pthread_cond_wait(&cond,&mutex);
        }
        if(head!=NULL){
            tmp=head;
            head=head->next;
            //解锁
            pthread_mutex_unlock(&mutex);
            //消费tmp指向的节点
            printf("con %d\n",tmp->data);
            free(tmp);
            tmp=NULL;
        }
    }
    usleep(rand()%1000);
    return NULL;
}

int main(void){
    pthread_t pid,cid;
    srand(time(0));//设置随机种子
    //创建生产者和消费者线程
    pthread_create(&pid,NULL,pro,NULL);
    pthread_create(&cid,NULL,con,NULL);
    //等待线程的汇合
    pthread_join(pid,NULL);
    pthread_join(cid,NULL);
    //销毁mutex锁
    pthread_mutex_destroy(&mutex);
    //销毁条件变量cond
    pthread_cond_destroy(&cond);
    return 0;
}

