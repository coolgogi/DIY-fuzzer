#include <stdio.h>
#include <stdlib.h>
#include "../include/runner.h"
#include <errno.h>
#include <unistd.h>

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

	EXITCODE rt ;
	rt = runner(argv[1], argv[2], argv[3]);

	return 0;
}
