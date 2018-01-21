/*************************************************************************
	> File Name: env_op.c
	> Author: 
	> Mail: 
	> Created Time: 2017年07月11日 星期二 17时24分26秒
 ************************************************************************/

#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
int main(void){
    //获取环境变量USER的值
    printf("%s\n",getenv("USER"));
    putenv("NAME=pycoming");
    printf("%s\n",getenv("NAME"));
    putenv("NAME=pyco");
    printf("%s\n",getenv("NAME"));
    setenv("NAME","hello",0);
    printf("setenv overwrite=0...%s\n",getenv("NAME"));
    setenv("NAME","hello",1);
    printf("setenv overwrite=1...%s\n",getenv("NAME"));
    unsetenv("NAME");
    clearenv();
    execl("./myenv","myenv",NULL);    
    return 0;
}
