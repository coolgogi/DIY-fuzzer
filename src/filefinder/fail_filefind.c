#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "filefind.h"

int 
main(int argc, char * argv[]){

    filefind("aaaa");
    filefind("runner.c");
    filefind("../filefind.h");
    return 0;
}