/*************************************************************************
	> File Name: map_file.c
	> Author: 
	> Mail: 
	> Created Time: 2017年07月07日 星期五 11时44分54秒
 ************************************************************************/

#include<stdio.h>
#include<sys/mman.h>
#include<stdio.h>
#include<sys/stat.h>
#include<sys/types.h>
#include<fcntl.h>
#include<unistd.h>
#include<stdlib.h>
#include<sys/mman.h>

int main(void){
    int fd;
    //打开文件hello
    fd=open("hello",O_RDWR);
    if(fd==-1){
        perror("open");
        return -1;
    }
    int flags=MAP_SHARED;
    int prot=PROT_READ|PROT_WRITE;
    //将文件映射到进程的虚拟空间
    void *p=mmap(NULL,1,prot,flags,fd,0);
    if(p==MAP_FAILED){
        perror("mmap");
        return -1;
    }
    int *q=p;
    q[0]=0x31323334;
    close(fd);
    //解除文件映射
    munmap(p,6);
    return 1;
}
