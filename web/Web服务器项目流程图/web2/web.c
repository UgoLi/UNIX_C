
#include "web.h"
#include <string.h>
#include <strings.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
char workdir[128]="/home/ugo/Desktop/Tedu old/web/Web服务器项目流程图/www";
char filename[256];

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

static int get_request(int fd,req_t *req){
    int r;
    char buf[1024];
    //将浏览器发送过来的信息，写到buf中
    r=read(fd,buf,1024);
    sscanf(buf,"%s %s %s\r\n",\
            req->method,req->path,\
            req->protocol);
    //设置默认路径
    if(!strcmp(req->path,"/"))
        strcat(req->path,"index.html");
    return 0;

}
static int get_code(const char *p){

    //获取文件的绝对路径
    bzero(filename,256);
   strcat(filename,workdir);
   strcat(filename,p);
   printf("filename:%s\n",filename);
   if(!access(filename,F_OK)&&!access(filename,R_OK)){

       return 200;
   }else{

        return 404;
   }

}
int get_f_type(const char *path){
    char *file=strrchr(path,'/');
    char *ext_file=strrchr(file,'.');
    printf("%s\n",ext_file);
    if(!strcmp(ext_file,".html"))
        return 1;
    if(!strcmp(ext_file,".jpg"))
        return 2;
    if(!strcmp(ext_file,".png"))
        return 3;
    return -1;
}
void get_type(const char *f,response_t *res){
    int f_type; 
    f_type=get_f_type(f);
    switch (f_type){
        case 1: 
            strcpy(res->f_type,"text/html");
            break;
        case 2:
            strcpy(res->f_type,"image/jpg");
            break;
        case 3:
            strcpy(res->f_type,"image/png");
            break;
        default:
            break;

    }
    return;

}
static int org_response(req_t *r,\
        response_t *res){
    //初始化协议
    strcpy(res->proto,r->protocol);
    //获取Content-Type:的信息
    get_type(r->path,res);
    printf("file type:%s\n",res->f_type);
    //获取code信息
    res->code=get_code(r->path);
    printf("code:%d\n",res->code);
    return 0;
}
//将文件的内容输出到浏览器
static int response_b(int fd){
    char buf[128];
    int r;
    int s_fd=open(filename,O_RDONLY);
    if(s_fd==-1){
        perror("open");
        return -1;
    }
    while((r=read(s_fd,buf,128))>0)
        write(fd,buf,r);
    return 0;

}
//根据响应信息组织客户端的响应
static void do_response(int fd,response_t *rs,req_t *rq){
    char head[256]={0};
    

    if(rs->code==200){//需要将filename文件发送给浏览器
            //回文件
        sprintf(head,"%s %d\r\nContent-Type:%s\r\n\r\n",\
                rq->protocol,rs->code,rs->f_type);

        //给浏览器回响应头
        write(fd,head,strlen(head));
        //文件的拷贝
        response_b(fd);

    }
    if(rs->code==404){
        char *error="<html><body>file not found!</body></html>";
        sprintf(head,"%s %d\r\nContent-Type:%s\r\n\r\n",\
                rq->protocol,rs->code,"text/html");
        
        //给浏览器回响应头
        write(fd,head,strlen(head));
        write(fd,error,strlen(error));

    }
    return;
}
void doit(int c_fd){
    req_t r;
    response_t res;
    //获取浏览器的请求头信息
    get_request(c_fd,&r);
    printf("%s\t%s\t%s\n",r.method,
            r.path,r.protocol);
    //根据请求头信息，组织响应信息
    org_response(&r,&res);
    //响应浏览器
    do_response(c_fd,&res,&r);
    return;
}
