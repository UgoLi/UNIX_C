/*************************************************************************
	> File Name: pB.c
	> Author:UgoLi 
	> Mail: 2653920896@qq.com
	> Created Time: 2017年07月13日 星期四 14时00分48秒
 ************************************************************************/

#include<stdio.h>
#include<sys/stat.h>
#include<sys/types.h>
#include<fcntl.h>
#include<unistd.h>
int main(int argc,char *argv[]){
    int fd;
    char buf[1024];
    fd=open(argv[1],O_RDONLY);
    if(fd==-1){
        perror("open");
        return -1;
    }
    //从管道文件读取数据到buf中
    int r=read(fd,buf,1024);
    write(1,buf,r);
    close(fd);
    return 0;
}
