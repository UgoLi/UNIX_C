/*************************************************************************
	> File Name: test.c
	> Author:UgoLi 
	> Mail: 2653920896@qq.com
	> Created Time: 2017年07月14日 星期五 12时19分46秒
 ************************************************************************/

#include<stdio.h>
#include<signal.h>
#include<sys/types.h>
#include<unistd.h>

void doit(int n){
    printf("recv...%d\n",n);
    return;
}
int main(){
    signal(3,doit);
    printf("pid:%d\n",getpid());
    while(1);
    return 0;
}
