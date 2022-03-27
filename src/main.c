#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <stdint.h>
#include <fcntl.h>
#include <errno.h>
#include <dirent.h>
#include "../include/runner.h"

int
main (int argc, char * argv[]) {
	
	int bcov = 0 ;
	int * rt;
	if (argc != 4 && argc != 5) {
		fprintf(stderr, "main.c line 17 : invalid arguments") ;
        	exit(EXIT_FAILURE) ;
	}
	else if (argc == 5) {
		if (strcmp(argv[4], "bcov")) { 
			bcov = 1 ;	
		}
		else {
			fprintf(stderr, "main.c line 25 : invalid argument");
			exit(EXIT_FAILURE) ;	
		}
	}

	char * inputDir_path = (char *) malloc (strlen(argv[1]));
	char * outputDir_path = (char *) malloc (strlen(argv[2]));
	char * executeFile_path = (char *) malloc (strlen(argv[3]));

	strcpy(inputDir_path, argv[1]);
	strcpy(outputDir_path, argv[2]);
	strcpy(executeFile_path, argv[3]);

	if (access(executeFile_path, X_OK) != 0) {
		fprintf(stderr, "main.c line 38 : target program is not executable\n");
		exit(EXIT_FAILURE);
	}

	if (access(inputDir_path, F_OK) != 0) {
		fprintf(stderr, "main.c line 43 : input directory path is not valid\n");
		exit(EXIT_FAILURE);
	}

	if (access(outputDir_path, F_OK) != 0) {
		fprintf(stderr, "main.c line 48 : output directory path is not valid\n");
		exit(EXIT_FAILURE);
	}

   	rt = read_exec_dir(executeFile_path, inputDir_path, outputDir_path) ;
	
	if (bcov == 1) {

		char * total_path = (char *) malloc (strlen(executeFile_path) + 5) ;
		strcpy(total_path, executeFile_path) ;
		strcat(total_path, ".bcov") ;
		
		uint32_t * total = (uint32_t *) malloc (sizeof(uint32_t)) ;
		uint32_t * buf = (uint32_t *) malloc (sizeof(uint32_t)) ;
		char PcDescr[512] ;
		
		int covered = 0 ;		
		int max = 0 ;
		FILE * fp = fopen(total_path, "r") ;
		
		fread(buf, 1, sizeof(uint32_t), fp) ;
		fread(total, 1, sizeof(uint32_t), fp) ;
		fread(PcDescr, 1, 512, fp) ;

		int num_of_branch = *total + 1; 
		int branch[num_of_branch] ;	
		memset(branch, 0, sizeof(int) * (num_of_branch)) ;
		char * path_of_branch[num_of_branch] ;
		
		for (int i = 1 ; i < num_of_branch ; i ++ ) {
			path_of_branch[i] = (char *) malloc (512);
		}

		do {

			uint32_t index = *buf ;
			if (index < num_of_branch){
				
				fprintf(stderr, "num of branch, index : %d, %d\n", num_of_branch - 1, index);
				branch[index]++  ;
				strcpy(path_of_branch[index] , PcDescr) ;
			}

			if (fread(buf, 1, sizeof(uint32_t), fp) != sizeof(uint32_t)) {
				break ;
			}
			if (fread(total, 1, sizeof(uint32_t), fp) != sizeof(uint32_t)) {
				break ;
			}
		}
		while (fread(PcDescr, 1, 512, fp) == 512) ;
			
		fprintf(stderr, "passing case : %d, failure case : %d\n", rt[0], rt[1]) ;

		for (int i = 1 ; i < num_of_branch ; i ++) {
			if (branch[i] != 0) {
				fprintf(stderr, "%d, %s\n", i, path_of_branch[i]) ;
				free(path_of_branch[i]) ;
				covered++ ;
			}	
		}

		fprintf(stderr, "coverage : %.2lf(%d / %d)\n", (double) covered / (double) (num_of_branch - 1), covered, num_of_branch - 1);
		free(buf) ;
		free(total) ;
		free(total_path) ;

	}
	free(outputDir_path);
	free(inputDir_path);
	free(executeFile_path);
	return 0 ;
}
