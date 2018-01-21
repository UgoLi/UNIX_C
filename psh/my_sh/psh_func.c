/*************************************************************************
	> File Name: psh_func.c
	> Author:UgoLi 
	> Mail: 2653920896@qq.com
	> Created Time: 2017年08月12日 星期六 14时05分53秒
 ************************************************************************/

#include"psh.h"

int pipe_flag;  //有管道命令标志
int argc;  //参数个数

/*===========================================================================================*/
/*终端命令解析 逐个字符 参数以空格分开
*char *buf  命令缓冲区
*int size_b 命令缓冲区大小
*char* argv[] 命令行参数数组
*int size_a   命令行参数数组大小，最后一个参数必须是NULL
*注意:若有管道'|',则pipe_flag被设置为1
* */
void getcmd(char*buf,int size_b,char* argv[],int size_a){
    int i=0;
    while(++i){
        if(i>=size_b){//超过边界截断处理，将输入缓冲区超过的内容读出
            if(getchar()=='\n')break;
            continue;   
        }
        buf[i-1]=getchar();
        if(buf[i-1]==' ')buf[i-1]='\0';
        if((buf[i-1]=='\n')||(i==size_b)){//缓冲区边界处理
            char tmp=buf[i-1];
            buf[i-1]='\0';
            if(tmp=='\n')break;
        }
    }
    
    int j=0;
    argc=0;pipe_flag=0;//全局变量初始化
    for(j=0;j<i-1;argc++){
        while(buf[j]=='\0'){
            if((++j)>=i-1)break;
        }
        if(j>=i-1)break;//防止argv[0]=NULL被下面程序访问
        argv[argc]=buf+j;
        j+=strlen(argv[argc]);
        if(!argc&&(!strcmp(argv[0],"ls")||!strcmp(argv[0],"rm")||\
                !strcmp(argv[0],"mv")||!strcmp(argv[0],"cp"))){//需要设置默认选项的命令
            argc++;
            argv[argc]="";
        }
        if(argc&&!strcmp(argv[argc],"|")){
            pipe_flag=1;
        }
        if(argc>=size_a-2){
            printf("psh:命令过长，已被截断执行\n");
            break;
        }
    }
    if(argc>=1&&!strcmp(argv[0],"ls"))
        argv[1]="--color=auto";
    else if(argc>=1&&(!strcmp(argv[0],"rm")||!strcmp(argv[0],"mv")||!strcmp(argv[0],"cp")))
        argv[1]="-i";
    argv[argc]=NULL;
    return;
}
/*===========================================================================================*/
/*cd 命令
*char *argv[]   由getcmd带回的参数
* */
void cd(char *argv[]){
    char *path/*转义指针*/;
    char *wd=malloc(1024*sizeof(char))/*为目标目录分配存储空间*/;
    bzero(wd,1024);
    //默认路径处理
    if(!argv[1]){//NULL 处理
        argv[1]=getenv("HOME");
    }

    if((!strncmp(argv[1],"~",1))){//～ 转义处理
        path=getenv("HOME");
        argv[1]=strcat(path,strchr(argv[1],'~')+1);
    }

    if(!strcmp(argv[1],"-")){ //- 转义处理
        argv[1]=getenv("OLDPWD");
        printf("%s\n",argv[1]);
    }

    if(!strncmp(argv[1],".",1)){// 相对路进处理
        strcat(wd,getenv("PWD"));
        strcat(wd,"/");
        strcat(wd,argv[1]);
        argv[1]=wd;
    }
    
    //环境变量记录，然后，切换工作目录
    setenv("OLDPWD",getenv("PWD"),1);
    if(chdir(argv[1])){
        printf("%s\n",argv[1]);
        perror("chdir");
        free(wd);
        return;
    }
    getcwd(wd,1024);
    setenv("PWD",wd,1);
    free(wd);
    return;
}   

