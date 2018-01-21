/*************************************************************************
	> File Name: t_strcpy.c
	> Author:UgoLi 
	> Mail: 2653920896@qq.com
	> Created Time: 2017年07月25日 星期二 18时32分49秒
 ************************************************************************/

#include<stdio.h>
#include<sys/mman.h>

/*调用函数提供dest内存*/
char *t_strcpy(char *dest,const char *sour){
    int i=0;
    while(1){
        if(*(sour+i)=='\0'){
            *(dest+i)='\0';
            break;
        }
        *(dest+i)=*(sour+i);
        i++;
    }
    return dest;
}
/*被调用函数手动获取内存映射，注:malloc也是系统自动分配虚拟内存*/
char *t_strcpy_mmap(char* dest,const char* sour){
    int i=0;
    /*手动映射虚拟内存空间*/
    dest=mmap(NULL,1/*1x4k*/,PROT_EXEC|PROT_WRITE,MAP_PRIVATE|MAP_ANONYMOUS,-1,0);
    if(dest==MAP_FAILED){
        do{
            perror("mmap");
            return (void *)-1;
        }while(0);
    }
    while(1){
        if(*(sour+i)=='\0'){
            *(dest+i)='\0';
            break;
        }
        *(dest+i)=*(sour+i);
        i++;
    }
    return dest;
}


int main(void){
    char *sour="hello world";
    /*系统自动为dest分配虚拟内存*/
    char dest[128]={0};
    /*用调用函数手动分配内存--映射*/
    char *dest_1=NULL;
    printf("%s\n",t_strcpy(dest,sour));
    printf("%p\n",t_strcpy);
    printf("%s\n",t_strcpy_mmap(dest_1,sour));
    printf("%p\n",t_strcpy_mmap);
    munmap(dest_1,1);
    return 0;
}







