/*************************************************************************
	> File Name: file.c
	> Author: 
	> Mail: 
	> Created Time: 2017年07月03日 星期一 16时14分10秒
 ************************************************************************/

#include<stdio.h>
extern int errno;
int main(void){
    FILE *fp=fopen("hello","r");
    printf("%d\n",errno);
    if(!fp){
        //printf("open file fail...%d\n",\
              errno);
        perror("fopen");
        return -1;
    }
    fclose(fp);
    return 0;
}
