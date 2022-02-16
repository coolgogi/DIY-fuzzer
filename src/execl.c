#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int
main(int argc, char * argv[]) {

    int rt = 0;
    pid_t child_pid;
    child_pid = fork();

    if(child_pid == 0) {
        if(!execl(argv[1],argv[2],(char *) NULL)){
            /*
                fail case
                freopen();
            */
            return rt;
        }
        return rt;
        /*
            timeout case
        */
       
    }
    else {
        int * status;
        /*
            pass case
        */
        wait(&status);
        rt = 1;
       
    }

	printf("return : %d\n", rt);
	return 0;

}
