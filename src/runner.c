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
        int status ;
        // sigtimedwait isn't in signal.h
        // sigset_t set;
        // sigemptyset(&set);
        // sigaddset(&set, SIGKILL);
        
        // struct timespec to;
        // to.tv_sec = 10 ;
        // to.tv_nsec = 0 ;
        // status = sigtimedwait(&set,NULL,&to);
        
        time_t start = time(0);
        time_t cur = time(0);
    
        while (1) {
            if (cur - start >= 10) {
                
                kill(child_pid, SIGKILL);
            }

            if (waitpid(0, &status, WNOHANG) != 0) {

                break;
            }
            
            cur = time(0);
        }
        // waitpid(0, &status, WNOHANG);
        // alarm(10);
        // pause();
        // if (kill(child_pid, SIGKILL) != 0) {
        //     fprintf(stderr, "timeout case\n");
        // }
        // waitpid(0, &status, WNOHANG);

        if (status == 0) {
            rt.valid = VALID;
        }
        else {
            rt.valid = INVALID;
        }
        rt.code_num = status;
        return rt;
    
    }
    return rt;
}
