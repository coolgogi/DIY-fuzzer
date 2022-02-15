#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int
main(int argc, char * argv[]){

    int rt = 0;
    pid_t child_pid;
    child_pid = fork();

    if(child_pid == 0){
        if(!execl(argv[1],argv[2],(char *) NULL)){
            /*
                fail case
                freopen();
            */
           
        }
		
        /*
            timeout case
        */
       
    }else{
        /*
            pass case
        */
        wait(0);
        rt = 1;
       
    }

	printf("return : %d\n", rt);
	return 0;

}
