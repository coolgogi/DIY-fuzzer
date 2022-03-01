#include <dirent.h>
#include <string.h>
#include <errno.h>
#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
#include "../include/runner.h"

int
read_exec_dir (char * dir_path, char * output_path) {

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
            
            char * file_path = (char *) malloc (sizeof(char) * PATH_MAX);
            strcpy(file_path, dir_path);
            strcat(file_path, dir_info->d_name);
            // printf("path: %s\n", file_path);
            EXITCODE rt = runner(file_path, ".", output_path);
            
            // printf("%s: validation : %d, num : %d", file_path, rt.code_num, rt.valid);

            if (dir_info->d_type == DT_DIR) {
                strcat(file_path, "/");
                read_exec_dir(file_path, output_path);
            }

            free(file_path);

        }
    }

    closedir(dir);

    return 0;


}