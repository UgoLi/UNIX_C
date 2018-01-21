/*************************************************************************
	> File Name: r_file.c
	> Author: 
	> Mail: 
	> Created Time: 2017年07月06日 星期四 20时46分46秒
 ************************************************************************/

#include<stdio.h>
#include<sys/stat.h>
#include<fcntl.h>
#include<unistd.h>
int main(int argc,char *argv[]){
    //以只读方式打开
    int fd;
    fd=open(argv[1],O_RDONLY);
    if(fd==-1){
        perror("open");
        return -1;
    }
    printf("open success...\n");
    close(fd);
    //关闭文件描述符
    return 0;
}
