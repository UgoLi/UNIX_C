/*************************************************************************
	> File Name: fork_sig.c
	> Author:UgoLi 
	> Mail: 2653920896@qq.com
	> Created Time: 2017年07月14日 星期五 10时14分51秒
 ************************************************************************/

#include<stdio.h>
#include<signal.h>
#include<unistd.h>
#include<stdlib.h>
#include<sys/types.h>
#include<sys/wait.h>
void doit(int n){
    printf("recv ...%d\n",n);
    return;
}
int main(){
    //注册信号的信号处理函数
    signal(2,doit);
    //创建子进程 
    pid_t pid=fork();
    if(pid==-1){
        perror ("fork");
        return -1;
    }
    if(pid==0){
        printf("child pid:%d\n",getpid());
        while(1);
        exit(0);
    }
    else{
        wait(NULL);
    }
    return 0;
}
