/*************************************************************************
	> File Name: reentry.c
	> Author:UgoLi 
	> Mail: 2653920896@qq.com
	> Created Time: 2017年07月17日 星期一 17时27分13秒
 ************************************************************************/

#include<stdio.h>
#include<signal.h>
#include<unistd.h>
int value=1;
void doit(int n){
    int v;
    v=value;
    printf("v=%d\n",v);
    v++;
    usleep(5000);
    value=v;
    return ;
}
int main(void){
    signal(2,doit);
    while(1)
        doit(3);
    return 0;
}
