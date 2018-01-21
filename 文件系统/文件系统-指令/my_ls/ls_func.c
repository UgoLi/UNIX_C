/*************************************************************************
	> File Name: ls_func.c
	> Author:UgoLi 
	> Mail: 2653920896@qq.com
	> Created Time: 2017年08月09日 星期三 19时06分35秒
 ************************************************************************/

#include "my_ls.h"

/*获取文件类型*/
int getftype(const char *filename,struct stat *st,f_type *ftype){
    if(stat(filename,st)){
        perror("stat");
        return -1;
    }
    switch(st->st_mode&S_IFMT){
        case S_IFREG:
            *ftype='-';
            break;
        case S_IFDIR:
            *ftype='d';
            break;
        default:
            break;
    }
    return 0;
}


/*元数据写到屏幕上*/
int cnt=0;
void writefstat(const char* filename,struct stat *st,f_type *ftype){
    if(*ftype=='d'&&(filename[strlen(filename)-1]!='.')){
        printf(YELLOW);
    }
    
    /*file type*/
    printf("%c",*ftype);

    /*user*/
    if(st->st_mode&S_IRUSR)printf("r");else printf("-");
    if(st->st_mode&S_IWUSR)printf("w");else printf("-");
    if(st->st_mode&S_IXUSR)printf("x");else printf("-");
   
    /*group*/
    if(st->st_mode&S_IRGRP)printf("r");else printf("-");
    if(st->st_mode&S_IRGRP)printf("w");else printf("-");
    if(st->st_mode&S_IRGRP)printf("x");else printf("-");
    
    /*other*/
    if(st->st_mode&S_IROTH)printf("r");else printf("-");
    if(st->st_mode&S_IROTH)printf("w");else printf("-");
    if(st->st_mode&S_IROTH)printf("x ");else printf("- ");
    
    /*hard link*/
    printf("%d ",st->st_nlink);
    
    /*user & group*/
    printf("%6s ",getpwuid(st->st_uid)->pw_name);
    printf("%6s ",getgrgid(st->st_gid)->gr_name);
   
    /*size*/
    printf("%6ldb ",st->st_size);

    /*access time*/
    fatime atime;
    char week_b[8];
    char month_b[8];
    atime.week=week_b;
    atime.month=month_b;
    char *time_a=ctime(&st->st_atime);
    sscanf(time_a,"%s %s %d %d:%d:%d %u",atime.week,atime.month,&atime.day,\
            &atime.h,&atime.m,&atime.s,&atime.year);  
    printf("%2d:%2d ",atime.h,atime.m);
    
    /*filename*/
    char buf[256],tmp[256];
    strcpy(tmp,filename);
    if(tmp[strlen(tmp)-1]=='/'){
        tmp[strlen(tmp)-1]='\0';
    }
    char *str=strrchr(tmp,'/');
    if(str){
        sscanf(str,"/%s",buf);
    }else{
        sscanf(tmp,"%s",buf);
    }
    printf("%s",buf);
    if(*ftype=='d'){
        printf("/");
    }
    printf("\n"NONE"%d",cnt++);
}


/*层次缩进函数*/
void level(int tab_cnt){/*use before writefstat()*/
    int i=tab_cnt;
    while(i--){
        printf("\t");
    }
    if(tab_cnt)
    printf(GREEN"|lv%2d--- "NONE,tab_cnt);
}

/*处理函数*/
void deal(const char* filename,int tab_cnt/*递归层数*/){
    f_type ftype;
    struct stat st;
    int a=getftype(filename,&st,&ftype);
    if(a!=0){
        return;
    }
    /*显示元数据*/
    level(tab_cnt);
    writefstat(filename,&st,&ftype);
    if(access(filename,X_OK)&&ftype=='d'){/*无通过权限的目录不访问*/
        return;
    }

    switch(ftype){
        
        case 'd':{/*目录文件*/ 
                /*显示目录内文件*/
                tab_cnt++;/*缩进计数*/
                DIR *f=opendir(filename);
                struct dirent *p;
                
                /*read content of file*/
                while(1){
                    
                    char fpath[512];
                    bzero(fpath,512);
                    strcpy(fpath,filename);
                    if(fpath[strlen(fpath)-1]!='/'){
                        strcat(fpath,"/");
                    }
                    
                    
                    if(!(p=readdir(f)))
                        break;
                    char *path=strcat(fpath,p->d_name);
                    /*处理"."和".."文件*/
                    if(!strcmp(p->d_name,".")||!strcmp(p->d_name,"..")){
                        level(tab_cnt);
                        printf(CYAN);
                        writefstat(path,&st,&ftype);
                    }
                    else{    
                        deal(path,tab_cnt);
                    }
                }       
                 
            }
            break;
         
        default://其他
            break;
       
        
    }
    return;
}
