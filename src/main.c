#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include "../include/runner.h"
#include <dirent.h>


int
main (int argc, char * argv[]) {

    if (argc != 3) {
        fprintf(stderr, "invalid argument");
        exit(EXIT_FAILURE);
    }
    
    return read_exec_dir(argv[1], argv[2]);
    
}