/*************************************************************************
	> File Name: msgA.c
	> Author:UgoLi 
	> Mail: 2653920896@qq.com
	> Created Time: 2017年07月18日 星期二 03时55分33秒
 ************************************************************************/

/*从消息队列获取消息*/
#include"msg.h"
int main(void){
    key_t key;
    msg_t msgp;
    //获取键值
    key=ftok(".",21);
    if(key==-1){
        perror("ftok");
        return -1;
    }
    //使用键值获取消息队列的id
    int msqid=msgget(key,IPC_CREAT|0644);
    if(msqid==-1){
        perror("msgget");
        return -1;
    }
    //从消息队列获取消息
    int rcv=msgrcv(msqid,&msgp,120,3,0);
    if (rcv==-1){
        perror("msgsnd");
        return -1;
    }
    printf("msg get success...\n");
    printf("%s",msgp.mtext);
    return 0;
}
