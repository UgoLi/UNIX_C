/*************************************************************************
	> File Name: fork.c
	> Author: 
	> Mail: 
	> Created Time: 2017年07月10日 星期一 10时15分53秒
 ************************************************************************/

#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>
int main(void){
    pid_t pid;

    //创建子进程
    pid=fork();
    if(pid==-1){//产生错误
        perror("fork");
        return -1;
    }
    if(pid==0){
        sleep(1);
        printf("child....\n");
        printf("child pid:%d\n",getpid());
        printf("parent of child:%d\n",getppid());
    }
    else{
        exit(0);
        printf("parent....\n");
        printf("parent pid:%d\n",getpid());
        printf("parent of parent:%d\n",getppid());
    }
    return 0;
}
