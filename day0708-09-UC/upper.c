/*************************************************************************
	> File Name: upper.c
	> Author:UgoLi 
	> Mail: 2653920896@qq.com
	> Created Time: 2017年07月13日 星期四 14时17分26秒
 ************************************************************************/
/*将从键盘输入的内容转换为大写*/
#include<stdio.h>
#include<ctype.h>
int main(void){
    int ch;
    while((ch=getchar())!=EOF){
        putchar(toupper(ch));
    }
    return 0;
}
