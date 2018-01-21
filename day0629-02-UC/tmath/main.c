/*************************************************************************
	> File Name: main.c
	> Author: 
	> Mail: 
	> Created Time: 2017年06月28日 星期三 16时43分17秒
 ************************************************************************/

#include<stdio.h>
#include "tmath.h"
int main(void){
    int x=6,y=6;
    int (*f[4])(int,int)={tadd,tsub,tmul,tdiv};
    //f=tadd;
    printf("6+6=%d\n",f[0](x,y));
    //f=tsub;
    printf("6-6=%d\n",f[1](x,y));
    printf("6*6=%d\n",f[2](x,y));
    printf("6/6=%d\n",f[3](x,y));
}
