/*************************************************************************
	> File Name: mouse_test.c
	> Author:UgoLi 
	> Mail: 2653920896@qq.com
	> Created Time: 2017年08月14日 星期一 00时10分34秒
 ************************************************************************/

#include<stdio.h>
#include<unistd.h>
#include<linux/input.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<fcntl.h>

int main(){
    struct input_event event_mouse;
    int fd_mouse=open("/dev/input/event2",O_RDONLY);//mouse input 
    if(fd_mouse==-1){
        perror("opne");
        return -1;
    }
    while(1){
        if(read(fd_mouse,&event_mouse,sizeof(event_mouse))==sizeof(event_mouse)){
            if(event_mouse.type==EV_REL){
                if(event_mouse.code==REL_WHEEL){
                    printf("REL_WHELL %d\n",event_mouse.value);//-1 down,1 up
                }
                if(event_mouse.code==BTN_LEFT&&event_mouse.value==1)//left button,1down,0release
                    printf("left down:%d\n",event_mouse.code);
                if(event_mouse.code==BTN_LEFT&&event_mouse.value==0)
                    printf("left release:%d\n",event_mouse.code);
            }
        }
    }
    close(fd_mouse);
    return 0;
}
