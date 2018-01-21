/*************************************************************************
	> File Name: userv.c
	> Author:UgoLi 
	> Mail: 2653920896@qq.com
	> Created Time: 2017年07月20日 星期四 13时58分14秒
 ************************************************************************/

/*udp的服务器端*/
#include<stdio.h>
#include<t_net.h>

int main(void){
    SA_I serv,cli;
    int i,cli_len;
    char buf[128];
    char IP[128];
    //1、创建socket文件描述符.基于udp
    int s_fd=socket(AF_INET,SOCK_DGRAM,0);
    if(s_fd==-1){
        perror("socket");
        return -1;
    }
    //2、将s_fd绑定到服务器的ip地址和端口号
    //初始化服务器ip和端口号
    serv.sin_family=AF_INET;
    serv.sin_port=htons(6666);
    serv.sin_addr.s_addr=htonl(INADDR_ANY);
    int b=bind(s_fd,(SA *)&serv,sizeof(SA_I));
    if(b==-1){
        perror("binf");
        return -1;
    }
    cli_len=sizeof(cli);
    while(1){
        //3、阻塞等待客户端数据
        int recv=recvfrom(s_fd,buf,128,0,(SA *)&cli,&cli_len);
        printf("-->来访IP：%s\n",inet_ntop(AF_INET,&cli.sin_addr,IP,128));
        printf("接受客户端信息长度:%d\n",recv);
        printf("内容：\n");
        write(STDOUT_FILENO,buf,recv);
        if(recv>0){//接受到数据
            for(i=0;i<recv;i++){
                buf[i]=toupper(buf[i]);
            }
        }
        //4、发送消息给客户端
        sendto(s_fd,buf,recv,0,(SA *)&cli,sizeof(cli));
    }
    close(s_fd);
    return 0;
}













