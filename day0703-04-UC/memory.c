/*************************************************************************
	> File Name: memory.c
	> Author: 
	> Mail: 
	> Created Time: 2017年07月06日 星期四 09时00分24秒
 ************************************************************************/

#include<stdio.h>
#include<sys/types.h>
#include<unistd.h>
#include<string.h>
int flag;
void count(void){
    static int value=1;
    printf("value++=%d\n",value++);
    printf("&value=%p\n",&value);
    return;
}
int main(void){
    char *str="hello tarena";
    char *str1="hello tarena";
    char str2[]={"hello tarena"};
    char str3[24];
    char *str4;
    int i;
    //str3="hello tarena";
    str4="hello tarena";
    strcpy(str3,"hello tarena");
    //str2 的空间分配在栈段。
    printf("pid:%d\n",getpid());
    printf("str=%p\n",str);
    printf("&str=%p\n",&str);
    printf("str1=%p\n",str1);
    printf("&str1=%p\n",&str1);
    printf("str2=%p\n",str2);
    printf("str2[]=%s \n",str2);
    for(i=0;i<5;i++){
        count();
    }
    printf("&flag %p\n",&flag);
    getchar();
    return 0;
}
