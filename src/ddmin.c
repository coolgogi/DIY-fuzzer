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
    char * result_file_path ;
	struct stat st;
	char ** ss ;

	do {
		stat(input_file_path, &st);
		size = st.st_size;
        printf("n : %d\npath : %s\n", n, input_file_path);
		if (n > size) {
			n = size ;
		}
        
		result_file_path = reduce_to_substring(execute_file_path, input_file_path, n);
        
		if (strcmp(input_file_path, result_file_path) != 0) {
			strcpy(input_file_path, result_file_path);
			n = 2 ;
		}
		else {
        
			result_file_path = reduce_to_complement(execute_file_path, input_file_path, n);
    
			if (strcmp(input_file_path, result_file_path) != 0) {
				strcpy(input_file_path, result_file_path);
				n = 2;
			}
			else {
				n = n * 2;
			}
		}
	} 
    while (size > 1 && size != n * 2) ;
	return input_file_path;
}
