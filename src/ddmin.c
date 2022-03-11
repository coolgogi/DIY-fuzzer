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
	int size ;
	char * s = (char *) malloc (sizeof(char) * PATH_MAX);
	strcpy(s, input_file_path);
    char * result_file_path ;
	struct stat st;
	char ** ss ;

	do {
		printf("num : %d\n",n);
		stat(s, &st);
		size = st.st_size;
		if (n > size) {
			n = size ;
		}
        
		result_file_path = reduce_to_substring(execute_file_path, s, n);
		if (strcmp(s, result_file_path) != 0) {
			strcpy(s, result_file_path);
			n = 2 ;
			free(result_file_path);
		}
		else {
        
			result_file_path = reduce_to_complement(execute_file_path, s, n);
			if (strcmp(s, result_file_path) != 0) {
				strcpy(s, result_file_path);
				n = 2;
				free(result_file_path);
			}
			else {
				n = n * 2;
			}
		}
		printf("result : %s\n", result_file_path);
	} 
    while (size > 1 && size != n * 2) ;
	return s;
}
