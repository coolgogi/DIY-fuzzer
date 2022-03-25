#include <dirent.h>
#include <string.h>
#include <errno.h>
#include <limits.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include "../include/runner.h"

int
read_exec_dir (char * executeFile_path, char * dir_path, char * outputFile_path) {

    DIR * dir;
    struct dirent * dir_info;

    dir = opendir(dir_path);
    
    if (dir == NULL) {
        perror("opendir returned NULL");
        return errno;
    }

    while ((dir_info = readdir(dir))) {

        if (strcmp(dir_info->d_name, ".") == 0) {
            continue;
        }
        else if (strcmp(dir_info->d_name, "..") == 0) {
            continue;
        }
        else {
            
            char * file_path = (char *) malloc (strlen(dir_path) + strlen(dir_info->d_name) + 1);
            
	    strcpy(file_path, dir_path);
            strcat(file_path, dir_info->d_name);
	  	
            if (dir_info->d_type == DT_DIR) {
                strcat(file_path, "/");
                read_exec_dir(executeFile_path, file_path, outputFile_path);
            }
	    else { 
		char * output_path = (char *) malloc (strlen(file_path) + 10);
		strcpy(output_path, file_path);
		strcat(output_path, ".bcov");
            	EXITCODE rt = runner(executeFile_path, file_path, outputFile_path);
		free(output_path);
	    }

            free(file_path);

        }
    }

    closedir(dir);

    return 0;
}
