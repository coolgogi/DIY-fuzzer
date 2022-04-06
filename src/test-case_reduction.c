#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h> 
#include <sys/types.h>
#include <sys/stat.h>
#include <stdint.h>
#include <unistd.h>

int find_number_of_covered_branch (char *, int) ;
void make_SA (char *, char *, int, int) ;

int
main (int argc, char * argv[]) {
	
	if (argc < 4) {
		fprintf(stderr, "invalid arguments\n") ;
		exit(EXIT_FAILURE) ;
	}

	if (access(argv[1], F_OK) != 0) {
		fprintf(stderr, "Cannot access to input directory\n") ;
		exit(EXIT_FAILURE) ;
	}
	if (access(argv[2], F_OK) != 0) {
		fprintf(stderr, "Cannot access to output directory\n") ;
		exit(EXIT_FAILURE) ;
	}
	
	char * inputDir_path = (char *) malloc (strlen(argv[1]) + 1) ;
	char * bcovDir_path = (char *) malloc (strlen(argv[2]) + 1) ;
	strcpy(inputDir_path, argv[1]) ;
	strcpy(bcovDir_path, argv[2]) ;

	int total = atoi(argv[3]) ;
	int n =	find_number_of_covered_branch(bcovDir_path, total) ;
	
	make_SA(inputDir_path, bcovDir_path, total, n) ;

	free(bcovDir_path) ;
	free(inputDir_path) ;
	return 0 ; 
}


int
find_number_of_covered_branch (char * bcovDir_path, int total) {

	DIR * dir ;
	struct dirent * dir_info ;	
	int branch[total + 1] ; 
	int rt = 0 ;
	memset(branch, 0, sizeof(int) * (total + 1)) ;
	dir = opendir(bcovDir_path) ;
	
	if (dir == NULL) {
		perror("In find_all_branch function") ;
		return EXIT_FAILURE ;
	}
	
	while ((dir_info = readdir(dir))) {
		
		if (dir_info ->d_name[0] == '.')
			continue ;

		if (dir_info->d_type == DT_DIR) 
			continue ;
		

		char * bcovFile_path = (char *) malloc (strlen(bcovDir_path) + strlen(dir_info->d_name) + 1) ;	
		strcpy(bcovFile_path, bcovDir_path) ;
		strcat(bcovFile_path, dir_info->d_name) ;

		struct stat st ;
		stat(bcovFile_path, &st) ;
			
		unsigned int file_size = st.st_size ;

		FILE * bcov_ptr = fopen(bcovFile_path, "r") ;
		
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
			
			branch[*buf] ++ ;
		}

		free(PcDescr) ;
		free(size) ;
		free(buf) ;		
		fclose(bcov_ptr) ;
		free(bcovFile_path) ;
	}

	for (int i = 1 ; i < total + 1 ; i ++) {
		if (branch[i] > 0)
			rt++ ;
	}

	closedir(dir) ;

	return rt ;
}

void
make_SA (char * inputDir_path, char * outputDir_path, int total, int n) {
	
	int covered[total + 1] ;
	memset(covered, 0, sizeof(int) * (total + 1)) ;

	int covered_branch = 0 ; 

	DIR * dir ;
	struct dirent * dir_info ;
	dir = opendir(outputDir_path) ;
	
	char * SA_dir_path = (char *) malloc (strlen(outputDir_path) + 4) ;
	strcpy(SA_dir_path, outputDir_path) ;
	strcat(SA_dir_path, "SA/") ;

	while ((dir_info = readdir(dir))) {
		
		if (dir_info->d_name[0] == '.')
			continue ;

		if (dir_info->d_type == DT_DIR)
			continue ;
	
		int tp_branch[total + 1] ;
		memset(tp_branch, 0, sizeof(int) * (total + 1)) ;

		char * bcov_file = (char *) malloc (strlen(outputDir_path) + strlen(dir_info->d_name) + 1) ;
		strcpy(bcov_file, outputDir_path) ;
		strcat(bcov_file, dir_info->d_name) ;
		
		FILE * bcov_ptr = fopen(bcov_file, "r") ;

		struct stat st ;
		stat(bcov_file, &st) ;

		unsigned int file_size = st.st_size ;

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

			tp_branch[*buf] ++ ;

		}
		
		char * ch = (char *) malloc (sizeof(char)) ;
		fread(ch, 1, sizeof(char), bcov_ptr) ;
		int save = 0 ;
		
		for (int i = 1 ; i < total + 1 ; i ++) {
			if (tp_branch[i] > 0) {
				if (covered[i] == 0) {
					save = 1 ;
					covered_branch++ ;
				}
				covered[i] = 1 ;
			}
		}
		
		printf("1\n") ;
		if (save == 1) {
			printf("2\n") ;
			char * read_file_path = (char *) malloc (strlen(inputDir_path) + strlen(dir_info->d_name)) ;	
			strcpy(read_file_path, inputDir_path) ;
			strncat(read_file_path, dir_info->d_name, strlen(dir_info->d_name) - 5) ;

			char * write_file_path = (char *) malloc (strlen(outputDir_path) + 3 + strlen(dir_info->d_name)) ;	
			strcpy(write_file_path, outputDir_path) ;
			strcat(write_file_path, "SA/") ;
			strncat(read_file_path, dir_info->d_name, strlen(dir_info->d_name) - 5) ;
			
			FILE * read_fp = fopen(read_file_path, "r") ;
			FILE * write_fp = fopen(write_file_path, "w+") ;

			char * buf = (char *) malloc (sizeof(char)) ;
			while (fread(buf, 1, 1, read_fp) > 0) {
				fwrite(buf, 1, 1, write_fp) ;
			}
			free(buf) ;
		}

		if (covered_branch >= n) {
			break ;
		}
		
	}

	closedir(dir) ;
}

