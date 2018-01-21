/*************************************************************************
	> File Name: wait.c
	> Author: 
	> Mail: 
	> Created Time: 2017年07月10日 星期一 15时27分15秒
 ************************************************************************/

#include<stdio.h>
#include<sys/types.h>
#include<sys/wait.h>
#include<unistd.h>
#include<stdlib.h>
int main(void){
    pid_t pid;
    int s;
    //创建子进程
    pid=fork();
    if(pid==-1){
        perror("fork");
        return -1;
    }
    if(pid==0){//child
        printf("child if %d\n",getpid());
        //sleep(3);
        getchar();
        exit(-1);
    }
    else{//parent
        //阻塞等待子进程的退出, 将子进程的退出信息保存到&s
        //非阻塞
        pid_t w=waitpid(-1,&s,0/*WNOHANG*/);
        printf("parent id %d\n",getpid());
         if(w==0){
            //没等到
            printf("not wait...\n");
            return 1;
         }
         if(w==-1){
            //错误
            perror("waitpid");
            return -1;
         }
        //检测子进程是否正常终止
        if(WIFEXITED(s))
            //输出子进程的正常退出状态码
            printf("normal....exit code %d\n",WEXITSTATUS(s));
        //检测子进程是否被信号打断
         if( WIFSIGNALED(s))
            //被哪个信号打断
            printf("signum %d\n",WTERMSIG(s));
    }
    return 0;
}
