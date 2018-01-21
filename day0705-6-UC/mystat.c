/*************************************************************************
	> File Name: mystat.c
	> Author: 
	> Mail: 
	> Created Time: 2017年07月07日 星期五 16时04分44秒
 ************************************************************************/

#include <stdio.h>
#include <t_file.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <time.h>
#include <pwd.h>
#include <grp.h>
int main(int argc,char *argv[]){
    int s;
    struct stat sbuf;
    //获取文件的元数据
    
    s=stat(argv[1],&sbuf);
    if(-1==s){
        perror("stat");
        return -1;
    }
    if(S_ISREG(sbuf.st_mode))
        printf("-");
    if(S_ISDIR(sbuf.st_mode))
        printf("d");
    /*
    switch(sbuf.st_mode&S_IFMT){
        case S_IFREG:
            printf("-");
            break;
        case S_IFDIR:
            printf("d");
            break;
        default:
            break;
    }
    */
    //获取拥有者的权限
    int u_mode=sbuf.st_mode&S_IRWXU;
    //判断拥有者是否有读的权限
    if(u_mode&S_IRUSR)printf("r");else printf("-");
    if(u_mode&S_IWUSR)printf("w");else printf("-");
    if(u_mode&S_IXUSR)printf("x");else printf("-");
    //获取组权限
    int g_mode=sbuf.st_mode&S_IRWXG;
    //判断组权限
    if(g_mode&S_IRGRP)printf("r");else printf("-");
    if(g_mode&S_IWGRP)printf("w");else printf("-");
    if(g_mode&S_IXGRP)printf("x");else printf("-");
    //获取其他用户权限
    int o_mode=sbuf.st_mode&S_IRWXO;
    //判断其他用户权限
    if(o_mode&S_IROTH)printf("r");else printf("-");
    if(o_mode&S_IWOTH)printf("w");else printf("-");
    if(o_mode&S_IXOTH)printf("x");else printf("-");
    printf(" ");
    //printf("\n");
    //printf("%o ",sbuf.st_mode);                      //mode
    //printf("%lu ",sbuf.st_ino);                      //inode
    printf("%lu ",sbuf.st_nlink);                    //hard links
    printf("%ldkb ",sbuf.st_size);                     //size
    //printf("%u ",sbuf.st_uid);                       //uid
    printf("%s ",(getpwuid(sbuf.st_uid))->pw_name);  //username
    //printf("%u ",sbuf.st_gid);                       //gid
    printf("%s ",(getgrgid(sbuf.st_gid))->gr_name);  //groupname
    //printf("%ld ",sbuf.st_atime);                    //atime
    printf("%s ",ctime(&(sbuf.st_atime)));           //atime_c format
    return 0;
}
