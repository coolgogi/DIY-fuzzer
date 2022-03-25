#include <stdio.h>
#include <stdlib.h>
#include "../../include/runner.h"
#include "../../include/ddmin.h"
#include <errno.h>
#include <unistd.h>
#include <limits.h>
#include <sys/stat.h>
#include <string.h>
#include <math.h>

char *
ddmin (char * executeFile_path, char * inputFile_path) {
	
	int n = 2 ;
	int file_size;
	char * current_file_path = (char *) malloc (strlen(inputFile_path));
	strcpy(current_file_path, inputFile_path);
     	char * result_file_path;
	struct stat st;

	do {
		stat(current_file_path, &st);
		file_size = st.st_size;
		if (n > file_size) {
			n = file_size;
		}
		fprintf(stderr, "num : %d\n",n);
        
		result_file_path = reduce_to_substring(executeFile_path, current_file_path, n);
		if (strcmp(current_file_path, result_file_path) != 0) {
			fprintf(stderr, "result of substring : %s\n", result_file_path);
			strcpy(current_file_path, result_file_path);
			n = 2;
			free(result_file_path);
			continue ;
		}
		
			
		result_file_path = reduce_to_complement(executeFile_path, current_file_path, n);
		if (strcmp(current_file_path, result_file_path) != 0) {
			fprintf(stderr, "result of complement : %s\n", result_file_path);
			strcpy(current_file_path, result_file_path);
			n = 2;
			free(result_file_path);
		}
		else {
			n = n * 2;
		}
	} 
    	while (file_size > 1 && file_size != n * 2);
	
	return current_file_path;
}
