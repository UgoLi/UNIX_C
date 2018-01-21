/*************************************************************************
	> File Name: Endian_union.c
	> Author:UgoLi 
	> Mail: 2653920896@qq.com
	> Created Time: 2017年07月25日 星期二 10时00分08秒
 ************************************************************************/

#include<stdio.h>
typedef union{
    unsigned int a;
    char ch;
}union_Endian;
int main(void){
    union_Endian a;
    a.a=0x0001;
    if(a.ch){
        printf("a.ch=%d,小端\n",a.ch);
    }
    else{
        printf("a.ch=%d,大端\n",a.ch);
    }
}

