/*************************************************************************
	> File Name: test.c
	> Author:UgoLi 
	> Mail: 2653920896@qq.com
	> Created Time: 2017年07月18日 星期二 00时51分24秒
 ************************************************************************/

#include<stdio.h>
#include<string.h>
int main(){
    char str[50]={0};
    int qty;
    printf("请输入成绩个数:");
    scanf("%d",&qty);
    int num=0;
    for(num=0;num<qty;num++){
        int a;
        printf("输入成绩:");
        scanf("%d",&a);
        char tmp[5]={a/100+48,a/10%10+48,a-a/10*10+48,','};
        strncat(str,tmp,50);
    }
    str[strlen(str)-1]=0;
    printf("%s\n",str);
}
