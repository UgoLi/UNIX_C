/*************************************************************************
	> File Name: uclie.c
	> Author:UgoLi 
	> Mail: 2653920896@qq.com
	> Created Time: 2017年07月20日 星期四 14时21分33秒
 ************************************************************************/

#include<stdio.h>
#include<t_net.h>
#include<stdlib.h>
#include<string.h>
int main(int argc,char *argv[]){
    SA_I serv;
    char buf[128];
    char msg[128];
    //1、创建socket文件描述符s_fd,基于UDP
    int s_fd=socket(AF_INET,SOCK_DGRAM,0);
    if(s_fd==-1){
        perror("socket");
        return -1;
    }
    //2、向服务器发送信息
    //初始化服务器信息
    serv.sin_family=AF_INET;
    serv.sin_port=htons(6666);
    inet_pton(AF_INET,"127.0.0.1",&serv.sin_addr);
    while(1){
        gets(msg);
        strcat(msg,"\n");
        if(!strcmp(msg,"break\n")||!strcmp(msg,"BREAK\n"))
            break;
        sendto(s_fd,msg,strlen(msg),0,(SA *)&serv,sizeof(serv));
        //3、等待服务器的响应信息，接受信息
        int recv=recvfrom(s_fd,buf,128,0,NULL,NULL);
        printf("接受信息长度：%d\n",recv);
        if(recv>0){//接收到信息
            //将从服务器接收到的信息输出到显示器
            write(STDOUT_FILENO,buf,recv);
        }
    }
    //关闭网络
    close(s_fd);
    return 0;
}
