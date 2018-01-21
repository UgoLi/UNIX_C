#include <stdio.h>
#include "ll.h"
int main(int argc,char *argv[]){
    //打印访问的文件元属性
	print(argv[1]);
    struct stat data = {};
    int f = stat(argv[1],&data);
    if(f == -1){
        perror("stat");
        return ;
    }
	//如果是目录，调用访问目录函数(Dir)
    if (/*(data.st_mode&S_IFMT) == S_IFDIR*/S_ISDIR(data.st_mode)){
        Dir(argv[1]);
    }
    return 0;
}
