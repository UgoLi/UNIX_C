/*************************************************************************
	> File Name: server.c
	> Author:UgoLi 
	> Mail: 2653920896@qq.com
	> Created Time: 2017年07月19日 星期三 10时22分41秒
 ************************************************************************/

#include<stdio.h>
#include<t_net.h>
#include<stdlib.h>
#include<sys/wait.h>
//获取客户端的数据、处理数据、响应给客户端
void doit(int c_fd){
    int i;
    char buf[128];
    //6、从客户端读取数据
    int r=read(c_fd,buf,128);
    //对获取的数据进行处理--转换为大写
    for(i=0;i<r;i++)
        buf[i]=toupper(buf[i]);
    //7、处理完响应给客户端
    write(c_fd,buf,r);
    sleep(30);
    //while(1);
    //8、关闭客户端的连接
    close(c_fd);
    return;
}

int main(void){
    int s_fd/*socket返回描述符*/,conn_fd/*accept*/;
    SA_I ser,cli;
    char IP[128];
    pid_t pid;
    //1、创建socket,AF_INET->IPV4协议家族,基于连接的SOCK_STREAM
    s_fd=socket(AF_INET,SOCK_STREAM,0);
    if(s_fd==-1){
        perror("socket");
        return -1;
    }
    //初始化服务器的ip地址和端口号
    ser.sin_family=AF_INET;//指定IPV4家族
    ser.sin_port=htons(7777);     //指定端口号，并转成网络字节序
    //指定服务器的ip地址。
    //INADDR_ANY代表本机上的所有ip地址，长整型的
    ser.sin_addr.s_addr=htonl(INADDR_ANY);
    
    //2、将socket通讯端点s_fd与服务器ip地址和端口好绑定
    int b=bind(s_fd,(SA *)&ser,sizeof(SA_I));
    if(b==-1){
        perror("bind");
        return -1;
    }
    //3、监听socket
    listen(s_fd,5);
    //4、从未决连接队列中取出一个连接处理
    while(1){
        int cli_len=sizeof(cli);
        //5、取出一个连接,如果没有未决连接，阻塞等待
        conn_fd=accept(s_fd,(SA*)&cli,&cli_len);
        if(conn_fd==-1){
            perror("accept");
            return -1;
        }
        //需要将二进制转换成字符串格式
        printf("%s\n",inet_ntop(AF_INET,&cli.sin_addr,IP,128));
        //握手成功
        pid=fork();//创建子进程
        if(pid==-1){
            perror("fork");
            return -1;
        }
        if(pid==0){//child
            //close(s_fd);
            doit(conn_fd);
            exit(EXIT_SUCCESS);
        }
        else{//parent
            close(conn_fd);    
            waitpid(-1,NULL,WNOHANG);
        }
    }
    return 0;
}
