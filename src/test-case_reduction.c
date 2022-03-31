#include <stdio.h>
#include <stdlib.h>
#include <strlen.h>
#include <dirent.h> 
#include <sys/stat.h>

int find_all_branch (char *, int) ;

int
main (int argc, char * argv[]) {
	
	if (argc < 4) {
		fprintf(stderr, "invalid arguments\n") ;
		exit(EXIT_FAILURE) ;
	}

	if (access(argv[1], F_OK) != 0) {
		fprintf(stderr, "Cannot access to input directory\n") ;
		exit(EXIT_FAILURE) ;
	}
	if (access(argv[2], F_OK) != 0) {
		fprintf(stderr, "Cannot access to output directory\n") ;
		exit(EXIT_FAILURE) ;
	}
	
	char * inputDir_path = (char *) malloc (strlen(argv[1]) ;
	char * bcovDir_path = (char *) malloc (strlen(argv[2]) ;
	
	int total = atoi(argv[3]) ;
	int n =	find_all_branch(bcovDir_path, total) ;



}


int
find_all_branch (char * bcovDir_path, int total) {

	DIR * dir ;
	struct dirent * dir_info ;	
	int branch[total + 1] ; 
	memset(branch, 0, sizeof(int) * (total + 1)) ;
	dir = opendir(bcovDir_path) ;
	
	if (dir == NULL) {
		perror("In find_all_branch function") ;
		return EXIT_FAILURE ;
	}
	
	while ((dir_info = readdir(dir))) {
		char * bcovFile_path = (char *) malloc (strlen(bcovDir_path) + strlen(dir_info->d_name) + 1) ;	
		strcpy(bcovFile_path, bcovDir_path) ;
		strcat(bcovFile_path, dir_info->d_name) ;

		FILE * fp = fopen(bcovFile_path, "r") ;
		struct stat st ;

		while (


	}
	

}
