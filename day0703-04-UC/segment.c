/*************************************************************************
	> File Name: segment.c
	> Author: 
	> Mail: 
	> Created Time: 2017年07月05日 星期三 19时42分37秒
 ************************************************************************/

#include<stdio.h>
int main(void){
    int var_i=321;
    int *q=NULL;     //野指针，悬空指针
    //*q=45;
    int *p=(int *)0x30000000; //操作系统上运行，则未映射物理内存
    //在裸板开发上就是物理地址
    printf("q=%p,*q=%d\n",q);
    printf("p=%p\n",p);
    *p=45;                                                                                      
    printf("*p=%d\n",*p);
    return 0;
}
