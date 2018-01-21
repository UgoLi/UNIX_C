/*************************************************************************
	> File Name: map_file_1.c
	> Author:UgoLi 
	> Mail: 2653920896@qq.com
	> Created Time: 2017年07月26日 星期三 13时35分06秒
 ************************************************************************/

#include<stdio.h>
#include<sys/stat.h>
#include<sys/types.h>
#include<fcntl.h>
#include<unistd.h>
#include<stdlib.h>
#include<sys/mman.h>
#include<string.h>
#include<assert.h>
int main(int argc,char *argv[]){
    //打开文件
    int fd=open(argv[1],O_RDWR);
    if(fd==-1){
        do{
            perror("open");
            return -1;
        }while(0);
    }
    void *p_mmap=mmap(NULL,1,PROT_READ|PROT_WRITE,MAP_SHARED,fd,0);
    
    if(p_mmap==MAP_FAILED){
        do{
            perror("mmap");
            return -1;
        }while(0);   
    }
    printf("mmap successd...\n");
    printf("p_mmap=%p\n",p_mmap);
    char *q=p_mmap;
    printf("sizeof(*q)=%ld\n",sizeof(*q));
    q[100]=0x31;
    printf("pid=%d\n",getpid());
    perror("");
        
    getchar();
    close(fd);
    munmap(p_mmap,6);
    return EXIT_FAILURE;
}

