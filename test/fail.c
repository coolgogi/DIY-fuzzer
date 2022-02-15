#include <stdio.h>

int
main(int argc, char *argv[]){

    printf("argv[%d] is %s\n", argc+1, argv[argc+1]);
    return 0;
}