/*************************************************************************
	> File Name: pending.c
	> Author:UgoLi 
	> Mail: 2653920896@qq.com
	> Created Time: 2017年07月14日 星期五 17时01分07秒
 ************************************************************************/

#include<stdio.h>
#include<signal.h>
#include<unistd.h>
int main(void){
    sigset_t set,pset;//set用于设置进程的信号屏蔽字。pset用户获取进程的未决信号
    int is;
    //初始化信号屏蔽字
    sigemptyset(&set);
    //将2信号添加到信号屏蔽字的合集里
    sigaddset(&set,SIGINT);
    //将set设置为进程的信号屏蔽字
    sigprocmask(SIG_SETMASK,&set,NULL);
    while(1){
        sleep(1);
        sigpending(&pset);
        //测试2好信号是否是pset信号集中的成员。
        if(is=sigismember(&pset,2)){
            printf("pending...2\n");
        }
    }
    return 0;
}


