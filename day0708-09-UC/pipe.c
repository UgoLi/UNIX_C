/*************************************************************************
	> File Name: pipe.c
	> Author:UgoLi 
	> Mail: 2653920896@qq.com
	> Created Time: 2017年07月12日 星期三 16时41分52秒
 ************************************************************************/

#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
#include<sys/types.h>
#include<sys/wait.h>

void quite(void){
    printf("程序结束...\n");
    return ;
}
int main(void){
    int fd[2]={0};
    pid_t pid=0;
    pid_t pid1=0;
    char buf[1024]={0};
    char *msg="\rThis is a test...\n";
    char key;
    //父进程创建管道
    int p=pipe(fd);
    if(p==-1){
        perror("pipe");
        return -1;
    }
    //创建子进程
    pid=fork();
    if(pid==-1){
        perror("fork");
        return -1;
    }
    if(pid==0){//子进程 1 负责的工作
        close(fd[1]);
        int r;
        while(1){
            r=read(fd[0],buf,1024);
            printf("子进程 1 读取数据：%d\n",r);
            if(r==-1){
                perror("read");
                return -1;
            }
            if(!r){
                close(fd[0]);
                break;
            }
            //数据处理
            printf("子进程 1 处理中...输出：\n");
            write(STDOUT_FILENO,buf,r);
        }
        exit(1);
    }
    else{//父进程负责的工作
         pid1=fork();
         if(pid1==-1){
             perror("fork1");
             return -1;
         }
         if(pid1==0){//子进程 2 的工作
            int r;
            while(1){
                r=read(STDIN_FILENO,&key,1);
                scanf("%*[^\n]");
                scanf("%*c");
                if(r&&key!='q'){
                    printf("键盘输入 q+Enter 退出...\n");
                }
                if(key=='q'){
                    printf("子进程 2 结束...\n");
                    break;
                }
            }
            exit(0);
        }
        else{//父进程的工作
            close(fd[0]);
            pid_t r_pid1;;
            while(1){
                r_pid1=waitpid(-1,NULL,WNOHANG);
                if(r_pid1==-1){
                    perror("waitpid");
                    return -1;
                }
                if(r_pid1){
                    close(fd[1]);
                    break; 
                }
                sleep(1);
                write(fd[1],msg,strlen(msg));    
            }
            printf("等待子进程 1 处理完数据...\n");
            //waitpid(-1,NULL,WNOHANG);
            wait(NULL);
        }
    }
    atexit(quite);
    return 0;
}
