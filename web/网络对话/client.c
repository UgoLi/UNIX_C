/*************************************************************************
	> File Name: client.c
	> Author:UgoLi 
	> Mail: 2653920896@qq.com
	> Created Time: 2017年07月19日 星期三 13时57分38秒
 ************************************************************************/

#include<stdio.h>
#include<stdlib.h>
#include<t_net.h>
#include<string.h>
#include<sys/types.h>
#include<sys/wait.h>

int main(int argc,char *argv[]){
    int s_fd;
    SA_I serv;
    char buf_r[128];
    char buf_w[128];
    //1、创建socket
    s_fd=socket(AF_INET,SOCK_STREAM,0);
    if(s_fd==-1){
        perror("socket");
        return -1;
    }
    //初始化服务器信息
    serv.sin_family=AF_INET;
    serv.sin_port=htons(atoi(argv[1]));
    //用户知道的是服务器字符串类型的ip地址。需要转换为binary格式
    //127.0.0.1   代表本机ip
    inet_pton(AF_INET,argv[2],&serv.sin_addr);
    //2、建立s_fd与服务器的连接
    int c=0,i=0;
    while(1){
        printf("第 %d 次 尝试连接\n",i++);
        c=connect(s_fd,(SA*)&serv,sizeof(SA_I));
        if(c==-1){
            perror("connect");
            sleep(2);
        }else break;
        if(i>=10){
            printf("连接超时，请稍后重试！！\n");
            exit(-1);
        }
    }
    printf("连接成功....\n");
    fflush(stdin);
    //3、向服务器发送信息
    pid_t pid_w=fork();
    switch(pid_w){
        case -1:
            perror("fork");
            return -1;
        case 0://write
            while(1){
                printf("\rme:");
                fflush(stdout);
                fflush(stdin);
                fgets(buf_w,128,stdin);
                write(s_fd,buf_w,strlen(buf_w));
            }
        default:
            break;
    }
    pid_t pid_r=fork();
    switch(pid_r){
        case -1:
            perror("fork");
            return -1;
        case 0://read
            while(1){
                bzero(buf_r,128);
                if(read(s_fd,buf_r,128)<=0)break;
                printf("\rs_fd %d:",s_fd);
                fflush(stdout);
                write(1,buf_r,strlen(buf_r));
                printf("\rme:");fflush(stdout);
            }
        default:
            break;
    }
    //6、关闭连接
    while(1)if(wait(NULL)==-1)break; 
    close(s_fd);
    return 0;
}
