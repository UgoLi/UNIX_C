/*************************************************************************
	> File Name: on_exit.c
	> Author: 
	> Mail: 
	> Created Time: 2017年07月10日 星期一 14时17分55秒
 ************************************************************************/

#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
//进程推出的时候调用的函数
void doit(int n,void *str){
    printf("doit0:n=%d\t%s\n",n,(char*)str);
    return ;
}
void doit1(int n,void *str){
    printf("doit1:n=%d\t%s\n",n,(char*)str);
    return;
}
int main(void){
    //向进程注册函数
    on_exit(doit,"on exit...\n");
    on_exit(doit1,"on exit...again...\n");
    pid_t pid;
    pid=fork();
    if(pid==-1){
        perror("fork");
        return -1;
    }
    if(pid==0){
        printf("child>>>>>>>>>>>>\n");
        exit(1);
    }
    else{
        sleep(3);
        printf("parent>>>>>>>>>>>\n");
        exit(5);
    }
    exit(3);
}
