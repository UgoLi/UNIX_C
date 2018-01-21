/*************************************************************************
	> File Name: c_fifo.c
	> Author:UgoLi 
	> Mail: 2653920896@qq.com
	> Created Time: 2017年07月13日 星期四 10时13分51秒
 ************************************************************************/

#include<stdio.h>
#include<sys/types.h>
#include<sys/stat.h>
int main(int argc,char *argv[]){
    //创建管道文件
    int f= mkfifo(argv[1],0664);
    if(f==-1){
        perror("mkfifo");
        return -1;
    }
    printf("mkfifo success...\n");
    return 0;
}
