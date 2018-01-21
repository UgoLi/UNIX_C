/*************************************************************************
	> File Name: printf_color.h
	> Author: 
	> Mail: 
	> Created Time: 2017年07月10日 星期一 18时55分20秒
 ************************************************************************/

#ifndef _PRINTF_COLOR_H
#define _PRINTF_COLOR_H
/*
 *printf 颜色定义
 *2017.07.10
 *Author：UgoLi
 * */
#include<stdio.h>
#define NONE "\033[m"        //正常终端颜色
#define RED "\033[0;32;31m"  //红色
#define YELLOW "\033[1;31m" //黄色
#define GREEN "\033[0;32;32m"  //绿色
#define LIGHT_GREEN "\033[1;32m" //淡绿色
#define DARK_GRAY "\033[1;30m"  //暗灰色
#define CYAN "\033[0;36m"    //蓝绿色
#define LIGHT_CYAN "\033[1;36" //淡蓝绿色
/*#define PURPLE "\033[0;35m"    //紫色*/
#define LIGHT_PURPLE "\033[1;35m" //淡紫色
#define PURPLE "\033[1;33m"     //紫色
#define WHITE "\033[1;37m"    //粗体白色
//清除屏幕
#define CLEAR() printf("\033[2J")
//上移光标
#define MOVEUP(x) printf("\033[%dA",(x))
//下移光标
#define MOVEDOWN(x) printf("\033[%dB",(x))
//左移光标
#define MOVELEFT(y) printf("\033[%dD",(y))
//右移光标
#define MOVERIGHT(y) printf("\033[%dC",(y))
//定位光标
#define MOVETO(x,y) printf("\033[%d;%dH",(x),(y))
//光标复位
#define RESET_CURSOR() printf("\033[H")
//隐藏光标
#define HIDE_CURSOR() printf("\033[?25l")
//显示光标
#define SHOW_CURSOR() printf("\033[?25h")
//反显
#define HIGHT_LIGHT() printf("\033[7m")
#define UN_HIGHT_LIGHT() printf("\033[27m")
#endif
