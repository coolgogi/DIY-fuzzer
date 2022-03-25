#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <stdint.h>
#include <errno.h>
#include "../include/runner.h"
#include <dirent.h>


int
main (int argc, char * argv[]) {
	
	int bcov = 0 ;

	if (argc != 4 && argc != 5) {
		fprintf(stderr, "main.c line 16 : invalid argument") ;
        	exit(EXIT_FAILURE) ;
	}
	else if (argc == 5) {
		if (strcmp(argv[4], "bcov")) { 
			bcov = 1 ;	
		}
		else {
			fprintf(stderr, "main.c line 25 : invalid arguments");
			exit(EXIT_FAILURE) ;	
		}
	}

	char * executeFile_path = (char *) malloc (strlen(argv[1]));
	char * inputDir_path = (char *) malloc (strlen(argv[2]));
	char * outputFile_path = (char *) malloc (strlen(argv[3]));
	strcpy(executeFile_path, argv[1]);
	strcpy(inputDir_path, argv[2]);
	strcpy(outputFile_path, argv[3]);

	if (access(executeFile_path, X_OK) != 0) {
		fprintf(stderr, "target program is not executable\n");
		exit(EXIT_FAILURE);
	}

	if (access(inputDir_path, F_OK) != 0) {
		fprintf(stderr, "input directory path is not valid\n");
		exit(EXIT_FAILURE);
	}
	
   	int rt = read_exec_dir(executeFile_path, inputDir_path, outputFile_path) ;

	if (bcov == 1) {
		char * total_path = (char *) malloc (strlen(executeFile_path) + 5) ;
		strcpy(total_path, executeFile_path) ;
		strcat(total_path, ".bcov") ;
		
		uint32_t * buf = (uint32_t *) malloc (sizeof(uint32_t)) ;
		char PcDescr[512] ;
		
		int max = 0 ;
		FILE * fp = fopen(total_path, "r") ;
		while (fread(buf, 1, sizeof(uint32_t), fp) == sizeof(uint32_t)) {
			fread(PcDescr, 1, 512, fp) ;
			if (*buf > max) {
				max = *buf ;
			}
		}

		rewind(fp) ;
		
		int num_of_branch[max + 1] ;	
		memset(num_of_branch, 0, sizeof(int) * (max + 1)) ;
		char * path_of_branch[max + 1] ;
		
		while (fread(buf, 1, sizeof(uint32_t), fp) == sizeof(uint32_t)) {
			fread(PcDescr, 1, 512, fp) ;	
			int index = *buf ;
			if (num_of_branch[index] == 0) {
				num_of_branch[index] = 1 ;
				path_of_branch[index] = (char *) malloc (512);
				strcpy(path_of_branch[index] , PcDescr) ;
				
			}
			
		
		}
		printf("covered branches:\n");
		for (int i = 0 ; i < max + 1 ; i ++) {
			if(num_of_branch[i] == 1) {
				printf("%s\n", path_of_branch[i]) ;
				free(path_of_branch[i]);
			}	
		}
		
		free(buf);
		free(total_path);

	}
	free(outputFile_path);
	free(inputDir_path);
	free(executeFile_path);
	return 0 ;
}
