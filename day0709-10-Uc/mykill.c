/*************************************************************************
	> File Name: mykill.c
	> Author:UgoLi 
	> Mail: 2653920896@qq.com
	> Created Time: 2017年07月14日 星期五 11时39分20秒
 ************************************************************************/

#include<stdio.h>
#include<signal.h>
#include<stdlib.h>
int main(int argc,char *argv[]){
    pid_t pid;
    int sig;
    //argv[1]保存了信号的编号
    sig=atoi(argv[1]);
    pid=atoi(argv[2]);
    kill(pid,sig);
    return 0;
}
