/*************************************************************************
	> File Name: mmap_read.c
	> Author:UgoLi 
	> Mail: 2653920896@qq.com
	> Created Time: 2017年07月26日 星期三 19时46分33秒
 ************************************************************************/

#include<stdio.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<fcntl.h>
#include<unistd.h>
#include<string.h>
#include<sys/mman.h>
int mmap_read(void){
    int fd=open("../hello",O_CREAT|O_RDWR,0774);
    if(fd==-1){
        perror("c15:open");
        return -1;
    }
    void *p=mmap(NULL,1,PROT_READ|PROT_WRITE,MAP_SHARED,fd,0);
    if(p==MAP_FAILED){
        perror("c20:mmap");
        return -1;
    }
    printf("%s\n",(char *)p);
    int myc=msync(p,1024,MS_ASYNC);
    if(myc==-1){
        perror("msync");
        return -1;
    }
    munmap(p,1);
    close(fd);
    return 1;
}








