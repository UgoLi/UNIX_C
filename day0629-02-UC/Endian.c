/*************************************************************************
	> File Name: Endian.c
	> Author: 
	> Mail: 
	> Created Time: 2017年06月29日 星期四 15时50分44秒
 ************************************************************************/

#include<stdio.h>
int main(){
    unsigned int value=0x12345678;
    unsigned char *buff;
    buff=&value;
    printf("unsigned int size=%ld\n",sizeof(unsigned int));
    printf("int size=%ld\n",sizeof(int));
    printf("unsigned char size=%ld\n",sizeof(unsigned char));
    printf("char size=%ld\n",sizeof(char));
    //printf("buff[0]=%p,buff[3]=%p\n",&buff[0],&buff[3]);
    printf("*buff    =%x,adress=%p\n",*(buff+0),buff);
    printf("*(buff+1)=%x,adress=%p\n",*(buff+1),buff+1);
    printf("*(buff+2)=%x,adress=%p\n",*(buff+2),buff+2);
    printf("*(buff+3)=%x,adress=%p\n",*(buff+3),buff+3);
    if(*buff>*(buff+3)/*高位字节 */&&buff>(buff+3)/*高位地址*/){
        printf("主机字节序：大端\n");
    }
    else {
        printf("主机字节序：小端\n");
    }

    return 0;
}
