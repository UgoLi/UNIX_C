/*************************************************************************
	> File Name: psh.c
	> Author:UgoLi 
	> Mail: 2653920896@qq.com
	> Created Time: 2017年08月11日 星期五 20时08分01秒
 ************************************************************************/

#include"psh.h"


const int size_b=1024; /*命令缓冲区大小*/ 
const int size_a=20;/*命令行参数最大数量*/
int main(void){
    char buf[size_b]/*命令行字符缓冲区*/;
    char *p_buf=buf/*buf区域的访问指针*/;
    char *argv[size_a]/*命令行参数数组*/;
    char **p_argv=argv/*命令行参数*/;
   
    dostart();//开始动作
    
    
    while(1){//阻塞处理输入命令 
        bzero(buf,size_b);//初始化命令行参数缓存区
        
        printf(PURPLE"%s%s[@~Ubuntu]"GREEN"%s$:"NONE,getLocTime(),getenv("USER"),\
               strrchr(getenv("PWD"),'/')+1);//打印命令提示符
            
        fflush(0);//清空输入缓存    
        
        getcmd(p_buf,size_b,argv,size_a);//解析输入的命令。无命令，阻塞
        
#ifdef  DEBUG  //条件编译，调试解析结果
        printf("获取到的命令参数:");
        int l=0;
        printf("cmd: ");
        for(;;l++){
            if(!argv[l])break;
            printf("%s ",argv[l]);
        }
        printf("\n");
#endif  
#ifndef PIPE
        if(pipe_flag){//执行管道处理
#ifdef DEBUG
            printf("已检测到'|'管道命令\n");
#endif
            if(-1==psh_pipe(argc,argv))
            continue;
        }
#endif

        if(!argv[0])continue;//未输入命令重新等待输入
        
        if(!strcmp(argv[0],"cd")){
            //printf("执行 cd命令\n");
            cd(argv); 
            continue;
        }
        
        if(!strcmp(argv[0],"exit")||!strcmp(argv[0],"q")){
            atexit(doexit);//退出动作
            return 0;
        }
        /*=================以上为内嵌命令===============================*/
        
        
        //printf("fork 执行外部命令\n");
        pid_t pid=fork();
        switch(pid){
            case -1:
                perror("psh::fork");
                return -1;
            case 0:
                execvp(argv[0],p_argv);
                printf("%s:未找到命令\n",argv[0]);
                exit(-1);
            default:
                wait(NULL);
        }       
    }
    return 1;
}
