#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "filefind.h"

int 
main(int argc, char * argv[]){

    filefind("filefind.c");
    filefind("filefind.h");
    filefind("../runner.c");
    return 0;
}