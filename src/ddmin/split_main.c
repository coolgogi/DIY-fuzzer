#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include "../../include/ddmin.h"

int
main (int argc, char * argv[]) {

    if (argc != 3) {
        fprintf(stderr, "invalid arguments");
        return EXIT_FAILURE;
    }

    if (access(argv[1], R_OK) == -1) {
        perror("");
        return errno;
    }

    int n = atoi(argv[2]);
    char ** ss = split(argv[1], n);
    
    return 0;

}
