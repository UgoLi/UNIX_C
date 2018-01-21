/*************************************************************************
	> File Name: web.h
	> Author:UgoLi 
	> Mail: 2653920896@qq.com
	> Created Time: 2017年07月27日 星期四 09时13分58秒
 ************************************************************************/

#ifndef _WEB_H
#define _WEB_H
#include<sys/types.h>
#include<stdlib.h>
#include<sys/wait.h>
#include<string.h>
#include<stdio.h>
#include<fcntl.h>
#include<strings.h>
#include<unistd.h>
#include<time.h>
#include<errno.h>
#include"t_net.h"
#include"printf_color.h"
typedef struct {
    char method[12];//请求的方法的名字
    char path[128];//请求的文件路径
    char protocol[16];//协议及其版本
}request_t;

typedef struct {
    char protocol[16];//协议及其版本
    short code;//状态码
    char f_type[16];//回响文件类型
}response_t;

typedef struct{
    short port;//端口号
    char workdir[128];//应求文件路径
}http_conf;
extern http_conf config;

int get_http_conf(void);
int t_listen(int port,int backlog);
int doit(int conn_fd);
void handler(int );


#endif
