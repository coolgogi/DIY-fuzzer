#include <stdio.h>
#include <stdlib.h>
#include "../include/runner.h"
#include "../include/ddmin.h"
#include <errno.h>
#include <unistd.h>
#include <limits.h>
#include <sys/stat.h>

int
main (int argc, char * argv[]) {

	if (argc != 3) {
		fprintf(stderr, "invalid arguments");
		exit(EXIT_FAILURE);
	}

	if (access(argv[1], X_OK) == -1) {
		perror("");
		exit(errno);
	}

	if (access(argv[2], R_OK) == -1) {
		perror("");
		exit(errno);
	}

	char * rt = ddmin(argv[1], argv[2]);
	printf("result file path : %s\n", rt);
}
