/*************************************************************************
	> File Name: server.c
	> Author:UgoLi 
	> Mail: 2653920896@qq.com
	> Created Time: 2017年07月19日 星期三 10时22分41秒
 ************************************************************************/

#include"web.h"

int main(void){
    /******************        定义变量             ******************/
    pid_t s_fd=0/*socket套接描述符*/,conn_fd=0/*链接描述符*/,apt_fd=0/*连通描述符*/;
    int nready=0/*已连接描述符个数*/,client[FD_SETSIZE]={0};//已连接IO集
    int maxi=0/*client数组下标*/,maxfd=0/*select函数第一个参数*/;
    fd_set allset,rset;//可操作IO集
    SA_I cli;//客户端地址结构
    socklen_t addrlen=16; //客户端地址长度
    pid_t pid;//创建子进程
    int fd_out;//标准输出重定向前记录
    int serv_fd;//服务器信息记录文件
    char ip[128]={0};//解析ip存放地址
    time_t now;//当前时间
    int i=0/*循环变量*/;
    
    
    if(get_http_conf()==-1){
        printf("exit\n");
        return -1;
    };//获取http配置
    if(!config.port){
        printf("config erro!\n");
        return -1;
    }
    dprintf(1,"启动 listen port:%d\n",config.port);
    s_fd=t_listen(config.port,100);//监听端口
    if(s_fd==-1){
        perror("t_listen");
        return -1;
    }

    //初始化
    maxfd=s_fd;
    maxi=-1;
    FD_ZERO(&allset);
    FD_SET(s_fd,&allset);//将监听端口描述字加入集

    //初始化client数组
    for(i=0;i<=FD_SETSIZE;i++)
        client[i]=-1;
    
    //提示信息标准输出重定向
#ifndef DEBUG
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
#endif
    while(1){
#ifdef DEBUG
        printf("1 nready=%d\n",nready);
#endif
        rset=allset;    
        
        nready=select(maxfd+1,&rset,NULL,NULL,NULL);//防止accept在内核态被中断
        if(nready==-1){
            //perror("select");
            continue;
        }
#ifdef DEBUG
        printf("2 nready=%d\n",nready);
#endif
        if(FD_ISSET(s_fd,&rset)){//有新的连接
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
        
            //将新的已连接描述符加到可操作集，下标最小&&无其他描述符的位置
            for(i=0;i<=FD_SETSIZE;i++){
                if(client[i]<0){
                    client[i]=conn_fd;
                    break;
                }
            }
            if(i==FD_SETSIZE){
                printf("too many client...\n");
                return -1;
            }
            FD_SET(conn_fd,&allset);//将新的描述符添加到全部可用集内
            if(i>maxi) maxi=i;
            if(conn_fd>maxfd)maxfd=conn_fd;
            if(--nready<=0)continue;//新的连接全部处理，退出
        }
        
        //负责和客户端端的通讯，业务的处理
        for(i=0;i<=maxi;i++){
            if((apt_fd=client[i])<0)continue;//在集内下标为i的元素为-1,略过
            signal(SIGCHLD,handler);
            pid=fork();
            switch(pid){
                case -1:
                    perror("fork");
                    return -1;
                case 0:
                    close(s_fd);
                    doit(apt_fd);
                    shutdown(apt_fd,SHUT_WR);//关闭连接描述符写端
                    //sleep(10);
                    exit(0);
                default:
                    close(apt_fd);
                    FD_CLR(apt_fd,&allset);
                    client[i]=-1;
                    break;
            }
        }
}
    dup2(fd_out,1);
    close(s_fd);
    return 0;
}