/*=========================================================================================
系统时间
返回例，19:00:00
*/
char *getLocTime(void){
    /*access time*/
    time_t loc;
    ctime_t_loc atime;
    char week_b[8];
    char month_b[8];
    atime.week=week_b;
    atime.month=month_b;
    time(&loc);
    char *time_a=ctime(&loc);
    sscanf(time_a,"%s %s %d %d:%d:%d %u",atime.week,atime.month,&atime.day,\
            &atime.h,&atime.m,&atime.s,&atime.year);  
    static char loctime[28];bzero(loctime,28);
    sprintf(loctime,"[%02d:%02d:%02d]",atime.h,atime.m,atime.s);
    return loctime;
}

void doexit(void){
    pid_t pid=fork();
    switch(pid){
        case -1:
            perror("fork");
            return;
        case 0:
            execlp("clear","clear",NULL);
            printf("clear err\n");
            return;
        default:
            wait(NULL);
            printf(RED"psh "NONE"状态 [+已退出]\n");
            return;
    }
}


/*===========================================================================
*设置程序的开始动作
* */
void dostart(void){

#ifndef DEBUG   //调试期间不屏蔽信号
    /*屏蔽信号*/
    sigset_t newset,oldset;
    sigfillset(&newset);
    sigprocmask(SIG_SETMASK,&newset,&oldset);
#endif

    setenv("OLDPWD",getenv("PWD"),1);//初始化环境变量OLDPWD
    //初始化界面
    pid_t pid=fork();
    if(pid==-1){
        perror("fork");
        return;
    }
    if(pid==0){
        execlp("clear","clear",NULL);
        perror("execlp");
        return;
    }
    wait(NULL);
    printf("提示:输入'q'或'exit'退出 psh.\n");//提示    
    return;
}



/*==============================================================
*psh 管道功能
*int argc 参数个数 
*char **argv 参数内容
*成功返回0,否在-1
* */
int psh_pipe(int argc,char **argv){
    int fd[2]={0};
    int fdin=0,fdout=1;
    int first_rt=0;
    int k=0;
    while(1){
        if(k>=argc-1)break;
        //printf("%s\n",argv[k]);
        if(!strcmp(argv[k],"|")){
            argv[k]=NULL;
            break;
        }
        k++;
    }
#ifdef  DEBUG  //条件编译，调试解析结果
        printf("出现'|'的位置argv[%d]\n",k);
        printf("解析'|'后的命令：");
        int l=0;
        printf("cmd: ");
        for(;;l++){
            if(l==k){
                printf(GREEN"{'|'管道读端}+ "NONE);
                continue;
            }
            if(!argv[l])break;
            printf(GREEN"{argv[%d]}"NONE"%s ",l,argv[l]);
        }
        printf("\n");
#endif  
    int n=pipe(fd);
    if(n==-1){
        perror("pipe");
        return -1;
    }
    pid_t first = fork();
    switch(first){
        case -1:
            perror("fork");
            return -1;
        case 0:
            close(fd[0]);
            dup2(fd[1],1);
            close(fd[1]);
            execvp(argv[0],argv);
            printf("'%s' 未知命令\n",argv[1]);
            return -1;
        default: 
            //wait(&first_rt);
            //if(first_rt==-1)
            //return -1;
            break;
#ifdef DEBUG
            printf("回收管道写端进程资源\n");
#endif
    }
    pid_t second = fork();
    switch(second){
        case -1:
            perror("fork");
            return -1;
        case 0:
            close(fd[1]);
            dup2(fd[0],STDOUT_FILENO);
            close(fd[0]);
            execvp(argv[k+1],argv+k+1);
            printf("'%s' 未知命令\n",argv[k+1]);
            return -1;
        default:
            wait(NULL);
            //close(fd[0]);
            //close(fd[1]);
#ifndef DEBUG
            printf("回收管道读端进程资源\n");
#endif
    }
    return 0;
}




