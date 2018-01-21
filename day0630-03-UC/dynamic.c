/*************************************************************************
	> File Name: dynamic.c
	> Author: 
	> Mail: 
	> Created Time: 2017年07月03日 星期一 15时31分14秒
 ************************************************************************/

#include<stdio.h>
#include<dlfcn.h>
#include<sys/types.h>
#include<unistd.h>
int main(void){
    //加载动态库文件
    void *handle=dlopen("./tmath/libpmath.so",RTLD_NOW);
    if(!handle){
        //printf("failed...\n");
        printf("%s\n",dlerror());
        return -1;
    }
    printf("success...\n");
    //在动态库里查找symbol的地址
    void *p=dlsym(handle,"tsub");   //"tsub"函数的入口地址给p
    if (!p){
        printf("%s\n",dlerror());
        return -1;
    }
    printf("mem:%p pid:%d\n",p,getpid());
    getchar();
    typedef int (*fun_t)(int,int);
    fun_t q=p;
    printf("5-2=%d\n",q(5,2));
    //关闭动态库
    dlclose(handle);
    return 0;
}
