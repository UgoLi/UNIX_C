/*************************************************************************
	> File Name: dir_op.c
	> Author: 
	> Mail: 
	> Created Time: 2017年07月08日 星期六 10时29分38秒
 ************************************************************************/

#include<stdio.h>
#include <sys/types.h>
#include <dirent.h>
int main(int agrc,char *argv[]){
    DIR *d;
    struct dirent *p;
    //打开指定的文件夹
    d=opendir(argv[1]);
    if(!d){
        perror("opendir");
        return -1;
    }
    printf("opendir success...\n");
    //从文件夹流中读取一条数据
    
    while(1){
        if(!(p=readdir(d)))break;
        printf("filename:%s\tinode:%lu\n",p->d_name,p->d_ino);
    }
    
    
    //关闭文件夹
    closedir(d);
    return 0;
}
