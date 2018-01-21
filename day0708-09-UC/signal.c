/*************************************************************************
	> File Name: signal.c
	> Author:UgoLi 
	> Mail: 2653920896@qq.com
	> Created Time: 2017年07月13日 星期四 16时45分31秒
 ************************************************************************/
#include<stdio.h>
#include<signal.h>
//用户自定义的信号处理函数
void doit(int n){
    printf("recv 2 ...\n");
    return;
}
int main(void){
    //将2号信号的处理程序设置为忽略
    //signal(2,SIG_IGN);
    //将2号信号的处理函数设置为用户自定义的
    signal(3,SIG_IGN);
    signal(2,doit);
    while(1);
    return 0;
}
