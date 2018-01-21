/*************************************************************************
	> File Name: psh.h
	> Author:UgoLi 
	> Mail: 2653920896@qq.com
	> Created Time: 2017年08月12日 星期六 14时06分17秒
 ************************************************************************/

#ifndef _SPH_H
#define _SPH_H
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
#include<sys/stat.h>
#include<sys/types.h>
#include<fcntl.h>
#include<sys/wait.h>
#include"printf_color.h"
#include<time.h>
#include<signal.h>

extern int pipe_flag;//'|'exist 1,otherwise,0
extern int argc; //argc参数个数

typedef struct ctime_t{
    char *week;
    char *month;
    int day;
    int h;
    int m;
    int s;
    unsigned int year;
}ctime_t_loc;
void getcmd(char*,int ,char* [],int);

void cd(char *[]);

char *getLocTime();

void dostart();
void doexit();
int psh_pipe(int,char **);
#endif
