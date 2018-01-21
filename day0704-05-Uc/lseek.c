/*************************************************************************
	> File Name: lseek.c
	> Author: 
	> Mail: 
	> Created Time: 2017年07月07日 星期五 11时21分08秒
 ************************************************************************/

#include<stdio.h>
#include<t_file.h>
int main(void){
    int fd,r;
    char buff[12];
    //以只读方式打开文件
    fd=open("mycat.c",O_RDONLY);
    if(fd==-1){
        perror("open");
        return -1;
    }
    //将读写位置定义在文件的第200个字节
    lseek(fd,440L,SEEK_SET);
    r=read(fd,buff,10);
    write(1,buff,r);
    printf("\n");
    close(fd);
    return 0;
}
