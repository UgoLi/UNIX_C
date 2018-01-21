/*************************************************************************
	> File Name: client.c
	> Author:UgoLi 
	> Mail: 2653920896@qq.com
	> Created Time: 2017年07月19日 星期三 13时57分38秒
 ************************************************************************/

#include<stdio.h>
#include<t_net.h>
#include<string.h>
int main(int argc,char *argv[]){
    int s_fd;
    SA_I serv;
    char *msg="this is a test\n";
    char buf[128];
    //1、创建socket
    s_fd=socket(AF_INET,SOCK_STREAM,0);
    if(s_fd==-1){
        perror("socket");
        return -1;
    }
    //初始化服务器信息
    serv.sin_family=AF_INET;
    serv.sin_port=htons(7777);
    //用户知道的是服务器字符串类型的ip地址。需要转换为binary格式
    //127.0.0.1   代表本机ip
    inet_pton(AF_INET,argv[1],&serv.sin_addr);
    //2、建立s_fd与服务器的连接
    int c=connect(s_fd,(SA*)&serv,sizeof(SA_I));
    if(c==-1){
        perror("connect");
        return -1;
    }
    //3、向服务器发送信息
    write(s_fd,msg,strlen(msg));
    //4、获取服务器端的响应信息
    int r=read(s_fd,buf,128);
    //5、处理响应信息
    write(1,buf,r);
    //6、关闭连接
    close(s_fd);
    return 0;
}
