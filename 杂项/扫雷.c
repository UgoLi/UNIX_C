/*************************************************************************
	> File Name: 扫雷.c
	> Author:UgoLi 
	> Mail: 2653920896@qq.com
	> Created Time: 2017年07月13日 星期四 12时31分56秒
 ************************************************************************/

#include<stdio.h>
#include<time.h>
#include<stdlib.h>
#include<printf_color.h>
int main(){
    srand(time(0));
    int level=0;
    int num=0;
    printf("输入地图级别：");
    scanf("%d",&level);
    printf("输入地雷数量：");
    scanf("%d",&num);
    int size=0;
    size=level+2;
    int map[size][size];
    int row,col;
    int cnt=0;
    for(row=0;row<size;row++){
        for(col=0;col<size;col++){
            map[row][col]=0;
        }
    }
    while(1){
        row=rand()%size;
        col=rand()%size;
        if(row>0&&col>0&&row<size-1&&col<size-1&&(map[row][col]!='X')){
            map[row][col]='X';
            cnt++;
            if(cnt>=num){
                break;
            }
        }
    }
    for(row=0;row<size;row++){
        for(col=0;col<size;col++){
            if(map[row][col]=='X'){
                int i,j;
                for(i=row-1;i<=row+1;i++){
                    for(j=col-1;j<=col+1;j++){
                        if(map[i][j]!='X'){
                            map[i][j]++;
                        }
                    }
                }
            }
        }
    }
    for(row=1;row<size-1;row++){
        for(col=1;col<size-1;col++){
            if(map[row][col]=='X'){
                printf(RED"x "NONE);
            }
            else{
                printf("%d ",map[row][col]);
            }
        }
        printf("\n");
    }
}
