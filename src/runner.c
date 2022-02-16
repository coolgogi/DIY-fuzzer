#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

int
runner(char * exec, char * input)
{

    int rt = 0;
    int fd[2];
    pid_t child_pid;

    if(pipe(fd) == -1)
    {
        printf("pipe Failed\n");
        return -1;
    }
    
    child_pid = fork();

    if(child_pid < 0)
    {
        printf("fork() failed\n");
        return -1;
    }
    else if(child_pid == 0)
    {
        freopen(input, "r", stdin);

        close(fd[0]);
        if(!execl(exec,0))
        {
            /*
                fail case
                freopen();
            */
           char msg[100] = "file failed";
           write(fd[1], msg, strlen(msg) + 1 );
           close(fd[1]);
        }
    }
    else
    {
        char msg[101];
        msg[0] = '\n';
        close(fd[1]);
        wait(0);

        if(read(fd[0], msg, 101)== -1)
        {
            /*
                pass case
            */
           printf("pass case\n");
        }
        else if(msg[0] == 'f')
        {
            /*
            fail case
            */
           printf("fail case\n");
        }
        close(fd[0]);

        /*
            timeout case
            rt = 0;
        */ 
        
    }
    return 0;
}
