/*************************************************************************
	> File Name: alarm.c
	> Author:UgoLi 
	> Mail: 2653920896@qq.com
	> Created Time: 2017年07月14日 星期五 13时56分38秒
 ************************************************************************/

#include<stdio.h>
#include<signal.h>
#include<unistd.h>
int main(){
    int i;
    //设置闹钟
    alarm(5);
    for(i=1;i<1000000;i++){
        printf("i=%d\n",i);
    }
    //取消闹钟
    int a=alarm(1);
    printf("a=%d\n",a);
    while(1);
    int a1=alarm(3);
    while(1);
    return 0;
}
