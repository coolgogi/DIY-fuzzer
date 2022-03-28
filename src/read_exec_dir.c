#include <dirent.h>
#include <string.h>
#include <errno.h>
#include <limits.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include "../include/runner.h"

int
read_exec_dir (char * executeFile_path, char * dir_path, char * outputDir_path) {
	
    int * pf_rt = (int *) malloc (sizeof(int) * 2) ;
    pf_rt[0] = 0 ;
    pf_rt[1] = 0 ;
    DIR * dir;
    struct dirent * dir_info;

    dir = opendir(dir_path);
    
    if (dir == NULL) {
        perror("opendir returned NULL");
        pf_rt[0] = -1 ;
	pf_rt[1] = errno ;
	return EXIT_FAILURE;
    }

    while ((dir_info = readdir(dir))) {

        if (strcmp(dir_info->d_name, ".") == 0) {
        	continue;
        }
        else if (strcmp(dir_info->d_name, "..") == 0) {
        	continue;
        }
        else {
            
            char * file_path = (char *) malloc (strlen(dir_path) + strlen(dir_info->d_name) + 2) ;
	    strcpy(file_path, dir_path);
            strcat(file_path, dir_info->d_name);

	  	
            if (dir_info->d_type == DT_DIR) {
                strcat(file_path, "/");
                read_exec_dir(executeFile_path, file_path, outputDir_path);
            }
	    else { 
            	char * outputFile_path = (char *) malloc (strlen(outputDir_path) + strlen(dir_info->d_name) + 6) ;
	    	char * ch = (char *) malloc (1) ;
		strcpy(outputFile_path, outputDir_path) ;
	    	strcat(outputFile_path, dir_info->d_name) ;
	    	strcat(outputFile_path, ".bcov") ;
            	
		EXITCODE rt = runner(executeFile_path, file_path, outputFile_path) ;

		if (rt.code_num == 0) {
			*ch = 'p' ;
		}
		else {
			*ch = 'f' ;
		}
		
		FILE * fp = fopen(outputFile_path, "a") ;
		fwrite(ch, 1, 1, fp) ;
		fclose(fp) ;
		
		free(ch) ;
		free(outputFile_path) ;
	    }

            free(file_path);
	    
        }
    }

    int num_of_branch = 0 ;
    uint32_t * buf = (uint32_t *) malloc (sizeof(uint32_t)) ;
    
    char * total_path = (char *) malloc (strlen(executeFile_path) + 6) ;
    strcpy(total_path, executeFile_path) ;
    strcat(total_path, ".bcov") ;
    FILE * total_fp = fopen(total_path, "r") ;

    fread(buf, 1, sizeof(uint32_t), total_fp) ;

    num_of_branch = * buf ;
    
    fclose(total_fp) ;
    remove(total_path) ;
    free(total_path) ;
    free(buf) ;
    closedir(dir) ;

    return num_of_branch ;
}
