/*************************************************************************
	> File Name: msg.h
	> Author:UgoLi 
	> Mail: 2653920896@qq.com
	> Created Time: 2017年07月18日 星期二 03时55分33秒
 ************************************************************************/
#ifndef _MSG_H
#define _MSG_H
/*负责想消息队列发送消息*/
#include<stdio.h>
#include<string.h>
#include<sys/types.h>
#include<sys/ipc.h>
#include<sys/msg.h>
typedef struct msgbuf{
    long mtype;
    char mtext[128];
}msg_t;
#endif //_MSG_H
