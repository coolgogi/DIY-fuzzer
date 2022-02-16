#include <stdio.h>

int
main(int argc, char *argv[]){

    printf("fail\n");
    int *p = NULL;
    *p = 1;
    return 0;
}