#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <unistd.h>
#include <limits.h>
#include "../../include/ddmin.h"
#include "../../include/runner.h"

int
main (int argc, char * argv[]) {

    if (argc != 4) {
        fprintf(stderr, "invalid arguments");
    }

    if (access(argv[1], X_OK) == -1) {
        perror("");
        exit(errno);
    }

    int n = atoi(argv[3]);

    char * s = reduce_to_substring(argv[1], argv[2], n);
    
    printf("%s\n", s);

    return 0;
}
