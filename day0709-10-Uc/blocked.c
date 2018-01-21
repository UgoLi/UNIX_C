/*************************************************************************
	> File Name: blocked.c
	> Author:UgoLi 
	> Mail: 2653920896@qq.com
	> Created Time: 2017年07月14日 星期五 15时29分29秒
 ************************************************************************/

#include<stdio.h>
#include<signal.h>

void doit(int n){
    printf("recv...%d\n",n);
    return;
}

int main(void){
    sigset_t set,pset,oldset;//设置进程的信号屏蔽字
    sigemptyset(&set);//初始化set信号集为空
    int is,i=0;
    //自定义接收到2、3信号的动作
    signal(SIGINT,doit);
    signal(SIGQUIT,doit);
    signal(45,doit);
    //将2号信号添加到set集合中
    sigaddset(&set,SIGINT);
    sigaddset(&set,SIGQUIT);
    sigaddset(&set,45);
    sigaddset(&set,SIGKILL);//阻塞不起作用
    sigaddset(&set,SIGSTOP);//阻塞不起作用
    //将set信号集设置为进程的信号屏蔽字
    int s=sigprocmask(SIG_SETMASK,&set,NULL);
    if(s==-1){
        printf("set erro\n");
        return -1;
    }
    /*在不知道原信号屏蔽字的情况下，检测阻塞信号的号码*/
    //将pset清为空
    sigemptyset(&pset);
    s=sigprocmask(SIG_UNBLOCK,&pset,&oldset);
    if(s==-1){
        printf("set erro\n");
        return -1;
    }
    if((is=sigismember(&pset,2))==1){
        printf("2 blocked....\n");
    }
    //恢复原来的信号阻塞
    sigprocmask(SIG_SETMASK,&oldset,NULL);
    while(i<20000000){
        printf("%d\n",i++);
    }  
    //解除对2、3信号的阻塞
    s=sigprocmask(SIG_UNBLOCK,&set,&oldset);
    while(1);
    return 0;
}
