/*************************************************************************
	> File Name: segment.c
	> Author:UgoLi 
	> Mail: 2653920896@qq.com
	> Created Time: 2017年07月18日 星期二 08时50分46秒
 ************************************************************************/

#include<stdio.h>
#include<sys/ipc.h>
#include<sys/shm.h>
#include<sys/types.h>
int main(void){
    key_t key;
    //获取键值
    key=ftok(".",41);
    if(key==-1){
        perror("ftok");
        return -1;
    }
    printf("key:0x%x\n",key);
    //使用键值获取共享内存的id
    int shmid=shmget(key,1024,IPC_CREAT|0644);
    if(shmid==-1){
        perror("shmget");
        return -1;
    }
    printf("shmid=%d\n",shmid);
    return 0;
}
