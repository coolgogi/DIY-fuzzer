#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "../include/runner.h"

int
main (int argc, char * argv[]) {

    if (argc != 3) {
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

    EXITCODE * result ;
    result = (EXITCODE *) malloc (sizeof(EXITCODE));
    result = runner(argv[1], argv[2]) ;

    printf("%s\n", result->msg);    

    return 0;
}