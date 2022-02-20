#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "../include/runner.h"

int
main (int argc, char * argv[]) {

    if (argc != 4) {
        fprintf(stderr, "invalid arguments\n");
        exit(SIGILL);
    }

    if (access(argv[1], X_OK) == -1) {
        fprintf(stderr, "Cannot access to the argv[1]\n");
        exit(SIGILL);
    }
    if (access(argv[2], R_OK) == -1) {
        fprintf(stderr, "Cannot access to the argv[2]\n");
        exit(SIGILL);
    }
    if (access(argv[3], W_OK) == -1) {
        fprintf(stderr, "Cannot access to the argv[3]\n");
        exit(SIGILL);
    }


    EXITCODE result ;
    result = runner(argv[1], argv[2], argv[3]) ;

    if (result.valid == 0) {
        fprintf(stderr, "Vaild and ");
    }
    else {
        fprintf(stderr, "Invalid and ");
    }

    if (result.code_num == ERROR_EXECL) {
       fprintf(stderr, "Error occured in execl function\n");
    }
    else if (result.code_num == ERROR_DUP2) {
        fprintf(stderr, "Error occured in dup2 function\n");
    }
    else if (result.code_num == ERROR_FORK) {
        fprintf(stderr, "Error occured in fork function\n");
    }
    else if (result.code_num == PASS) {
        fprintf(stderr, "Passing case\n");
    }
    else if (result.code_num == FAIL) {
        fprintf(stderr, "Failing case\n");
    }
    else if (result.code_num == TIMEOUT) {
        fprintf(stderr, "Timeout case\n");
    }
    else if (result.code_num == SEGV) {
        fprintf(stderr, "Segfault case\n");
    }

    return 0;
}