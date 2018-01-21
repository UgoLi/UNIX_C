/*************************************************************************
	> File Name: ftok.c
	> Author:UgoLi 
	> Mail: 2653920896@qq.com
	> Created Time: 2017年07月18日 星期二 00时17分28秒
 ************************************************************************/

#include<stdio.h>
#include<sys/types.h>
#include<sys/ipc.h>
#include<sys/msg.h>
int main(){
    key_t key;//用来存储键值
    //获取一个键值
    key=ftok(".",21);
    if(key==-1){
        perror("ftok");
        return -1;
    }
    printf("key=0x%x\n",key);
    //从系统中获取消息队列的id。如果消息队列不存在，创建这个消息队列，如果存在，
    //获取这个消息队列的id
    int msqid=msgget(key,IPC_CREAT|0664);
    if(msqid==-1){
        perror("magget");
        return -1;
    }
    printf("msqid=%d\n",msqid);
    return 0;
}



