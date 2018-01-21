#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(void){
    execl("./delay","delay",NULL);
    //system("./delay");
    return 0;
}
