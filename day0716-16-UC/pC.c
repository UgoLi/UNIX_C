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

//根据手册用户定义联合体
typedef union semun{
    int val;
}semun_t;

int main(void){
    key_t key;
    semun_t arg;
    struct sembuf semb={0,-1,0};
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
    //设置信号量集中的第一个信号量的semval值为5.
    arg.val=5;
    int sc=semctl(semid,0,SETVAL,arg.val);
    if(sc==-1){
        perror("semctl");
        return -1;
    }
    printf("set val success...\n");
    while(1){
        //将第一个信号量的semval值减1
        int sop=semop(semid,&semb,1);
        if(sop==-1){
            perror("semop");
            return -1;
        }
        printf("pA.c   occured..........\n");
        sleep(3);
    }
    
    
    return 0;
}

