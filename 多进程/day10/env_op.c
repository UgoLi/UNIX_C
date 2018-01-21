#include <stdio.h>
#include <stdlib.h>
int main(void){
    printf("%s\n",getenv("name"));
    putenv("CHINA=beijing");
    printf(" before...%s\n",getenv("CHINA"));
    setenv("CHINA","Nanjing",1);
    printf("after...%s\n",getenv("CHINA"));
    unsetenv("name");
    setenv("name","tarena",0);
    printf("%s\n",getenv("name"));
    return 0;
}
