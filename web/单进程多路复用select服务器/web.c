/*************************************************************************
	> File Name: server.c
	> Author:UgoLi 
	> Mail: 2653920896@qq.com
	> Created Time: 2017年07月19日 星期三 10时22分41秒
 ************************************************************************/

#include"web.h"

/*监听端口号为port的端口的被访问信号，并此监听可在队列
 中存放backlog个监听到但未处理的信号(未决信号)*/
int t_listen(int port,int num){
    int s_fd=0/*socket返回描述符*/;
    SA_I ser;
    //1、创建socket,AF_INET->IPV4协议家族,基于连接的SOCK_STREAM
    s_fd=socket(AF_INET,SOCK_STREAM,0);
    if(s_fd==-1){
        return -1;
    }
    //初始化服务器的ip地址和端口号
    ser.sin_family=AF_INET;//指定IPV4家族
    ser.sin_port=htons(port);     //指定端口号，并转成网络字节序
    //指定服务器的ip地址。
    //INADDR_ANY代表本机上的所有ip地址，长整型的
    ser.sin_addr.s_addr=htonl(INADDR_ANY);
    
    //2、将socket通讯端点s_fd与服务器ip地址和端口好绑定
    int b=bind(s_fd,(SA *)&ser,sizeof(SA_I));
    if(b==-1){
        return -1;
    }
    //3、监听socket
    listen(s_fd,num);
    return s_fd;
}

/*获取服务器配置文件信息*/
http_conf config;
int get_http_conf(void){
    char buf[1024];
    bzero(buf,1024);
    int fd=open("/home/ugo/Desktop/Tedu_old/web/单线程多路复用select服务器/var/http.conf",O_RDONLY);
    if(fd==-1){
        perror("get_http_conf");
        close(fd);
        return -1;
    }
    read(fd,buf,1024);
    close(fd);
    sscanf(buf,"port %hd\nworkdir %s\n",&(config.port),config.workdir);
    return 0;
}

/*解析获取的请求头信息*/
void get_request_head(int conn_fd,request_t *req_t){
    char buf[1024]={0};
    char filename[128]={0};
    char *end_r_line= "***********************************analysis************************************************\n";
    dprintf(1,"===================================receive=================================================\n");
    int r=read(conn_fd,buf,1024);
    write(1,buf,r);
    write(1,end_r_line,strlen(end_r_line));
    
    sscanf(buf,"%s %s %s\r\n",\
           req_t->method,req_t->path,req_t->protocol);
    //检测一下
    dprintf(1,"%s %s %s\r\n",req_t->method,req_t->path,req_t->protocol);
    //默认路径设置
    if(!strcmp(req_t->path,"/"))
        strcpy(req_t->path,"/index.html");

    //完整路径处理
    bzero(filename,128);
    strcpy(filename,config.workdir);
    strcat(filename,req_t->path);
    strcpy(req_t->path,filename);
    dprintf(1,"%s\n",req_t->path);
    return;
}
/*根据获取的请求头信息组织回应代码*/
int get_code(const request_t *req_t){
    if(!access(req_t->path,R_OK)&&!access(req_t->path,F_OK)){
        dprintf(1,"文件 '%s' 存在...\n",req_t->path);
        return 200;
    }else{
        dprintf(1,"文件 '%s' 不存在...\n",req_t->path);
        return 404;
    }
}
char * get_f_type(const request_t *req_t){
    char *path=strrchr(req_t->path,'/');

    //check '.' in string of 'path'
    int cnt=0;
    char *check=path;
    while(1){
        if(*(check++)=='.')
            cnt++;
        if(*check=='\0')
            break;
    }
    if(!cnt){
        return "text/html";  
    }
    
    //path include '.',check type 
    char *type=strrchr(path,'.');
    if(!strcmp(type,".html"))
        return  "text/html";
    if(!strcmp(type,".jpg"))
        return "image/jpg";
    if(!strcmp(type,".png"))
        return "image/png";
    dprintf(1,"未找到对应文件类型\n");
    return "text/html";
}


/*根据获取的请求头信息组织响应头信息*/
void org_respond(const request_t *req_t,response_t *res_t){
    strcpy(res_t->protocol,req_t->protocol);
    res_t->code=get_code(req_t);
    char *str=get_f_type(req_t);
    strcpy(res_t->f_type,str);
    return;
}
/*依据响应头做出响应*/
void do_response(int conn_fd,request_t *req_t,response_t *res_t){
    char res_head[256]={0};
    char *head_s_line="\n**********************************do_response*********************************************\n";
        
    write(1,head_s_line,strlen(head_s_line));
    //返回头内容
    if(res_t->code==200){
        sprintf(res_head,"%s %d\r\nContet-Type:%s\r\n\r\n",\
                res_t->protocol,res_t->code,res_t->f_type);
        write(conn_fd,res_head,strlen(res_head));
        
        //显示到显示器
        write(1,res_head,strlen(res_head));
        
        //读取请求文件并发送
        int fd=open(req_t->path,O_RDONLY);
        dprintf(1,"发送文件:%s\n",req_t->path);
        if(fd==-1){
            perror("main::doit::do_response::open");
            return;
        }
        char buf[1024*1024]={0};
        while(1){
            bzero(buf,1024*1024);
            int r=read(fd,buf,1024*1024);
            if(!r||r==-1){
                if(r==-1){
                    perror("main::doit::do_response::read");
                    close(fd);
                    return;
                }
                break;
            }
            dprintf(1,"发送字节数:%d\n",r);
            write(conn_fd,buf,r);
        }
    }


    if(res_t->code==404){
        char *error="<html><body>file not found!</body></html>"; 
        sprintf(res_head,"%s %d\r\nContet-Type:%s\r\n\r\n",\
                res_t->protocol,res_t->code,res_t->f_type);
        write(conn_fd,res_head,strlen(res_head));
        write(conn_fd,error,strlen(error));
    }
    dprintf(1,"=======================================end=================================================\n\n\n");
}

/*处理并响应请求信息*/
int doit(int conn_fd){
    request_t req_t;//存放接收头信息
    response_t res_t;//存放回应头信息
    get_request_head(conn_fd,&req_t);//解析
    org_respond(&req_t,&res_t);//组织
    do_response(conn_fd,&req_t,&res_t);//响应-->浏览器
    return 0;
}


void handler(int sig){
    pid_t pid;
    int status;
    if(sig==SIGCHLD){//signal of child process termination
        //printf("handler pid=%d\n",getpid());
        while(1){
            pid=waitpid(-1,&status,WNOHANG);    
            if(pid==-1){
                //perror("waitpid");
                return;
            }
            else if(pid==0){
                //printf("no signal recived\n");
                break;
            }else{
                //printf("release pro id=%d=====================================\n",pid);
                //sleep(2);
                if(WIFSIGNALED(status)){
                    //printf("terminated by signal %d\n",WTERMSIG(status));
                }
                if(WIFEXITED(status)){
                    //printf("child exit code=%d\n",WEXITSTATUS(status));
                }
                //printf("release over============================================\n");
            }
            //printf("\n\n\n\n\n");
        }
    }
}












