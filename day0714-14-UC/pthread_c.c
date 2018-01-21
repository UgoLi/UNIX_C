/*************************************************************************
	> File Name: pthread_c.c
	> Author:UgoLi 
	> Mail: 2653920896@qq.com
	> Created Time: 2017年07月20日 星期四 16时55分35秒
 ************************************************************************/

#include<stdio.h>
#include<pthread.h>
#include<unistd.h>
//线程的执行函数
void *doit(void *arg){ 
    printf("%s:%d:%ld\n",(char *)arg,getpid(),pthread_self());
    return NULL;
}
int main(void){
    pthread_t tid;
    //创建新的线程
    pthread_create(&tid,NULL,doit,"new");
    sleep(1);
    doit("main");
    return -1;
}
