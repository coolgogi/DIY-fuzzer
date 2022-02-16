#include <stdio.h>
#include <stdlib.h>
#include "../include/runner.h"

int
main(int argc, char * argv[]) 
{

    if(argc != 3)
    {
        printf("invalid argument\n");
        return 0;
    }    
    
    if( !fopen(argv[1], "r") )
    {
        printf("%s : file not exists\n", argv[1]);
        return 0;
    }
    if( !fopen(argv[2], "r") )
    {
        printf("%s : file not exists\n", argv[2]);
        return 0;
    }

    int result = runner(argv[1], argv[2]) ;

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

    return 0;
}