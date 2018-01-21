/*************************************************************************
	> File Name: malloc.c
	> Author: 
	> Mail: 
	> Created Time: 2017年07月06日 星期四 17时01分36秒
 ************************************************************************/

#include<stdio.h>
#include<sys/types.h>
#include<unistd.h>
#include<stdlib.h>
int c=0;
const int f=0;
int main(){
    int a=0;
    static int b=0;
    static int d;
    const int e=0;
    char *str="code segmaent";
    int *p=(int *)malloc(sizeof(int));
    int *p1=(int *)malloc(sizeof(int));
    char *q=(char *)malloc(4096);
    char *q1=(char *)malloc(31*4096);
    char *q2=(char *)malloc(4096);
    

    printf("a=0:%p\n",&a);//内部局部变量--> 栈
    printf("static b=0:%p\n",&b);//静态局部初始化的变量--> 数据段
    printf("all c=0:%p\n",&c);//全局初始化的变量-->数据段
    printf("static d:%p\n",&d);//静态局部未初始化的变量-->数据段(BSS)
    printf("const e=0:%p\n",&e);//只读局部常量-->栈
    printf("const f=0:%p\n",&f);//只读全局常量-->代码段
    printf("str=%p\n",str);//字符串-->代码段
    printf("&str=%p\n",&str);//局部指针变量-->栈
    printf("p=%p\n",p);//以下动态分配内存-->堆段
    printf("pid:%d\n",getpid());
    printf("p=%p\n",p);
    printf("p1=%p\n",p1);
    printf("q=%p\n",q);
    printf("q1=%p\n",q1);
    printf("q2=%p\n",q2);
    getchar();
    printf("free...\n");
    free(q2);
    getchar();

    return 0;
}
