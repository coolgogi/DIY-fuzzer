#include <dirent.h>
#include <string.h>
#include <errno.h>
#include <limits.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include "../include/runner.h"

int *
read_exec_dir (char * executeFile_path, char * dir_path, char * outputDir_path, int bcov) {
	
    DIR * dir;
    struct dirent * dir_info;

    dir = opendir(dir_path);
    
    int * rt = (int *) malloc (sizeof(int) * 3) ;     
    rt[0] = 0 ;
    rt[1] = 0 ;
    rt[2] = 0 ;
    if (dir == NULL) {
        perror("opendir returned NULL");
	rt[0] = -1 ;
	rt[1] = errno ;
	return rt;
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
    		int * tp = read_exec_dir(executeFile_path, file_path, outputDir_path, bcov);
		rt[0] = rt[0] + tp[0] ;
		rt[1] = rt[1] + tp[1] ;
		free(tp) ;
            }
	    else { 
            	char * outputFile_path = (char *) malloc (strlen(outputDir_path) + strlen(dir_info->d_name) + 6) ;
	    	char * ch = (char *) malloc (1) ;
		strcpy(outputFile_path, outputDir_path) ;
	    	strcat(outputFile_path, dir_info->d_name) ;
	    	strcat(outputFile_path, ".bcov") ;
            		
		EXITCODE exit = runner(executeFile_path, file_path, outputFile_path) ;

		if (exit.code_num == 0) {
			*ch = 'p' ;
			rt[0] ++ ;
		}
		else if (exit.code_num == 9) {
			*ch = 't' ;
			rt[1] ++ ;
		}
/*
 * 		else if (exit.code_num == 11) {
			*ch = 'f' ;
			rt[2] ++ ;
		}
*/
		else {	
			*ch = 'f' ;
			rt[1] ++ ;
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
    
    if (bcov == 1) {    
	    uint32_t * buf = (uint32_t *) malloc (sizeof(uint32_t)) ;
	    char * total_path = (char *) malloc (strlen(executeFile_path) + 6) ;
	    strcpy(total_path, executeFile_path) ;
	    strcat(total_path, ".bcov") ;
	    FILE * total_fp = fopen(total_path, "r") ;

	    fread(buf, 1, sizeof(uint32_t), total_fp) ;
	    rt[2] = * buf ;
    
	    fclose(total_fp) ;
	    remove(total_path) ;
	    free(total_path) ;
	    free(buf) ;
    }
    closedir(dir) ;
    return rt ;
}
