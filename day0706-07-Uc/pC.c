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
    //打开文件，以只读方式
    fd=open(argv[1],O_RDWR);
    if(fd==-1){
        perror("open");
        return -1;
    }
    //初始化lock
    lock.l_type=F_WRLCK;
    lock.l_whence=SEEK_END;
    lock.l_start=0;
    lock.l_len=-6;
    //对打开的文件测试写锁
    int f=fcntl(fd,F_GETLK,&lock);
    if(f==-1){
        perror("fcntl");
        return -1;
    }
    printf("lock test...\n");
    if(lock.l_type==F_UNLCK)printf("能加锁\n");
    if(lock.l_type==F_WRLCK)printf("不能加锁：\
        被pid:%d F_WRLCK锁住\n",lock.l_pid);
    if(lock.l_type==F_RDLCK)printf("不能加锁：\
        被pid:%d F_RDLCK锁住\n",lock.l_pid);
    //printf("hold pid:%d\n",lock.l_pid);
    getchar();
    close(fd);
    return 0;
}
