/*************************************************************************
	> File Name: mysleep.c
	> Author:UgoLi 
	> Mail: 2653920896@qq.com
	> Created Time: 2017年07月14日 星期五 19时42分22秒
 ************************************************************************/

#include<stdio.h>
#include<unistd.h>
#include<signal.h>
unsigned int mysleep(unsigned int seconds){
    alarm(seconds);
    pause();
    unsigned int r=alarm(0);
    return r;
}
//信号处理程序
void doit(int n){ 
    printf("doit...\n");
    return ;
}

int main(){
    signal(SIGALRM,doit);
    while(1){
        mysleep(2);
        printf("hello...\n");
    }
}


