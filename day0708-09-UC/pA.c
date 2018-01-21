/*************************************************************************
	> File Name: pA.c
	> Author:UgoLi 
	> Mail: 2653920896@qq.com
	> Created Time: 2017年07月13日 星期四 10时25分45秒
 ************************************************************************/

#include<stdio.h>
#include<sys/stat.h>
#include<sys/types.h>
#include<fcntl.h>
#include<unistd.h>
#include<string.h>
int main(int argc,char *argv[]){
    int fd;
    char *msg="This is a test...\n";
    //打开文件，以写的方式打开
    fd=open(argv[1],O_RDWR|O_APPEND);
    if(fd==-1){
        perror("open");
        return -1;
    }
    //向管道文件写数据
    write(fd,msg,strlen(msg));
    close(fd);
    return 0;
}
