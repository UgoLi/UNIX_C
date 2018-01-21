#ifndef WEB_H_
#define WEB_H_
#include<t_net.h>
//定义结构体存储请求头信息
typedef struct{
    char method[16];
    char path[128];
    char protocol[32];
}req_t;
typedef struct{
    char proto[32];
    int code;
    char f_type[32];
}response_t;

int t_listen(int port,int backlog);
void doit(int c_fd);
#endif
