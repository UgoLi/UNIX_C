/*************************************************************************
	> File Name: zombie.c
	> Author: 
	> Mail: 
	> Created Time: 2017年07月10日 星期一 14时50分39秒
 ************************************************************************/

#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>
int main(void ){
    pid_t pid;
    //创建子进程
    pid=fork();
    if(pid==-1){
        perror("fork");
        return -1;
    }
    if(pid==0){//子进程
        printf("child pid :%d\n",getpid());
        exit(3);    
    }
    else{//父进程
        getchar();
    }
    return 0;
}
