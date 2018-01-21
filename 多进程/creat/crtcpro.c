/*************************************************************************
	> File Name: crtcpro.c
	> Author:UgoLi 
	> Mail: 2653920896@qq.com
	> Created Time: 2017年08月11日 星期五 09时07分56秒
 ************************************************************************/

#include<stdio.h>
#include<sys/types.h>
#include<sys/wait.h>
#include<unistd.h>
#include<stdlib.h>
#include<time.h>
#include<printf_color.h>

int re_cnt=0;
int cr_cnt=0;
void handler(int sig){
    pid_t pid;
    int status;
    if(sig==SIGCHLD){//signal of child process termination
        printf("handler pid=%d\n",getpid());
        while(1){
        pid=waitpid(-1,&status,WNOHANG);    
        if(pid==-1){
            perror("waitpid");
            return;
        }
        else if(pid==0){
            //printf("no signal recived\n");
            break;
        }else{
            re_cnt++;
            printf("release pro id=%d=====================================\n",pid);
            //sleep(2);
            if(WIFSIGNALED(status)){
                printf("terminated by signal %d\n",WTERMSIG(status));
            }
            if(WIFEXITED(status)){
                printf("child exit code=%d\n",WEXITSTATUS(status));
            }
            printf("release over============================================\n");
            }
            printf("\n\n\n\n\n");
        }
    }
}

int main(int argc,char** argv){
    printf(PURPLE);
    pid_t pid;
    signal(SIGCHLD,handler);
    int n=atoi(*(argv+1));
    while(n--){
        //getchar();
        pid=fork();
        if(pid==-1){//erro
            perror("fork");
            return -1;
        }else if(pid==0){//child
            break;
        }else{//parent
            //sleep(1);
            cr_cnt++;
            continue;   
        }
    }
    if(pid==0){
        printf("new child pro %d\n",getpid());
        printf("cr_cnt=%d\n",cr_cnt);
        
        char *const ps_argv[]={"ps","-o","pid,ppid,pgrp,comm",NULL};
        extern char **environ; 
        system("./delay");
        
        /*execle(3)测试
        execle("/bin/ps","ps","-o","pid,ppid,pgrp,comm",NULL,environ);
        perror("execle");
        */
        /*execl(3)测试
        execl("/bin/ps","ps","-o","pid,ppid,pgrp,comm",NULL);
        perror("execl");
        */

        /*execvp(3)测试
        execvp("ps",ps_argv);
        perror("execvp");
         
        char *const argv[]={"ls","-al",NULL};
        execvp("ls",argv);
        perror("execvp");
        */
        
        /*退出状态测试*/
        //srand(getpid());
        //int a=rand()%10+1;
        //alarm(a);
        //sleep(5);
        exit(10);
    }
    getchar();
    printf("create  cr_cnt=%d\n",cr_cnt);
    printf("release rl_cnt=%d\n",re_cnt);
    getchar();
    printf(NONE);
    return 0;
}
