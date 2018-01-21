/*************************************************************************
	> File Name: va_list_open.c
	> Author:UgoLi 
	> Mail: 2653920896@qq.com
	> Created Time: 2017年08月07日 星期一 09时53分36秒
 ************************************************************************/

#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdarg.h>
#include <unistd.h>

int my_open(char *pathname,int flags,...){
    va_list vl;
    int mode_t=0;

    va_start(vl,flags);    
    /*O_CREAT|O_RDONLY(O_WRONLY)|O_RDWR|O_APPEND 的解析和相应操作
     *参考：ftruncate(2)/truncate(2) 清空文件内容
     *      fcntl(2) 设置文件描述符的状态，用标志  F_SETFD
     *      readlinkat()  获取文件描述符所指向文件的路径 
     **/
    
    if(access(pathname,F_OK))
        if((O_CREAT&flags)==O_CREAT){
            mode_t=va_arg(vl,int);
            creat(pathname,mode_t);
            printf("mode_t=0%o\n",mode_t);
        }
        else{
            printf("no O_CREAT\n");
        }
    va_end(vl);
    return 0;
}
int main(){
    my_open("./test.c",O_CREAT,0664);
    /*printf("O_CREAT=0%o,pid()=%d\n",O_CREAT,getpid());
    printf("O_EXCL=0%o\n",O_EXCL);    
    printf("O_TRUNC=0%o\n",O_TRUNC);    
    printf("O_RDONLY=0%o\n",O_RDONLY);    
    printf("O_WRONLY=0%o\n",O_WRONLY);    
    printf("O_RDWR=0%o\n",O_RDWR);    
    */    
    getchar();
    return 0;
}
