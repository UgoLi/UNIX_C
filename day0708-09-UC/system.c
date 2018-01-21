/*************************************************************************
	> File Name: system.c
	> Author:UgoLi 
	> Mail: 2653920896@qq.com
	> Created Time: 2017年07月12日 星期三 15时31分19秒
 ************************************************************************/

#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
int main(void){
    system("t");
    //execl("/bin/sh","sh","-c","t",NULL);
    //execlp("./t","t",NULL);
    return 0;
}
