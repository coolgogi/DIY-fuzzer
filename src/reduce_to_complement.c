#include "../include/runner.h"
#include "../include/ddmin.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <unistd.h>
#include <limits.h>
#include <math.h>

char * 
reduce_to_complement(char * executeFile_path, char * input_file_path, int n) {
	
	struct stat st;
	stat(input_file_path, &st);
	int size = (int) ceil((double)st.st_size / n);

	char * subcomplement = (char *) malloc (21);
	char * substring = (char *) malloc (21);
	FILE * read_file;

	for (int i = 0 ; i < n ; i ++) {
		sprintf(subcomplement, "output/ddmin-%d", i);

		FILE * write_file = fopen(subcomplement, "w+");

		for (int j = 0 ; j < n ; j ++) {
			if (i == j) 
				continue;
			
			sprintf(substring, "output/ddmin%d", j);
			read_file = fopen(substring, "r");

			unsigned char buf ;
			while (fread(&buf, 1, 1, read_file) == 1) {
				fwrite(&buf, 1, 1, write_file);
			}
			
			fclose(read_file);	
		}
		fclose(write_file);

		EXITCODE rt = runner(executeFile_path, subcomplement, "output/ddmin_output.txt");
		if (rt.code_num == 1) {
			free(substring);
			FILE * answer_file = fopen("output/dd_answer", "w+");
			FILE * failing_file = fopen(subcomplement, "r");
			unsigned char buf;
			while (fread(&buf, 1, 1, failing_file)) {
				fwrite(&buf, 1, 1, answer_file);	
			}
			fclose(failing_file);
			fclose(answer_file);
			return subcomplement;
	
		}
	}

	free(substring);
	free(subcomplement);
	
	return input_file_path;
}
