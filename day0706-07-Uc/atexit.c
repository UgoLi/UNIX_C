/*************************************************************************
	> File Name: atexit.c
	> Author: 
	> Mail: 
	> Created Time: 2017年07月10日 星期一 12时01分48秒
 ************************************************************************/

#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/wait.h>
void doit(void){
    printf("registe function 0\n");
    printf("function 0 %d\n",getpid());
    //printf("release pid:%d\n",wait(NULL));
    sleep(4);
    return;
}
void doit1(void){
    printf("registe function 1\n");
    printf("function 1 %d\n",getpid());
    return;
}
int main(void){
    //向进程注册函数，在进程推出的时候，调用这个函数
    int i=0;
    while(++i){
        getchar();
        //atexit(doit);
        pid_t pid;
        pid=fork();
        if(pid==-1){
            perror("fork");
            return -1;
        }
        if(pid==0){
            printf("child>>>>>>>>>>>>\n");
            printf("creat child pid=%d\n",getpid());
            printf("i=%d\n",i);
            sleep(10);
            exit(0);
        } 
            
        else{
            pid_t pid_re;
            pid_re= fork();
            if(pid_re==-1){
                perror("fork");
                return -1;
            }
            if(pid_re==0){
                
                printf("release pid=%d\n",waitpid(0,NULL,WNOHANG));
                 
                perror("wait");
                exit(0);
            }else{
                printf("parent>>>>>>>>>>>\n");
                sleep(1);
            }
            //getchar();
        }
    }
    //getchar();
    return 0;
}
