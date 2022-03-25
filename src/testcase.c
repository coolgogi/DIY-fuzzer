#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../include/runner.h"

int
main (int argc, char * argv[]) {
	
	if (argc < 4) {
		fprintf(stderr, "invalid argument\n") ;
		exit(EXIT_FAILURE) ;
	}

	EXITCODE rt = runner(argv[1], argv[2], argv[3]) ;

	fprintf(stderr, "exitcode is %d, valid is %d\n", rt.code_num, rt.valid);

	
	return 0;
}
