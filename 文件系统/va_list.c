/*************************************************************************
	> File Name: va_list.c
	> Author:UgoLi 
	> Mail: 2653920896@qq.com
	> Created Time: 2017年07月28日 星期五 14时09分43秒
 ************************************************************************/

#include<stdio.h>
#include <stdarg.h>
#include<unistd.h>
#include<string.h>
void my_printf(char *fmt, ...)
{
    va_list ap;
    int d;
    char c, *s;
    va_start(ap, fmt);
    while (*fmt){
        if(*fmt=='%'){
            fmt++;
            switch (*fmt) {
                case 's':              /* string */
                s = va_arg(ap, char *);
                write(1,s,strlen(s));
                break;
                case 'd':              /* int */
                d = va_arg(ap, int);
                char buf[10];
                sprintf(buf,"%d",d);
                write(1,buf,strlen(buf));
                break;    
                case 'c':              /* char */
                /* need a cast here since va_arg only
                * takes fully promoted types */
                c = (char) va_arg(ap, int);
                write(1,&c,1);
                break;
            } 
        }
        else
        write(1,fmt,1);
        fmt++;
    }
    va_end(ap);
}

int main(void){ 
    my_printf("test  %s aaa %d aaaa %c\n","test_result",12323,'c');
    return 0;
}












