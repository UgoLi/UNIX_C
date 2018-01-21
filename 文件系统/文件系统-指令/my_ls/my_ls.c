/*************************************************************************
	> File Name: my_ls.c
	> Author:UgoLi 
	> Mail: 2653920896@qq.com
	> Created Time: 2017年08月09日 星期三 18时29分24秒
 ************************************************************************/

#include"my_ls.h"
int main(int argc,char *argv[]){
    /*1、检查文件是否存在*/
    char *entpath;
    if(argc>1)
        entpath=argv[argc-1];
    else
        entpath=".";
        
    if(access(entpath,F_OK)||access(entpath,R_OK)||access(entpath,X_OK)){
        perror("access");
        return -1;
    }
    /*2、根据类型处理文件*/
    int tab_cnt=0;
    deal(entpath,tab_cnt);
    return 0;
}
