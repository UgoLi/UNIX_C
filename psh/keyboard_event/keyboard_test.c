/*************************************************************************
	> File Name: keyboard_test.c
	> Author:UgoLi 
	> Mail: 2653920896@qq.com
	> Created Time: 2017年08月13日 星期日 23时17分17秒
 ************************************************************************/

#include<stdio.h>
#include<unistd.h>
#include<linux/input.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<fcntl.h>
#include<string.h>

int main(){
    struct input_event event_kb;
    int fd_kb=open("/dev/input/event1",O_RDONLY);//键盘输入
    if(fd_kb==-1){
        perror("open(2)->'/dev/input/event1'");
        return -1;
    }
    while(1){
        if(read(fd_kb,&event_kb,sizeof(event_kb))==sizeof(event_kb)){
            if(event_kb.type==EV_KEY){
                if(event_kb.value==1){//键按下
                    switch(event_kb.code){
                        case KEY_ESC:
                            return 0;
                        case KEY_Q:
                            printf("q\n");
                            break;
                        case KEY_W:
                            printf("w\n");
                            break;
                        case KEY_RIGHT:
                            fflush(0);
                            printf("right");
                            break;
                    }
                }
            }
        }

    }
    close(fd_kb);
    return 0;
}
