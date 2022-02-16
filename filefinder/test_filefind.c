#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "filefind.h"

int 
main(int argc, char * argv[]){

    if(argc != 2){
        printf("error\n");
        return 0;
    }
    
    filefind(argv[1]);
    return 0;
}