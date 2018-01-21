/*************************************************************************
	> File Name: pB.c
	> Author: 
	> Mail: 
	> Created Time: 2017年07月08日 星期六 14时27分28秒
 ************************************************************************/

#include<stdio.h>
#include<stdio.h>
#include<unistd.h>
#include<fcntl.h>
#include<sys/types.h>
#include<sys/stat.h>
int main(int argc,char *argv[]){
    int fd;
    struct flock lock;
    //打开文件，以读写方式
    fd=open(argv[1],O_RDWR);
    if(fd==-1){
        perror("open");
        return -1;
    }
    //初始化lock的值
    lock.l_type=F_WRLCK;
    lock.l_whence=SEEK_END;
    lock.l_start=0;
    lock.l_len=-6;
    //对打开的文件加读锁
    int f=fcntl(fd,F_SETLKW,&lock);
    if(f==-1){
        perror("fcntl");
        return -1;
    }
    printf("fcntl success...\n");
    getchar();
    close(fd);
    return 0;
}
