/*************************************************************************
	> File Name: file.c
	> Author: 
	> Mail: 
	> Created Time: 2017年07月03日 星期一 16时14分10秒
 ************************************************************************/

#include<stdio.h>
#include <errno.h>
int main(void){
    FILE *fp=fopen("hello","r");
    if(!fp){
        //printf("open file fail...%d\n",\
              errno);
        perror("fopen");
        return -1;
    }
    fclose(fp);
    return 0;
}
