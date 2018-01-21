/*************************************************************************
	> File Name: color_test.c
	> Author: 
	> Mail: 
	> Created Time: 2017年07月10日 星期一 19时16分42秒
 ************************************************************************/

#include<stdio.h>
#include<printf_color.h>
#include<time.h>
#include<stdlib.h>
#include<unistd.h>
int main(){
    srand(time(0));

        HIDE_CURSOR();
    while(1){
        int x=rand()%300;
        int y=rand()%300;
        //CLEAR();
        printf(RED);
        MOVETO(x,y);
        printf("       **    **        \n");
        MOVETO(x,y+1);
        printf("     *    **    *      \n");
        MOVETO(x,y+2);
        printf("     *          *      \n");
        MOVETO(x,y+3);
        printf("      *        *       \n");
        MOVETO(x,y+4);
        printf("        *    *         \n");
        MOVETO(x,y+5);
        printf("          **           \n");
        sleep(1);
        //CLEAR();
        printf(YELLOW);
        x=rand()%300;
        y=rand()%300;
        MOVETO(x,y);
        printf("       **    **        \n");
        MOVETO(x,y+1);
        printf("     *    **    *      \n");
        MOVETO(x,y+2);
        printf("     *          *      \n");
        MOVETO(x,y+3);
        printf("      *        *       \n");
        MOVETO(x,y+4);
        printf("        *    *         \n");
        MOVETO(x,y+5);
        printf("          **           \n");
        sleep(1);
        //CLEAR();
        printf(GREEN);
        x=rand()%300;
        y=rand()%300;
        MOVETO(x,y);
        printf("       **    **        \n");
        MOVETO(x,y+1);
        printf("     *    **    *      \n");
        MOVETO(x,y+2);
        printf("     *          *      \n");
        MOVETO(x,y+3);
        printf("      *        *       \n");
        MOVETO(x,y+4);
        printf("        *    *         \n");
        MOVETO(x,y+5);
        printf("          **           \n");
        sleep(1);
        //CLEAR();
        printf(CYAN);
        x=rand()%300;
        y=rand()%300;
        MOVETO(x,y);
        printf("       **    **        \n");
        MOVETO(x,y+1);
        printf("     *    **    *      \n");
        MOVETO(x,y+2);
        printf("     *          *      \n");
        MOVETO(x,y+3);
        printf("      *        *       \n");
        MOVETO(x,y+4);
        printf("        *    *         \n");
        MOVETO(x,y+5);
        printf("          **           \n");
        sleep(1);
        //CLEAR();
        printf(DARK_GRAY);
        x=rand()%300;
        y=rand()%300;
        MOVETO(x,y);
        printf("       **    **        \n");
        MOVETO(x,y+1);
        printf("     *    **    *      \n");
        MOVETO(x,y+2);
        printf("     *          *      \n");
        MOVETO(x,y+3);
        printf("      *        *       \n");
        MOVETO(x,y+4);
        printf("        *    *         \n");
        MOVETO(x,y+5);
        printf("          **           \n");
        sleep(1);
        //CLEAR();
        printf(PURPLE);
        x=rand()%300;
        y=rand()%300;
        MOVETO(x,y);
        printf("       **    **        \n");
        MOVETO(x,y+1);
        printf("     *    **    *      \n");
        MOVETO(x,y+2);
        printf("     *          *      \n");
        MOVETO(x,y+3);
        printf("      *        *       \n");
        MOVETO(x,y+4);
        printf("        *    *         \n");
        MOVETO(x,y+5);
        printf("          **           \n");
        sleep(1);
        //CLEAR();
        printf(WHITE);
        MOVETO(x,y);
        printf("       **    **        \n");
        MOVETO(x,y+1);
        printf("     *    **    *      \n");
        MOVETO(x,y+2);
        printf("     *          *      \n");
        MOVETO(x,y+3);
        printf("      *        *       \n");
        MOVETO(x,y+4);
        printf("        *    *         \n");
        MOVETO(x,y+5);
        printf("          **           \n");
        sleep(1);
    }
    return 0;
}
