/*************************************************************************
	> File Name: grtopt.c
	> Author:UgoLi 
	> Mail: 2653920896@qq.com
	> Created Time: 2017年08月16日 星期三 09时08分58秒
 ************************************************************************/

#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>

int main(int argc,char **argv){
    int flags, opt;
    int nsecs, tfnd;

    nsecs = 0;
    tfnd = 0;
    flags = 0;
    while ((opt = getopt(argc, argv, "nt:")) != -1) {
        switch (opt) {
            case 'n':
                flags = 1;
                break;
            case 't':
                nsecs = atoi(optarg);
                tfnd = 1;
                break;
            default: /* '?' */
                fprintf(stderr, "Usage: %s [-t nsecs] [-n name]\n",argv[0]);
                exit(EXIT_FAILURE);
        }
    }
    printf("flags=%d; tfnd=%d; nsecs=%d; optind=%d\n",flags, tfnd, nsecs, optind);
    if (optind >= argc){
        fprintf(stderr, "Expected argument after options\n");
        exit(EXIT_FAILURE);           
    }
    printf("name argument = %s\n", argv[optind]);
    /* Other code omitted */
    exit(EXIT_SUCCESS);
}





