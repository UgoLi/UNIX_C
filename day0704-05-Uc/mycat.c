/*************************************************************************
	> File Name: mycat.c
	> Author: 
	> Mail: 
	> Created Time: 2017年07月07日 星期五 10时46分59秒
 ************************************************************************/

#include<stdio.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<unistd.h>
#include<fcntl.h>
int main(int argc,char *argv[]){
    int fd;
    char buff[128];
    int r,i=-2;
    //以只读方式打开文件
    fd=open(argv[1],O_RDONLY);
    if(fd==-1){
        perror("open");
        return -1;
    }

    while(lseek(fd,i--,SEEK_END)){
        r=read(fd,buff,1);
        write(STDOUT_FILENO,buff,r);
    }
    //关闭文件描述符
    close(fd);
    return 0;
}
