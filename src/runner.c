#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <time.h>
#include <sys/wait.h>
#include <signal.h>
#include "../include/runner.h"


EXITCODE
runner (char * exec, char * input, char * output) {

    pid_t child_pid;
    EXITCODE rt;
    
    child_pid = fork();

    if (child_pid < 0) {
        rt.code_num = ERROR_FORK;
        rt.valid = INVALID;
        return rt;
    }
    else if (child_pid == 0) {
    
        int fp[2] ;
        fp[0] = open(input, O_RDONLY);
        fp[1] = open(output, O_WRONLY);

        if (dup2(fp[0], STDIN_FILENO) == -1) {
            
            _exit(ERROR_DUP2);
        }   
        if (dup2(fp[1], STDOUT_FILENO) == -1) {

            _exit(ERROR_DUP2);
        }
        if (dup2(fp[1], STDERR_FILENO) == -1) {

            _exit(ERROR_DUP2);
        }   
        
        if (execl(exec,0) == -1) {
            
            close(fp[0]);
            close(fp[1]);
            _exit(ERROR_EXECL);
        }
        
    }
    else {
        pid_t w;
        int status ;
        time_t cur, start ;
        cur = time(0);
        start = time(0);

        while (cur - start < 10) {
            cur = time(0);
        }
        kill(child_pid, SIGKILL);
        w = waitpid(child_pid, &status, 0);
        if (w == -1) {
            _exit(ERROR_WAITPID);
        }

        rt.code_num = status;
        if (WIFEXITED(status)) {
            rt.valid = VALID;
        }
        else {
            rt.valid = INVALID;
        }

        return rt;
    
    }
    return rt;
}
