#include <stdio.h>
#include <stdlib.h>
#include "../include/runner.h"
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <dirent.h>

int
main (int argc, char * argv[]) {
	
	if (argc != 4) {
		fprintf(stderr, "invalid input\n") ;
		exit(0) ;
	}
	
	char * inputDir = (char *) malloc (strlen(argv[1])) ;
	char * outputDir = (char *) malloc (strlen(argv[2])) ;
	char * targetDir = (char *) malloc (strlen(argv[3])) ;
	int * rt_branch ;


	strcpy(inputDir, argv[1]) ;
	strcpy(outputDir, argv[2]) ;
	strcpy(targetDir, argv[3]) ;	
	
		
	if (access(targetDir, X_OK) != 0) {
		fprintf(stderr, "sancov_main.c : target program isn't executable\n") ;
		exit(0) ;
	}

	if (access(inputDir, F_OK) != 0) {
		fprintf(stderr, "sancov_main.c : input directory isn't valid\n") ;
		exit(0) ;
	}

	if (access(outputDir, F_OK) != 0) {
		fprintf(stderr, "sancov_main.c : output directory isn't valid\n") ;
		exit(0) ;
	}
	
	rt_branch = exec_sancov_dir(targetDir, inputDir, outputDir, 1) ;
	
	printf("%d %d %d\n", rt_branch[0], rt_branch[1], rt_branch[2]) ;
/*	
	int num = 31484 ; 
	//num11539428 //a31484
	int p_branch[num + 1] ;
	int f_branch[num + 1] ;
	memset(p_branch, 0, sizeof(int) * (num + 1)) ;
	memset(f_branch, 0, sizeof(int) * (num + 1)) ;

	DIR * dir ;
	struct dirent * dir_info ;

	int covered = 0 ;
	int rt[2] ;
	rt[0] = 0 ;
	rt[1] = 0 ;
	
	char * pass_dir = (char *) malloc (sizeof(outputDir) + 6) ;
	char * fail_dir = (char *) malloc (sizeof(outputDir) + 6) ;
	strcpy(pass_dir, outputDir) ;
	strcat(pass_dir, "pass/") ;
	strcpy(fail_dir, outputDir) ;
	strcat(fail_dir, "fail/") ;

	dir = opendir(pass_dir) ;

	while ((dir_info = readdir(dir))) {
		
		if (dir_info->d_name[0] == '.')
			continue ;
		if (dir_info->d_type == DT_DIR)
			continue ;
		
		int tp_branch[num + 1] ;
		memset(tp_branch, 0, sizeof(int) * (num + 1)) ;

		char * file_path = (char *) malloc (strlen(pass_dir) + strlen(dir_info->d_name)) ;
		strcpy(file_path, pass_dir) ;
		strcat(file_path, dir_info->d_name) ;

		FILE * file_ptr = fopen(file_path, "r") ;
		
		char buf[20] ;
		memset(buf, 0, 20) ;

		while (!feof(file_ptr)) {
			fgets(buf, 20, file_ptr) ;
			long int tp = strtol(buf, NULL, 16) ;
			if (tp > num)
				continue ;
			p_branch[tp] ++ ;
		}
		fclose(file_ptr) ;
		free(file_path) ;
	}
	dir = opendir(fail_dir) ;
	
	while ((dir_info = readdir(dir))) {

                if (dir_info->d_name[0] == '.')
                        continue ;
                if (dir_info->d_type == DT_DIR)
                        continue ;

                int tp_branch[num + 1] ;
                memset(tp_branch, 0, sizeof(int) * (num + 1)) ;

                char * file_path = (char *) malloc (strlen(fail_dir) + strlen(dir_info->d_name)) ;
                strcpy(file_path, fail_dir) ;
                strcat(file_path, dir_info->d_name) ;

                FILE * file_ptr = fopen(file_path, "r") ;

                char buf[20] ;
                memset(buf, 0, 20) ;

                while (!feof(file_ptr)) {
                        fgets(buf, 20, file_ptr) ;
                        long int tp = strtol(buf, NULL, 16) ;
			if (tp > num)
				continue ;
                        f_branch[tp] ++ ;
                }
                fclose(file_ptr) ;
                free(file_path) ;	
	}

	for (int i = 1 ; i < num + 1 ; i ++) {
		if (p_branch[i] > 0 || f_branch[i] > 0) {
			printf("%d : %d %d\n", i, p_branch[i], f_branch[i]) ;
		}
	}
*/

	return 0 ;
}
