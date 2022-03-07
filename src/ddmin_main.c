#include <stdio.h>
#include <stdlib.h>
#include "../include/runner.h"

int
main (int argc, char * argv[]) {

	if (argc != 4) {
		fprintf(stderr, "invalid arguments");
		exit(EXIT_FAILURE);
	}

	EXITCODE rt ;
	rt = runner(argv[1], argv[2], argv[3]);


	return 0;
}
