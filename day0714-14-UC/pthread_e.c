/*************************************************************************
	> File Name: pthread_e.c
	> Author:UgoLi 
	> Mail: 2653920896@qq.com
	> Created Time: 2017年07月20日 星期四 19时04分32秒
 ************************************************************************/

#include<stdio.h>
#include<pthread.h>
#include<unistd.h>
//线程处理函数，使用return从线程的处理函数退出
void *doit1(void *arg){
    *(int *)arg=9;
    printf("running doit1 ...\n"); 
    return (void *)arg;
}
//使用pthread_exit(3)终止当前线程
void *doit2(void *arg){
    printf("running doit2 ...\n");
    pthread_exit((void *)arg);
}
void *doit3(void *arg){
    while(1){
        printf("running doit3 ...\n");
        sleep(1);
    }
}
int main(void){
    pthread_t tid;
    int **retval;
    int a=1;
    int *p=&a;
    //创建一个新的进程****************************************************
    pthread_create(&tid,NULL,doit1,p);
    //等待线程的汇合
    pthread_join(tid,(void **)retval);
    printf("exit code is %d\n",**(int **)retval);
    //创建一个新的进程****************************************************
    pthread_create(&tid,NULL,doit2,(void *)-2);
    //等待线程的汇合
    pthread_join(tid,(void **)retval);
    printf("exit code is %d\n",*(int *)retval);
    //创建一个新的进程****************************************************
    pthread_create(&tid,NULL,doit3,(void *)-3);
    sleep(10);
    //给doit3发送取消请求
    pthread_cancel(tid);
    //等待线程的汇合
    pthread_join(tid,(void **)retval);
    if(*retval==PTHREAD_CANCELED)
        printf("doit3 cancel...\n");
    return 0;
}












