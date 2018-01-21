/*************************************************************************
	> File Name: my_ls.h
	> Author:UgoLi 
	> Mail: 2653920896@qq.com
	> Created Time: 2017年08月09日 星期三 18时43分22秒
 ************************************************************************/

#ifndef _MY_LS_H
#define _MY_LS_H
#include <stdio.h>
#include <pwd.h>
#include <grp.h>
#include <time.h>
#include <unistd.h>
#include <dirent.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <string.h>
#include "printf_color.h"
typedef char f_type;
typedef struct fatime{
    char *week;
    char *month;
    int day;
    int h;
    int m;
    int s;
    unsigned int year;
}fatime;
void deal(const char*,int);

#endif
