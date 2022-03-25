#include <stdio.h>
#include <stdlib.h>

int
main (int argc, char * argv[]) {
	/*
	if (argc == 1) {
		fprintf(stderr, "branch.c : no arguments\n") ;
		return 0 ;
	}
	*/
	
	int n ;
	scanf("%d", &n);
	
	if ((n % 2) == 0) {
		if ((n % 3) == 0) {
			printf("line 18\n");
			return 0;
		}
		else {
			printf("line 22\n");
			return 0;
		}
	}
	else {
		if ((n % 3) == 0) {
			printf("line 28\n");
			return 0;
		}
		else {
			printf("line 32\n");
			return 0;
		}
	}

	return 0;
}
