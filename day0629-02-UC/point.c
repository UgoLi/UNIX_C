/*************************************************************************
	> File Name: point.c
	> Author: 
	> Mail: 
	> Created Time: 2017年06月29日 星期四 10时02分11秒
 ************************************************************************/

#include<stdio.h>
int main(void){
    int var_a=5,var_b=321;
    char var_c='v';

    char  *p=&var_a;
    printf("var_a address %p\n",&var_a);
    printf("p content %p\n",p);
    printf("&p=%p\n",&p);
    printf("*p=%d\n",*p);
    int **q=NULL;
    q=&p;
    printf("q=%p\n",q);
    printf("*q=%p\n",*q);
    printf("**q=%d\n",**q);
    return 0;
}
