/*************************************************************************
	> File Name: count.c
	> Author:UgoLi 
	> Mail: 2653920896@qq.com
	> Created Time: 2017年07月21日 星期五 09时50分09秒
 ************************************************************************/

#include<stdio.h>
#include<pthread.h>
#include<unistd.h>
int count=0;
//声明一个mutex锁变量
pthread_mutex_t mutex;
void *doit(void *arg){
    int val,i;
    for(i=0;i<1000;i++){
        //加锁
        pthread_mutex_lock(&mutex);//mutex锁只能被一个线程占有，挂起等待锁自由
        
        printf("\rthread %p ",arg);
        val=count;
        val++;
        printf("val=%d",val);
        fflush(stdout);
        count=val;
        usleep(1000);
        //解锁
        pthread_mutex_unlock(&mutex);//解除本线程对mutex锁的占有
    }
    return NULL;
}
int main(){
    pthread_t tid,cid;

    //初始化mutex
    pthread_mutex_init(&mutex,NULL);
   
    //创建两个新的线程
    pthread_create(&tid,NULL,doit,(void *)1);
    pthread_create(&cid,NULL,doit,(void *)2);
    
    //等待线程的汇合
    pthread_join(tid,NULL);
    pthread_join(cid,NULL);
    printf("\n");
    //销毁mutex锁
    pthread_mutex_destroy(&mutex);
    return 0;
}
