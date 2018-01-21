/*************************************************************************
	> File Name: mmap_write.c
	> Author:UgoLi 
	> Mail: 2653920896@qq.com
	> Created Time: 2017年07月26日 星期三 18时42分28秒
 ************************************************************************/

#include<stdio.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<fcntl.h>
#include<unistd.h>
#include<string.h>
#include<sys/mman.h>
int mmap_read(void);
typedef struct{
    char name[128];
    char id[24];
}people;
int main(){
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
    people pl={};
    strcpy(pl.name,"李卫国 \n");
    strcpy(pl.id,"341124199409120419\n");
    write(fd,"",strlen(pl.name)+strlen(pl.id));//write something-->分配物理内存
    close(fd);
    memcpy(p,pl.name,strlen(pl.name));
    memcpy(p+strlen(pl.name),pl.id,strlen(pl.id));
    int myc=msync(p,1024,MS_ASYNC);//手动将将映射区内容同步到文件
    if(myc==-1){
        perror("msync");
        return -1;
    }
    munmap(p,1);
    mmap_read();
    return 0;
}









