/*************************************************************************
	> File Name: datetime.c
	> Author:UgoLi 
	> Mail: 2653920896@qq.com
	> Created Time: 2017年08月02日 星期三 08时29分28秒
 ************************************************************************/

#include<stdio.h>
#include<time.h>
int main(){
    time_t now;
    now=time(NULL);
    printf("%s\n",ctime(&now));    
    return 0;
}
