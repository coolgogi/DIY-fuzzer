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
exec_sancov_dir (char * executeFile_path, char * dir_path, char * outputDir_path, int bcov) {
	
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

	    if (dir_info->d_name[0] == '.') {
		continue ;
	    }
            
            char * file_path = (char *) malloc (strlen(dir_path) + strlen(dir_info->d_name) + 2) ;
	    strcpy(file_path, dir_path);
            strcat(file_path, dir_info->d_name);

            if (dir_info->d_type == DT_DIR) {
        	strcat(file_path, "/");
    		int * tp = exec_sancov_dir(executeFile_path, file_path, outputDir_path, bcov);
		rt[0] = rt[0] + tp[0] ;
		rt[1] = rt[1] + tp[1] ;
		rt[2] = rt[2] + tp[2] ;
		free(tp) ;
            }
	    else {
		rt[2]++; 
            	char * outputFile_path = (char *) malloc (strlen(outputDir_path) + strlen(dir_info->d_name) + 6) ;
	    	char * ch = (char *) malloc (2) ;
		strcpy(outputFile_path, outputDir_path) ;
	    	strcat(outputFile_path, dir_info->d_name) ;
	    	strcat(outputFile_path, ".bcov") ;
            		
		EXITCODE exit = runner(executeFile_path, file_path, outputFile_path) ;

		if (exit.code_num == 0) {
			strcpy(ch, "p\n") ;
			rt[0] ++ ;
		}
		else if (exit.code_num == 9) {
			strcpy(ch, "t\n") ;
			rt[1] ++ ;
		}
		else {	
			strcpy(ch, "f\n") ;
			rt[1] ++ ;
		}
		
		FILE * fp = fopen(outputFile_path, "a") ;
		fwrite(ch, 1, strlen(ch), fp) ;
		fclose(fp) ;
		

		char * target_sancov = (char *) malloc (30) ;
		sprintf(target_sancov, "xmllint.%d.sancov", exit.child_pid) ;
		char * sancov_output = (char *) malloc (strlen(target_sancov) + 26) ;

		if (ch[0] == 'p') {
			sprintf(sancov_output, "%spass/%s.bcov", outputDir_path, target_sancov) ;
			sancov_runner(executeFile_path, target_sancov, sancov_output) ;	
		}
		else {
			sprintf(sancov_output, "%sfail/%s.bcov", outputDir_path, target_sancov) ;
			sancov_runner(executeFile_path, target_sancov, sancov_output) ;	
		}
		rm_runner(target_sancov) ;
			
		free(ch) ;
		free(sancov_output) ;
		free(outputFile_path) ;
	    }

            free(file_path);
	    
    }
    
    return rt ;
}
