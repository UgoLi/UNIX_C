/*************************************************************************
	> File Name: server.c
	> Author:UgoLi 
	> Mail: 2653920896@qq.com
	> Created Time: 2017年07月19日 星期三 10时22分41秒
 ************************************************************************/

#include<stdio.h>
#include"web.h"
#include<stdlib.h>
#include<sys/wait.h>
#include<time.h>
int main(void){
    /******************        定义变量             ******************/
    pid_t s_fd/*socket套接描述符*/,conn_fd/*链接描述符*/;
    SA_I cli;//客户端地址结构
    socklen_t addrlen=16; //客户端地址长度
    pid_t pid;//创建子进程
    int fd_out;//标准输出重定向前记录
    int serv_fd;//服务器信息记录文件
    char ip[128];//解析ip存放地址
    time_t now;//当前时间

    get_http_conf();//获取http配置
    dprintf(1,"启动 listen port:%d\n",config.port);
    s_fd=t_listen(config.port,5);//监听端口
    if(s_fd==-1){
        perror("t_listen");
        return -1;
    }

    while(1){
        serv_fd=open("server_log.txt",O_CREAT|O_RDWR|O_APPEND,0774);
        if(serv_fd==-1){
            perror("open");
            return -1;
        }
        fd_out=dup(1);
        if(dup2(serv_fd,1)==-1){
            perror("dup2");
            return -1;
        }
        
        /*5、取出一个连接,如果没有未决连接，阻塞等待*/
        conn_fd=accept(s_fd,(SA *)&cli,&addrlen);
        if(conn_fd==-1){
            perror("accept");
            return -1;
        }//握手成功
        
        
        //记录访问地址及时间
        inet_ntop(AF_INET,&cli.sin_addr,ip,128);//从结构体获取ip
        now=time(NULL);
        dprintf(1,"\n时间: %s IP: %s\n",ctime(&now),ip);
        
        
        //负责和客户端端的通讯，业务的处理
        doit(conn_fd);
        sleep(4);
        close(conn_fd);
        close(serv_fd);
        dup2(fd_out,1);
    }
    return 0;
}
