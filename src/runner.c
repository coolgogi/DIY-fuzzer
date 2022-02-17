#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <time.h>
#include <sys/wait.h>
#include <signal.h>
#include "../include/runner.h"

EXITCODE *
runner (char * exec, char * input) {

    pid_t child_pid;
    EXITCODE * rt;
    rt = (EXITCODE *) malloc (sizeof(EXITCODE));
    
    child_pid = fork();

    if (child_pid < 0) {
        rt->num = ERROR_FORK;
        strcpy(rt->msg, "fork() failed in runner");
        return rt;
    }
    else if (child_pid == 0) {
    
        int fp = open(input, O_RDONLY);

        if (dup2(fp, STDIN_FILENO) == -1) {
            rt->num = ERROR_DUP2;
            strcpy(rt->msg, "input dup2 error in runner");
            return rt;
        }

        if (execl(exec,0) == -1) {
            
            rt->num = 1;
            strcpy(rt->msg, "execl error in runner");
            return rt;
        }
        // close(fp); ??
    }
    else {
        time_t start = time(0);
        time_t cur = time(0);
        
        int status ;
        while (1) {
            if (cur - start >= 10) {
                kill(child_pid, SIGKILL);
            }

            if (waitpid(0, &status, WNOHANG) != 0) {
                break;
            }
            
            cur = time(0);
        }

        rt->num = status;
        switch (status)
        {
            case 0:
                strcpy(rt->msg, "PASS");
                break;
            
            case 9:
                strcpy(rt->msg, "TIMEOUT");
                break;

            case 11:
                strcpy(rt->msg, "SEGMENTATION FAULT");
                break;

            default:
                break;
        }
        
        int fp2 = open("../test/output/output.txt", O_WRONLY, 0);
        write(fp2, rt->msg, 101);
        close(fp2);
        return rt;
    }
    return rt;
}
