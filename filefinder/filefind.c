#include <stdio.h>

void
filefind(char * path){

    if(fopen(path, "r")){
        printf("file exists\n");
    }else{
        printf("file not exists\n");
    }

}