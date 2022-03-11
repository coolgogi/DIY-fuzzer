#include <stdio.h>
#include <stdlib.h>
#include "../include/runner.h"
#include "../include/ddmin.h"
#include <errno.h>
#include <unistd.h>
#include <limits.h>
#include <sys/stat.h>
#include <string.h>

char *
ddmin (char * execute_file_path, char * input_file_path) {

	int n = 2;
	int file_size;
	char * current_file_path = (char *) malloc (sizeof(char) * PATH_MAX);
	strcpy(current_file_path, input_file_path);
    char * result_file_path;
	struct stat st;

	do {
		printf("num : %d\n",n);
		stat(current_file_path, &st);
		file_size = st.st_size;
		if (n > file_size) {
			n = file_size;
		}
        
		char ** substrings = split(current_file_path, n);

		result_file_path = reduce_to_substring(execute_file_path, current_file_path, substrings, n);
		if (strcmp(current_file_path, result_file_path) != 0) {
			strcpy(current_file_path, result_file_path);
			n = 2;
			free(result_file_path);
		}
		else {
			
			result_file_path = reduce_to_complement(execute_file_path, current_file_path, substrings, n);
			printf("result of complement : %s\n", result_file_path);
			if (strcmp(current_file_path, result_file_path) != 0) {
				strcpy(current_file_path, result_file_path);
				n = 2;
				free(result_file_path);
			}
			else {
				n = n * 2;
			}
		}
		// for (int i = 0 ; i < n ; i ++) {
		// 	free(substrings[i]);
		// }
		
		free(substrings);
	} 
    while (file_size > 1 && file_size != n * 2);
	return current_file_path;
}
