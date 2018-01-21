#include <stdio.h>
#include "ll.h"
//访问目录函数
void Dir(char *path){
    struct dirent *dir;
	//打开目录文件
    DIR *p = opendir(path);
    if (!p){
        perror("opendir");
        return;
    }
	//读取目录内文件分析
    while(dir = readdir(p)){
	//打印文件元数据
      	char buf[100] = {0};
        sprintf(buf,"%s/%s",path,dir->d_name);
        print(buf);
    //普通文件跳过   
		if (dir->d_type == 8 )	continue;
    //目录类型文件两种情况   
		if(dir->d_type == 4)
	//隐藏文件跳过
            if(!strcmp(dir->d_name,".")||!strcmp(dir->d_name,".."))
				continue;
	//正常目录类型文件调用递归函数
            else Dir(buf);
       }
	//关闭
    closedir(p);
}
//打印元数据
void print(char *path){
    struct stat data;
	struct tm *TM;
    int f = stat(path,&data);
    if(f == -1){
        perror("stat");
        return ;
    }
	//文件类型
    int m = data.st_mode&S_IFMT;
    if (m == S_IFREG) printf("-");
    else printf("d");
	//属主权限
    m = data.st_mode&S_IRWXU;
    if (m & S_IRUSR) printf("r");
    else printf("-");
    if (m & S_IWUSR) printf("w");
    else printf("-");
    if (m & S_IXUSR) printf("x");
    else printf("-");
	//组权限
    m = data.st_mode&S_IRWXG;
    if (m & S_IRGRP) printf("r");
    else printf("-");
    if (m & S_IWGRP) printf("w");
    else printf("-");
    if (m & S_IXGRP) printf("x");
    else printf("-");
	//其他人权限
    m = data.st_mode&S_IRWXO;
    if (m & S_IROTH) printf("r");
    else printf("-");
    if (m & S_IWOTH) printf("w");
    else printf("-");
    if (m & S_IXOTH) printf("x");
    else printf("-");
	//硬链接数
    printf(" %d",data.st_nlink);
	//属主名
    printf(" %s",getpwuid(data.st_uid)->pw_name);
  //组名
	printf(" %s",getgrgid(data.st_gid)->gr_name);
	//文件大小（9个数对齐）
	printf(" %9ld",data.st_size);
	//时间调整打印方式
	//printf(" %s",ctime(&data.st_mtime));
	TM = localtime(&data.st_mtime);
    printf(" %d-%02d-%02d %02d:%02d",TM->tm_year+1900,\
			TM->tm_mon+1,TM->tm_mday,\
			TM->tm_hour,TM->tm_min);
  //文件名
	printf(" %s",path);
    printf("\n");
}
