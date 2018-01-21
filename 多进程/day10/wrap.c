#include <stdio.h>
#include <p_file.h>

int main(int  argc,char *argv[]){
    //关闭标准输入文件描述符
    close(0);
    //打开文件，以只读方式打开文件
    //fd==0
    int fd=open(argv[1],O_RDONLY);
    if(fd==-1){
        perror("open");
        return -1;
    }
    execl("./upper","upper",NULL);
    close(fd);
    return 0;
}
