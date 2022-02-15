#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int
runner(char * exec, char * input){
    
    int rt = 0;
    pid_t child_pid;
    child_pid = fork();

    if(child_pid == 0){
        if(!execl(exec,input,(char *) NULL)){
            /*
                fail case
                freopen();
            */
        }
        return rt;
       
    }else{
        /*
            pass case
            rt = 1;
        */
        /*
            timeout case
            rt = 0;
        */ 
        wait(0);
        rt = 1;
        return rt ;
    }

    return rt;

}

