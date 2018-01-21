/*************************************************************************
	> File Name: big_little.c
	> Author: 
	> Mail: 
	> Created Time: 2017年07月08日 星期六 11时47分44秒
 ************************************************************************/

#include<stdio.h>
int main(void){
    short var_s=0x0001;
    char *p;
    p=(char *)&var_s;
    if(*p){
        printf("little \n");
    }
    else {
        printf("big \n");
    }
    return 0;
}
