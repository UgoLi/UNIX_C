/*************************************************************************
	> File Name: test.c
	> Author: 
	> Mail: 
	> Created Time: 2017年06月29日 星期四 14时29分49秒
 ************************************************************************/

#include<stdio.h>
#include "tmath.h"
int process(int (*p)(int ,int ),int x,int y){
    return p(x,y);
}
int main(void){
    int a=6,b=2;
    printf("%d-%d=%d\n",a,b,\
           process(tsub,a,b));
    return 0;
}
