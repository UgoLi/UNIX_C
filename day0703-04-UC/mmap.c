/*************************************************************************
	> File Name: mmap.c
	> Author: 
	> Mail: 
	> Created Time: 2017年07月06日 星期四 13时31分58秒
 ************************************************************************/

#include<stdio.h>
#include<sys/mman.h>
#include<string.h>
int main(void){
    int prot=/*PROT_READ|*/PROT_WRITE;
    int flags=MAP_PRIVATE|MAP_ANONYMOUS;
    //创建映射区
    void *p=mmap(NULL,1,prot,flags,-1,0);
    if(p==MAP_FAILED){
        perror("mmap");
        return -1;
    }
    printf("maping success..\n");
    strcpy(p,"hello");
    printf("p=%p\n",p);
    printf("%s\n",(char *)p);
    //解除映射
    getchar();
    munmap(p,1);
    return 0;
}
