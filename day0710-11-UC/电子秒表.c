/*************************************************************************
	> File Name: 电子秒表.c
	> Author:UgoLi 
	> Mail: 2653920896@qq.com
	> Created Time: 2017年07月17日 星期一 22时05分44秒
 ************************************************************************/

#include<stdio.h>
#include<signal.h>
#include<sys/time.h>
#include<stdlib.h>
#include<printf_color.h>
void doit(int signum){
    static int seconds=0;
    int hour=seconds/3600;
    int minute=(seconds-hour*3600)/60;
    int second=seconds++-hour*3600-minute*60;
    CLEAR();
    MOVETO(0,0);
    printf(RED"%02d"NONE":"CYAN"%02d"NONE":"GREEN"%02d"WHITE"  按回车键退出\n"NONE,hour,minute,second);
    HIDE_CURSOR();
    return;
}


int main(void){
    struct itimerval new,old;
    new.it_value.tv_sec=1;
    new.it_value.tv_usec=0;
    new.it_interval.tv_sec=1;
    new.it_interval.tv_usec=0;
    //init s=setitimer(ITIMER_REAL,&new,&old);
    if(setitimer(ITIMER_REAL,&new,&old)==-1){
        perror("setitmer");
        exit(EXIT_FAILURE);
    }
    //signal(SIGALRM,doit);
    if(signal(SIGALRM,doit)==SIG_ERR){
        perror("signal");
        return -1;
    }
    //doit(ITIMER_REAL); 
    getchar();
    SHOW_CURSOR();

    new.it_value.tv_sec=0;
    new.it_value.tv_usec=0;
    new.it_interval.tv_sec=0;
    new.it_interval.tv_usec=0;
    if(setitimer(ITIMER_REAL,&new,&old)==-1){
        perror("setitmer");
        exit(EXIT_FAILURE);
    }

    return 0;
}
