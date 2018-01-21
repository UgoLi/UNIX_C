/*************************************************************************
	> File Name: test.c
	> Author:UgoLi 
	> Mail: 2653920896@qq.com
	> Created Time: 2017年07月26日 星期三 14时01分50秒
 ************************************************************************/

#include<stdio.h>
int main(){
    enum{a,b,c,d,e};
    enum{A,B,C,D,E};
    typedef enum{hello,world}test;
    printf("%d %d %d %d %d\n",a,b,c,d,e);
    printf("%d %d %d %d %d\n",A,B,C,D,E);
    printf("test= %ld byte\n",sizeof(test));
    return 1;
}
