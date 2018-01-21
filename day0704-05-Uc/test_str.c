/*************************************************************************
	> File Name: test_str.c
	> Author:UgoLi 
	> Mail: 2653920896@qq.com
	> Created Time: 2017年07月26日 星期三 15时38分54秒
 ************************************************************************/

#include<stdio.h>
#include<string.h>
int main(){
    char str[128];
    strcpy(str,"hello world");
    perror("");
    printf("%s\n",str);
    return 1;
}
