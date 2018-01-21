/*************************************************************************
	> File Name: msgA.c
	> Author:UgoLi 
	> Mail: 2653920896@qq.com
	> Created Time: 2017年07月18日 星期二 03时55分33秒
 ************************************************************************/

/*负责想消息队列发送消息*/
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
    //初始化消息
    msgp.mtype=3;
    char *msg="this is a test\n";
    strcpy(msgp.mtext,msg);
    int msg_len=strlen(msg);
    //想消息队列发送消息
    //printf("msqid=%d,magp=%p,msg_len=%d\n",msqid,&msgp,msg_len);
    int snd=msgsnd(msqid,&msgp,msg_len,0);
    if (snd==-1){
        perror("msgsnd");
        return -1;
    }
    printf("msg send success...\n");
    return 0;
}
