/*************************************************************************
	> File Name: array.c
	> Author: 
	> Mail: 
	> Created Time: 2017年06月29日 星期四 13时17分40秒
 ************************************************************************/

#include<stdio.h>
int main(){
    int p[3][3]={{1,2,3},{4,5,6},{7,8,9}};
    int (*p_p)[3]=p;
    int **arr=&p_p;
    printf("sizeof(p)=%ld,sizeof(p[0])=%ld,sizeof(*p_p)=%ld,sizeof(**arr)=%ld,\n\
           sizeof(*arr)=%ld,sizeof(arr)=%ld,sizeof(p_p)=%ld,\n\
           sizeof(&p)=%ld\n",
          sizeof(p),sizeof(p[0]),sizeof(*p_p),sizeof(**arr),sizeof(*arr),
          sizeof(arr),sizeof(p_p),sizeof(&p));
    printf("p[0]=%p,*(p[0]+1)=%d\n",p[0],*(p[0]+1));
    printf("p_p=%p,p_p+1=%p\n",p_p,p_p+1);
    printf("p[0]=%p,p[0]+1=%p\n",p[0],p[0]+1);
    printf("&p=%p,&p+1=%p\n",&p,&p+1);
    printf("p=%p,p+1=%p\n",p,p+1);
    
    printf("%p\n",arr+1);
    printf("%d\n",**arr);
    #if 1 
    printf("*((*arr+1)+1)=%d\n",*((*arr+1)+1));
    printf("*(*arr+1)=%d\n",*(*arr+1));
    printf("*(*(arr))=%d\n",*(*(arr)));
    #endif
    return 0;
}
