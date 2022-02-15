#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "../src/runner.h"

int
main(int argc, char * argv[]){
	
	int rt = 0;
	pid_t child_pid;
	child_pid = fork();

	if(child_pid == 0){
		execl("/usr/bin/gcc","gcc","test/fail.c","-o","file",(char *) NULL);
	}else{
		wait(0);
		rt = runner("./file","abc");
	}
	
	if(rt){
		printf("target program passes\n");
	}else{
		printf("target program fails\n");
	}

	return 0;
}
