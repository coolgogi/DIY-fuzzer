#include <stdio.h>
#include <stdlib.h>
#include "runner.h"

int
main(int argc, char * argv[]) {

    if(argc != 3)
    {
        printf("need more arguments\n");
        return 0;
    }    

    int result = runner(argv[1], argv[2]);
    if(result == 1)
    {
        /*
        pass case
        */
    }
    else if(result == 0)
    {
        /*
        timeout case
        */
    }
    else if(result == -1)
    {
        /*
        other fail case
        */
    }

}