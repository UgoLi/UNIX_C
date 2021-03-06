/*************************************************************************
	> File Name: sems.c
	> Author:UgoLi 
	> Mail: 2653920896@qq.com
	> Created Time: 2017年07月22日 星期六 11时16分57秒
 ************************************************************************/

#include<stdio.h>
#include<unistd.h>
#include<sys/types.h>
#include<sys/ipc.h>
#include<sys/sem.h>


int main(void){
    key_t key;
    //获取键值
    key=ftok(".",51);
    if(key==-1){
        perror("ftok");
        return -1;
    }
    //使用键值获取一个信号量集id
    int semid=semget(key,1,IPC_CREAT|0664);
    if(semid==-1){
        perror("semget");
        return -1;
    }
    printf("semid=%d\n",semid);
    //获取信号量集中的第一个信号量的semval值
    while(1){
        int sc=semctl(semid,1,GETVAL);
            if(sc==-1){
                perror("semctl");
                return -1;
        }
        printf("get val success...%d\n",sc);
        sleep(1);
    }
    return 0;
}

