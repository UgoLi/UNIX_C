/*************************************************************************
	> File Name: exec.c
	> Author: 
	> Mail: 
	> Created Time: 2017年07月11日 星期二 15时39分42秒
 ************************************************************************/

#include<stdio.h>
#include<unistd.h>
#include<sys/types.h>
#include<sys/wait.h>
#include<stdlib.h>
int main(void){
    pid_t pid;
    char *const ps_argv[]={"myenv",NULL};
    char *const ps_envp[]={"NAME=ugo",NULL};
    //创建子进程
    pid=fork();
    if(pid==-1){
        perror("fork");
        return -1;
    }
    if(pid==0){//子进程执行的代码
        execvpe("myenv",ps_argv,ps_envp);
        //子进程可执行程序ps执行完已经exit,下面只有错误\
        //才执行。
        getchar();//不会执行
        perror("execvpe");
        exit(0);
    }
    else{//父进程代码
        //阻塞等待子进程的结束
        wait(NULL);
    }
    return 0;
}
