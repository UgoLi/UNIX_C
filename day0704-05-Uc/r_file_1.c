/*************************************************************************
	> File Name: r_file_1.c
	> Author:UgoLi 
	> Mail: 2653920896@qq.com
	> Created Time: 2017年07月26日 星期三 11时16分34秒
 ************************************************************************/

#include<stdio.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<fcntl.h>
#include<unistd.h>
int main(int argc,char **argv){
    int fd=open("hello",O_RDONLY);
    if(fd==-1){
        do{    
            perror("open");
            return -1;
        }while(0);
    }
    printf("open %s successd...\n",*(argv+1));
    close(fd);
    return 0;
}
