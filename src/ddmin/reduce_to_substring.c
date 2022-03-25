#include "../include/runner.h"
#include "../include/ddmin.h"
#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <string.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <math.h>
#include <unistd.h>

char *
reduce_to_substring (char * executeFile_path, char * input_file_path, int n) {

	struct stat st;
	stat(input_file_path, &st);
	int size = (int) ceil((double)st.st_size / n);

	char * substring = (char *) malloc (21);

	FILE * read_file = fopen(input_file_path, "r");
	if (read_file == NULL) {
		perror("reduce_to_substring : fopen NULL");
		exit(EXIT_FAILURE);
	}

	for (int i = 0 ; i < n ; i ++ ) {
		sprintf(substring, "output/ddmin%d", i);

		FILE * write_file = fopen(substring, "w+");

		for (int j = 0 ; j < size ; j ++) {
			unsigned char buf ;

			if (fread(&buf, 1, 1, read_file) != 1) {
				break;
			}
			fwrite(&buf, 1, 1, write_file);

		}

		fclose(write_file);

		EXITCODE rt = runner(executeFile_path, substring, "output/ddmin_output.txt");
		if (rt.code_num == 1) {
			FILE * answer_file = fopen("output/dd_answer", "w+");
			FILE * failing_file = fopen(substring, "r");
			unsigned char buf ;
			while (fread(&buf, 1, 1, failing_file)) {
				fwrite(&buf, 1, 1, answer_file);
			}
			fclose(failing_file);
			fclose(answer_file);
			return substring;
		}
	}

	free(substring);
	return input_file_path;
}
