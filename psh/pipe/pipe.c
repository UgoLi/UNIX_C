/*************************************************************************
	> File Name: pipe.c
	> Author:UgoLi 
	> Mail: 2653920896@qq.com
	> Created Time: 2017年08月16日 星期三 18时12分34秒
 ************************************************************************/

#include<stdio.h>
#include<unistd.h>
#include<sys/types.h>
#include<sys/wait.h>
#include<sys/stat.h>
#include<string.h>
#include<fcntl.h>
#include<stdlib.h>

void doit(int n,void *arg){
    printf("%d  %s\n",n,(char*)arg);
}


int swarp(int argc,char **argv){
    int fd[2];
    int k=0;
    on_exit(doit,"doit");
    while(1){
        if(k>=argc-1)break;
        //printf("%s\n",argv[k]);
        if(!strcmp(argv[k],"aa")){
            argv[k]=NULL;
            break;
        }
        k++;
    }
    int n=pipe(fd);
    if(n==-1){
        perror("pipe");
        return -1;
    }
    pid_t pid = fork();
    switch(pid){
        case -1:
            perror("fork");
            return -1;
        case 0:
            close(fd[0]);
            dup2(fd[1],1);
            close(fd[1]);
            execvp(argv[1],argv+1);
            perror("1");
            printf("未找到 '%s' 命令\n",argv[1]);
            return -1;
        default:
            wait(NULL);
            close(fd[1]);
            dup2(fd[0],0);
            execvp(argv[k+1],argv+k+1);
            perror("2");
            printf("未找到 '%s' 命令\n",argv[k+1]);
            return -1;
    }
    return 0;
}

