/*************************************************************************
	> File Name: heap.c
	> Author: 
	> Mail: 
	> Created Time: 2017年07月06日 星期四 11时16分36秒
 ************************************************************************/

#include<stdio.h>
#include<stdlib.h>
#include<sys/types.h>
#include<unistd.h>
#include<string.h>
/*
void *myfunc(void){
    int flag=3;
    return &flag;
}
*/
int main(void){
    printf("pid: %d\n",getpid());
    char *p;
    p=(char *)malloc(1024);
    printf("p %p",p);
    strcpy(p,"hello tarena");
    printf("%s\n",p);

    getchar();
    free(p);
    p=NULL;

    return 0;
}
