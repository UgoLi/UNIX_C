/*************************************************************************
	> File Name: myenv.c
	> Author: 
	> Mail: 
	> Created Time: 2017年07月11日 星期二 17时02分07秒
 ************************************************************************/

#include<stdio.h>
int main(void){
    extern char **environ;
    int i;
    for(i=0;environ[i]!=NULL;i++){
        printf("%s\n",environ[i]);
    }
    getchar();
    return 0;
}
