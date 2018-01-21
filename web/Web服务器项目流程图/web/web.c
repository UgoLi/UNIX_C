#include "web.h"

int t_listen(int port,int backlog){
    int s_fd;
    SA_I ser;

    //创建socket,IPV4  基于TCP
    s_fd=socket(AF_INET,SOCK_STREAM,0);
    if(s_fd==-1){
        perror("socket");
        return -1;
    }
    //初始化服务器的ip地址和端口号
    ser.sin_family=AF_INET;//指定IPV4家族
    //指定端口号，网络字节序
    ser.sin_port=htons(port);
    //指定服务器的ip地址。
    //INADDR_ANY代表本机上的所有ip地址，长整型的
    ser.sin_addr.s_addr=htonl(INADDR_ANY);

    //将服务器的ip地址和端口绑定到s_fd
    int b=bind(s_fd,(SA *)&ser,sizeof(SA_I));
    if(b==-1){
        perror("bind");
        return -1;
    }
    //监听socket
    listen(s_fd,backlog);
    return s_fd;
}

void doit(int c_fd){
    char buf[1024];
    int r=read(c_fd,buf,1024);
    write(1,buf,r);
    printf("\n");
    return;
}
