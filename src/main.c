#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <stdint.h>
#include <fcntl.h>
#include <errno.h>
#include <dirent.h>
#include <sys/stat.h>
#include "../include/runner.h"

int
main (int argc, char * argv[]) {
	
	int bcov = 0 ;
	int num_of_branch;
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

   	num_of_branch = read_exec_dir(executeFile_path, inputDir_path, outputDir_path) ;
	
	int p_branch[num_of_branch + 1] ;
	int f_branch[num_of_branch + 1] ;
	memset(p_branch, 0, sizeof(int) * (num_of_branch + 1)) ;
	memset(f_branch, 0, sizeof(int) * (num_of_branch + 1)) ;

	if (bcov == 1) {
		
		DIR * dir ;
		struct dirent * dir_info ;
		dir = opendir(outputDir_path) ;

		int covered = 0 ;
		int rt[2] ;
		rt[0] = 0 ;
		rt[1] = 0 ;
		
		while ((dir_info = readdir(dir))) {
			
			if (dir_info->d_name[0] == '.')
				continue ;

			if (dir_info->d_type == DT_DIR)
				continue ;
			
			int tp_branch[num_of_branch + 1] ;
			memset(tp_branch, 0, sizeof(int) * (num_of_branch + 1)) ;
			
			char * bcov_file = (char *) malloc (strlen(outputDir_path) + strlen(dir_info->d_name)) ;
			strcpy(bcov_file, outputDir_path) ;
			strcat(bcov_file, dir_info->d_name) ;
		
			struct stat st ;
			stat(bcov_file, &st) ;

			unsigned int file_size = st.st_size ;
			int n = file_size / sizeof(uint32_t) ;

			FILE * bcov_ptr = fopen(bcov_file, "r") ;
			
			uint32_t * buf = (uint32_t *) malloc (sizeof(uint32_t)) ;
			char * ch = (char *) malloc (1) ;
			
			for (int i = 0 ; i < n ; i ++ ) {
				fread(buf, 1, sizeof(uint32_t), bcov_ptr) ;
				
				if (tp_branch[*buf] != 1) {
					tp_branch[*buf] = 1 ;
				}		
				
			}
			fread(ch, 1, 1, bcov_ptr) ;
			if (*ch == 'p') {
				rt[0] ++ ;
			}
			else if (*ch == 'f') {
				rt[1] ++ ;
			}
			for (int i = 1 ; i < num_of_branch + 1 ; i ++) {
				if (tp_branch[i] == 1) {

					if (*ch == 'p') {
						p_branch[i] ++ ;
					}
					else if (*ch == 'f') {
						f_branch[i] ++ ;
					}
				}
			}
			
			free(ch) ;
			free(buf) ;
			fclose(bcov_ptr) ;
			free(bcov_file) ;
			
		}

		for (int i = 1 ; i < num_of_branch + 1 ; i ++) {
			
			if ((p_branch[i] != 0)||(f_branch[i] != 0))
				covered++ ;

			fprintf(stderr, "%d : %d %d\n", i, p_branch[i], f_branch[i]) ;

		}
		fprintf(stderr, "coverage : %.2lf(%d / %d)\n", (double) covered / (double) num_of_branch, covered, num_of_branch);	
		fprintf(stderr, "passing case : %d, failing case : %d\n", rt[0], rt[1]) ;
	}
	free(outputDir_path);
	free(inputDir_path);
	free(executeFile_path);
	return 0 ;
}
