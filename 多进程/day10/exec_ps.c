#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int main(void){
    char *ps_argv[]={"ps","-o",\
        "pid,ppid,pgrp,comm",NULL};

    //创建子进程
    pid_t pid=fork();
    if(pid==-1){
        perror("fork");
        return -1;
    }
    if(pid==0){//子进程负责
        printf("child pid %d\n",getpid());
        //execv("/bin/ps",ps_argv);
        //execvp("ps",ps_argv);
        execlp("ps","ps","-o",\
                "pid,ppid,pgrp,comm",NULL);

        perror("execvp");
        exit(0);
    }else{//父进程负责
        wait(NULL);
    }
    return 0;
}
