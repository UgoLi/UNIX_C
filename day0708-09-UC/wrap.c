/*************************************************************************
	> File Name: wrap.c
	> Author:UgoLi 
	> Mail: 2653920896@qq.com
	> Created Time: 2017年07月13日 星期四 14时29分55秒
 ************************************************************************/
/*对upper.c的封装*/
#include<stdio.h>
#include<sys/stat.h>
#include<sys/types.h>
#include<fcntl.h>
#include<unistd.h>
int main(int argc,char *argv[]){
    //以只读方式打开文件
    int fd=open(argv[1],O_RDONLY);
    if(fd==-1){
        perror("open");
        return -1;
    }
    //将文件重定向到标准输入
    dup2(fd,STDIN_FILENO);
    close(fd);
    execlp("./upper","upper",NULL);
    return 0;
}
