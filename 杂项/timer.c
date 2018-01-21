/*************************************************************************
	> File Name: timer.c
	> Author:UgoLi 
	> Mail: 2653920896@qq.com
	> Created Time: 2017年07月17日 星期一 19时33分39秒
 ************************************************************************/

#include<stdio.h>
#include<signal.h>
#include<sys/time.h>
void doit(int n){
    printf("recv ... %d\n",n);
    return;
}
int main(void){
    struct itimerval new,old;
    signal(SIGALRM,doit);
    //doit(ITIMER_REAL);
    /*初始化new的值*/
    new.it_value.tv_sec=3;
    new.it_value.tv_usec=0;
    new.it_interval.tv_sec=1;
    new.it_interval.tv_usec=0;
    //设置定时器,3秒以后开始。每间隔一秒发送一次信号
    int s=setitimer(ITIMER_REAL,&new,&old);
    /*printf("old.it_value.tv_sec=%ld\n\
           old.it_value.tv_usec=%ld\n\
           old.it_interval.tv_sec=%ld\n\
           old.it_interval.tv_usec=%ld\n",
          old.it_value.tv_sec,
          old.it_value.tv_usec,
          old.it_interval.tv_sec,
          old.it_interval.tv_usec);*/
    if(s==-1){
        perror("setitimer");
        return -1;
    }
    //while(1);
    getchar();
    return 0;
}
