#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <time.h>
#include <sys/wait.h>
#include <signal.h>
#include <errno.h>
#include "../include/runner.h"


EXITCODE
rm_runner (char * target) {

	pid_t child_pid;
    	EXITCODE rt;

    	rt.valid = UNRESOLVED;

   	child_pid = fork();
	
    	if (child_pid < 0) {
        	rt.code_num = errno;
    	}
    	else if (child_pid == 0) {
		
		if (execl("/bin/rm", "/bin/rm", target, 0x0) == -1) {
	            	perror("rm_runner : ");
       	     		rt.code_num = errno;  
	           	exit(errno);  
        	}

	}
    	else {
        	pid_t w;
        	int status ;
        	time_t cur, start ;
        	cur = time(0);
       		start = time(0);

       		while (cur - start < 10) {
			w = waitpid(child_pid, &status, WNOHANG) ;
			if (w != 0)
				break ;
			cur = time(0) ;
	        }
	        if (cur - start >= 10) {
			kill(child_pid, SIGKILL);
        		w = waitpid(child_pid, &status, 0);
			rt.code_num = 9 ;
			return rt ;
		}
       
        	if (w == -1) {
            		perror("");
            		rt.code_num = errno;
            		return rt;
        	}

        	rt.code_num = WEXITSTATUS(status);
        	if (rt.code_num == EACCES) {
            		rt.valid = UNRESOLVED;
        	}
        	else if (rt.code_num == EBADF) {
            		rt.valid = UNRESOLVED;
        	}
        	else if (WIFEXITED(status)) {
            		rt.valid = VALID;
        	}
        	else {
            		rt.valid = INVALID;
        	}
		
    	}
    	return rt;
}
