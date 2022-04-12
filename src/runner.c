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
runner (char * exec, char * input, char * output) {

	pid_t child_pid;
    	EXITCODE rt;

    	rt.valid = UNRESOLVED;

   	child_pid = fork();
	
    	if (child_pid < 0) {
        	rt.code_num = errno;
    	}
    	else if (child_pid == 0) {
		
		char * total_path = (char *) malloc (strlen(exec) + 6);
		strcpy(total_path, exec);
		strcat(total_path, ".bcov");
	
		int fp[3] ;
		mode_t mode = S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP | S_IROTH ;
        	fp[0] = open(input, O_RDONLY);
		fp[1] = open(output, O_CREAT | O_APPEND | O_WRONLY, mode);
		fp[2] = open(total_path, O_CREAT | O_APPEND | O_WRONLY, mode);
		free(total_path);
		
		if (dup2(fp[0], STDIN_FILENO) == -1) {
			fprintf(stderr, "STDIN dup2 error in runner\n");
     		    	rt.code_num = errno;	
		    	exit(errno);
        	} 
	        if (dup2(fp[1], BCOV_FILENO) == -1) {
			fprintf(stderr, "BCOV FILE dup2 error in runner\n");
 	           	rt.code_num = errno;
	           	exit(errno);
     		}
		if (dup2(fp[2], TOTAL_FILENO) == -1) {
			fprintf(stderr, "TOTAL FILE dup2 error in runner\n");
			rt.code_num = errno;
			exit(errno);
		}
		fprintf(stderr, "pid : %d\n", getpid()) ;
//		if (execl(exec, exec, input, 0x0) == -1) {	        
//		if (execl(exec, exec, "--recover", "--postvalid", input, 0x0) == -1) {
		if (execl(exec, exec, "--maxmem", "5", input, 0x0) == -1) {
			perror("runner : ");
       		     	rt.code_num = errno;  
	            	exit(errno);  
		}
			
        	close(fp[0]);
        	close(fp[1]);
		close(fp[2]);

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
	rt.child_pid = child_pid ;

    	return rt;
}
