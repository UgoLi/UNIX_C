/*************************************************************************
	> File Name: w_file.c
	> Author: 
	> Mail: 
	> Created Time: 2017年07月07日 星期五 09时26分21秒
 ************************************************************************/

#include<stdio.h>
#include<t_file.h>
int main(int argc,char *argv[]){
    int fd;
    int flags=O_RDWR|O_CREAT|O_EXCL;
    //以写的方式打开文件
    fd=open(argv[1],flags,0666);
    if(fd==-1){
        perror("open");
        return -1;
    }
    printf("open file success..\n");

    close(fd);
    return 0;
}
