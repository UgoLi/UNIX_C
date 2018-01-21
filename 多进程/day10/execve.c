#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int main(void){
    char *e_argv[]={"myenv",NULL};
    char *e_envp[]={"tarena=guangqumen",\
        NULL};
    //创建子进程
    pid_t pid=fork();
    if(pid==-1){
        perror("fork");
        return -1;
    }
    if(pid==0){//子进程负责的事情
        //加载新的映像替换掉旧的
        execve("./myenv",e_argv,e_envp);
        perror("execve");
        exit(0);
    }else{//父进程负责的事情
        wait(NULL);
    }
    return 0;
}
