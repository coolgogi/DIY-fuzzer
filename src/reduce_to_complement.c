#include "../include/runner.h"
#include "../include/ddmin.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <unistd.h>
#include <limits.h>

char * 
reduce_to_complement(char * executeFile_path, char * input_file_path, char ** substrings, int n) {
    
    char ** sub_complement = (char **) malloc (sizeof(char *) * n); //

    char * extension = strrchr(input_file_path, '.');
    char * fileName = (char *) malloc (sizeof(char) * PATH_MAX); //

    size_t fileNameLengthWithoutExtension = strlen(input_file_path) - strlen(extension);
    strncpy(fileName, input_file_path, fileNameLengthWithoutExtension);
    
    for (int i = 0 ; i < n ; i ++) {
        sub_complement[i] = (char *) malloc (sizeof(char) * PATH_MAX); //
    
        sprintf(sub_complement[i], "%s-%d%s", fileName, i, extension); 
        mode_t mode = S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH ;
        
        int fp = creat(sub_complement[i], mode);

        FILE * write_file = fopen(sub_complement[i], "wa");
        for(int j = 0 ; j < n ; j ++) {
            if (i == j) {
                continue;
            }

            unsigned char buf;
            FILE * read_file = fopen(substrings[j], "r");
            while (fread(&buf, 1, 1, read_file) == 1) {
                fwrite(&buf, 1, 1, write_file);
            }
            fclose(read_file);
        }
        fclose(write_file);
        close(fp);

        EXITCODE rt = runner(executeFile_path, sub_complement[i], "output/output.txt");
        if(rt.valid == INVALID) {
            
            free(fileName);
            for (int j = i + 1 ; j < n ; j ++) {
                free(sub_complement[j]);
            }
            return sub_complement[i];
        }
        remove(sub_complement[i]);
        free(sub_complement[i]);
    }
    free(fileName);
    free(sub_complement);
    return input_file_path;
}