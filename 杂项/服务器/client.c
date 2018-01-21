/*************************************************************************
	> File Name: client.c
	> Author:UgoLi 
	> Mail: 2653920896@qq.com
	> Created Time: 2017年07月19日 星期三 19时21分12秒
 ************************************************************************/

#include<stdio.h>
#include<t_net.h>
#include<string.h>
int main(int argc,char *argv[]){
    //1、建立socket，基于连接TCP
    int s_fd=socket(AF_INET,SOCK_STREAM,0);
    if(s_fd==-1){
        perror("socket");
        return -1;
    }
    //2、connect，socket连接服务器
    SA_I serv;//声明一个服务器的ipv4的地址结构体，并赋值
    serv.sin_family=AF_INET;
    serv.sin_port=htons(7778);
    inet_pton(AF_INET,argv[1],&serv.sin_addr);
    int c=connect(s_fd,(SA *)&serv,sizeof(SA_I));
    if(c==-1){
        perror("connect");
        return -1;
    }
    //3、write向服务器发送数据
    char *msg="hello linux\n";
    write(s_fd,msg,strlen(msg));
    //4、read等待服务器响应。获取返回数据
    char buf[128];
    int r=read(s_fd,buf,128);
    //5、处理服务器返回的数据
    write(STDOUT_FILENO,buf,r);
    //6、关闭连接close
    close(s_fd);
    return 0;
}
