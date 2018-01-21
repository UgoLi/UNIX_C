/*************************************************************************
	> File Name: server.c
	> Author:UgoLi 
	> Mail: 2653920896@qq.com
	> Created Time: 2017年07月19日 星期三 18时19分51秒
 ************************************************************************/

#include<stdio.h>
#include"t_net.h"
int main(void){
    //1、创建socket通讯端点,基于连接
    int s_fd=socket(AF_INET,SOCK_STREAM,0);
    if(s_fd==-1){
        perror("socket");
        return -1;
    }
    //2、bind，将socket端点与服务器ip和端口绑定
    SA_I ser;//为服务器声明一个ipv4地址结构体，并初始化
    ser.sin_family=AF_INET;
    ser.sin_port=htons(7778);
    ser.sin_addr.s_addr=htonl(INADDR_ANY);    
    int b=bind(s_fd,(SA *)&ser,sizeof(SA_I));
    if(b==-1){
        perror("bind");
        return -1;
    }
    //3、listen，监听socket信号，并设置队列信号数
    listen(s_fd,5);
    SA_I cli;//为访问的客户声明一个ipv4的地址结构体，用来存放其地址
    while(1){
        //4、accept，一个未决socket并返回一个连接描述符，没有未决信号，即阻塞
        int cli_len;
        int conn_fd=accept(s_fd,(SA*)&cli,&cli_len);
        if(conn_fd==-1){
            perror("accept");
            return -1;
        }
        char IP[128];
        printf("最近一次来访地址：%s\n",inet_ntop(AF_INET,&cli.sin_addr,IP,128));
        printf("访问端口号:%d\n",ntohs(cli.sin_port));
        //5、读取连接内的数据,并处理
        char buf[128];
        int r=read(conn_fd,buf,128);
        for(int i=0;i<r;i++){
            buf[i]=toupper(buf[i]);
        }    
        //7、响应客户端
        write(conn_fd,buf,r);
        //8、关闭连接
        close(conn_fd);
    }
    return 0;
}

