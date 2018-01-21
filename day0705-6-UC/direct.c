/*************************************************************************
	> File Name: direct.c
	> Author: 
	> Mail: 
	> Created Time: 2017年07月08日 星期六 11时26分00秒
 ************************************************************************/

#include<stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
int main(int argc ,char *argv[]){
    int fd,s_fd;
    char msg[]="this is s test\n";
    //以写的方式打开文件
    fd=open(argv[1],O_RDWR|O_CREAT|O_TRUNC,0664);
    if(fd==-1){
        perror("open");
        return -1;
    }
    //保存标准输出的文件描述符
    s_fd=dup(STDOUT_FILENO);
    //将fd的值拷贝到标准输出中
    dup2(fd,STDOUT_FILENO);
    close(fd);
    //通过标准输出将内容输出到文件中
    write(1,msg,strlen(msg));
    //恢复原来的描述符
    dup2(s_fd,STDOUT_FILENO);
    close(s_fd);
    //将消息输出到显示器
    write(1,msg,strlen(msg));
    return 0;
}
