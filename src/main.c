#include <math.h>
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
	char mode = 'T' ;
	int timeout = 0 ;

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
	
	int * rt ;

	if (access(executeFile_path, X_OK) != 0) {
		fprintf(stderr, "main.c : target program is not executable\n");
		exit(EXIT_FAILURE);
	}

	if (access(inputDir_path, F_OK) != 0) {
		fprintf(stderr, "main.c : input directory path is not valid\n");
		exit(EXIT_FAILURE);
	}

	if (access(outputDir_path, F_OK) != 0) {
		fprintf(stderr, "main.c : output directory path is not valid\n");
	exit(EXIT_FAILURE);
	}

   	rt = read_exec_dir(executeFile_path, inputDir_path, outputDir_path, bcov) ;
	free(executeFile_path);
	free(inputDir_path);
	fprintf(stderr, "passed : %d\nfailed : %d\n", rt[0], rt[1]) ;	

      
	if (bcov == 1) {
		num_of_branch = rt[2] ;

		int p_branch[num_of_branch + 1] ;
		int f_branch[num_of_branch + 1] ;
		memset(p_branch, 0, sizeof(int) * (num_of_branch + 1)) ;
		memset(f_branch, 0, sizeof(int) * (num_of_branch + 1)) ;
	
		char * branch_path[num_of_branch + 1] ;
	
		for (int i = 1 ; i < num_of_branch + 1 ; i ++ ) {
			branch_path[i] = (char *) malloc (1024) ;
			memset(branch_path[i], 0, 1024) ;	
		}

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
			int n = file_size / (sizeof(uint32_t) + 1024)  ;

			FILE * bcov_ptr = fopen(bcov_file, "r") ;

			uint32_t * buf = (uint32_t *) malloc (sizeof(uint32_t)) ;
			uint32_t * size = (uint32_t *) malloc (sizeof(uint32_t)) ;
			char * PcDescr = (char *) malloc (1024) ;
			
			while (file_size > 1) {
				fread(buf, 1, sizeof(uint32_t), bcov_ptr) ;
				file_size = file_size - sizeof(uint32_t) ;
				fread(size, 1, sizeof(uint32_t), bcov_ptr) ;
				file_size = file_size - sizeof(uint32_t) ;
				fread(PcDescr, 1, *size, bcov_ptr) ;
				file_size = file_size - *size ;
				
				if (tp_branch[*buf] != 1) {
					tp_branch[*buf] = 1 ;
					strcpy(branch_path[*buf], PcDescr) ;
				}

			}

			free(PcDescr) ;
			free(size) ;
			free(buf) ;

			char * ch = (char *) malloc (1) ;
			fread(ch, 1, 1, bcov_ptr) ;
			if (*ch == 'p') {
				rt[0] ++ ;
			}
			else if (*ch == 't') {
				rt[1] ++ ;
				timeout ++ ;
			}
			else if (*ch == 'f') {
				rt[1] ++ ;
			}
			
			for (int i = 1 ; i < num_of_branch + 1 ; i ++) {
				if (tp_branch[i] == 1) {

					if (*ch == 'p') {
						p_branch[i] ++ ;
					}
					else  {	
						f_branch[i] ++ ;
					}
				}
			}
			
			free(bcov_file) ;
			free(ch) ;
			fclose(bcov_ptr) ;
			
		}
		
		fprintf(stderr, "\n") ;
		for (int i = 1 ; i < num_of_branch + 1 ; i ++) {
			if ((p_branch[i] != 0)||(f_branch[i] != 0))
				covered++ ;
		}
		
		fprintf(stderr, "coverage : %.2lf(%d / %d)\n", (double) covered / (double) num_of_branch, covered, num_of_branch);	
		fprintf(stderr, "passing case : %d, failing case : %d, timeout case : %d\n", rt[0], rt[1], timeout) ;
		
		double * sus ;
		double * con ;
		int * T_rank, * S_rank, * J_rank, * O_rank ;

		sus = calculate_sus('T', p_branch, f_branch, rt, num_of_branch) ;
		con = calculate_con('T', p_branch, f_branch, rt, num_of_branch) ;	
		T_rank = sorting_statement(num_of_branch, sus, con) ;	
		
		sus = calculate_sus('S', p_branch, f_branch, rt, num_of_branch) ;
		con = calculate_con('S', p_branch, f_branch, rt, num_of_branch) ;
		S_rank = sorting_statement(num_of_branch, sus, con) ;

		sus = calculate_sus('J', p_branch, f_branch, rt, num_of_branch) ;
		con = calculate_con('J', p_branch, f_branch, rt, num_of_branch) ;
		J_rank = sorting_statement(num_of_branch, sus, con) ;

		sus = calculate_sus('O', p_branch, f_branch, rt, num_of_branch) ;
		con = calculate_con('O', p_branch, f_branch, rt, num_of_branch) ;
		O_rank = sorting_statement(num_of_branch, sus, con) ;
		
		fprintf(stderr, "result\n") ;
		fprintf(stderr, "line : Tar SBI Jcd Och\n") ;
		for (int i = 1 ; i < num_of_branch + 1 ; i ++ ) { 
			fprintf(stderr, "%.3d  : %.3d %.3d %.3d %.3d\n", i, T_rank[i], S_rank[i], J_rank[i], O_rank[i]) ;
		}
		for (int i = 1 ; i < num_of_branch + 1 ; i ++ ) {
			fprintf(stderr, "%d : %d %d\n", i, p_branch[i], f_branch[i]) ;
		}
			
		free(sus) ;
		free(con) ;
		free(T_rank) ;	
		free(S_rank) ;	
		free(J_rank) ;	
		free(O_rank) ;	
		for (int i = 1 ; i < num_of_branch + 1 ; i ++) {
			free(branch_path[i]) ;
		}
	}

	free(outputDir_path);

	return 0 ;
}
