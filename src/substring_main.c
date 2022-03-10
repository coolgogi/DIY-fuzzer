#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <unistd.h>
#include <limits.h>
#include "../include/ddmin.h"
#include "../include/runner.h"

int
main (int argc, char * argv[]) {

    if (argc != 3) {
        fprintf(stderr, "invalid arguments");
    }

    if (access(argv[1], X_OK) == -1) {
        perror("");
        exit(errno);
    }

    char * s = reduce_to_substring("../bin/jsondump", argv[2], 2);
    
    printf("%s\n", s);
    
    return 0;
}