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
    printf("6+6=%d\n",tadd(x,y));
    printf("6-6=%d\n",tsub(x,y));
    printf("6*6=%d\n",tmul(x,y));
    printf("6/6=%d\n",tdiv(x,y));
}
