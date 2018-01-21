/*************************************************************************
	> File Name: remove_num.c
	> Author:UgoLi 
	> Mail: 2653920896@qq.com
	> Created Time: 2017年07月31日 星期一 15时41分05秒
 ************************************************************************/


#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include<string.h>
int main(void){
    const int size=31;
    char ch,buf[size];
    int fd_in,fd_out,i=0,cnt=0;
    int r=read(STDIN_FILENO,buf,size);
    if(strlen(buf)==size&&*(buf+size-1)!='\n'){
        scanf("%*[^\n]");
        scanf("%*c");
        *(buf+size-1)='\n';
    }
    write(fd_in=open("zfc.in",O_RDWR|O_CREAT|O_APPEND,0774),buf,r);
    if(fd_in==-1){
        perror("open:zfc.in");
        return -1;
    }
    fd_out=open("zfc.out",O_RDWR|O_CREAT|O_APPEND,0774);
    if(fd_out==-1){
        perror("open:zfc.out");
        return -1;
    }
    dprintf(fd_out,"字母部分:");
    while(1){
        ch=buf[i++];
        if(ch>='0'&&ch<='9'){
            cnt++;
        }else if(ch=='\n'||i==30)
        break;
        else{
            write(fd_out,&ch,1);
        }
    }
    dprintf(fd_out,"\n数字个数:%d\n",cnt);
    close(fd_in);
    close(fd_out);
    return 0;
}

