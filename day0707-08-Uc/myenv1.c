/*************************************************************************
	> File Name: myenv1.c
	> Author: 
	> Mail: 
	> Created Time: 2017年07月11日 星期二 17时09分21秒
 ************************************************************************/

#include<stdio.h>
int main(int argc,char *argv[],char *envp[]){
    int i;
    for(i=0;envp[i]!=NULL;i++){
        printf("%s\n",envp[i]);
    }
    return 0;
}
