/*************************************************************************
	> File Name: send.c
	> Author:UgoLi 
	> Mail: 2653920896@qq.com
	> Created Time: 2017年07月14日 星期五 11时27分13秒
 ************************************************************************/

#include<stdio.h>
#include<signal.h>


//信号的处理函数
void doit(int n){
    printf("recv ... %d\n",n);
    return;
}
int main(void){
    //改变当前进程的信号处理函数
    signal(2,doit);
    while(1){
        sleep(1);
        raise(2);
        printf("send ...2\n");
    }
    return 0;
}
