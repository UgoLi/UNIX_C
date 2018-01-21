#include <stdlib.h>
#include <sys/wait.h>
#include "web.h"

int main(void){
    int s_fd,conn_fd;

    s_fd=t_listen(8000,5);
    if(s_fd==-1){
        perror("t_listen");
        return -1;
    }
    //从未决连接队列中取出一个连接处理
    while(1){
        //取出一个连接,如果没有未决连接，阻塞等待
        conn_fd=accept(s_fd,NULL,NULL);
        if(conn_fd==-1){
            perror("accept");
            return -1;
        }

        //负责和客户端的通讯,业务处理
        doit(conn_fd);

        close(conn_fd);

    }
    return 0;
}
