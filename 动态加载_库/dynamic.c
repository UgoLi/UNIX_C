/*************************************************************************
	> File Name: dynamic.c
	> Author:UgoLi 
	> Mail: 2653920896@qq.com
	> Created Time: 2017年07月25日 星期二 11时57分44秒
 ************************************************************************/

#include<stdio.h>
#include<dlfcn.h>
int main(void){
    //加载库
    void *handle=dlopen("./libpmath.so",RTLD_LAZY);
    if(!handle){
        printf("%s\n",dlerror());
        return -1;
    }
    printf("dynamic load successed..\n");
    printf("handle=%p\n",handle);
    //获取函数地址
    void *func_tmp=dlsym(handle,"padd");
    if(!func_tmp){
        printf("%s\n",dlerror());
        return -1;
    }
    printf("func_tmp=%p\n",func_tmp);
    //使用函数
    int (*func)(int,int )=func_tmp;
    printf("5+3=%d\n",func(5,3));
    //共享库加载减1,减为0关闭
    getchar();
    dlclose(handle);
    return 0;
}








