#include <string.h>
#include <math.h>
#include <stdlib.h>
#include <stdio.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <limits.h>

char **
split (char * input_file_path, int n) {
    
    struct stat st;
    stat(input_file_path, &st);
    int size = (int) ceil((double)st.st_size / n);
    
    FILE * read_file = fopen(input_file_path, "r");

    char * fileName = (char *) malloc (sizeof(char) * PATH_MAX); //
    memset(fileName, 0, PATH_MAX);
    char * extension ;
    extension = strrchr(input_file_path, '.');

    size_t fileNameLengthWithoutExtension = strlen(input_file_path) - strlen(extension);
    strncpy(fileName, input_file_path, fileNameLengthWithoutExtension);
    
    char ** ss ;
    ss = (char **) malloc (sizeof(char *) * n); //

    for (int i = 0 ; i < n ; i ++ ) {

        ss[i] = (char *) malloc (sizeof(char) * PATH_MAX); //
        sprintf(ss[i], "%s_%d%s", fileName, i, extension); //
        
        mode_t mode = S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH ;
        creat(ss[i], mode);

        FILE * write_file = fopen(ss[i], "w");
        for (int j = 0 ; j < size ; j ++) {
            unsigned char buf;
            if (fread(&buf, 1, 1, read_file) != 1) {
                break ;
            }
            fwrite(&buf, 1, 1, write_file);
        }
        fclose(write_file);
    }

    free(fileName);
    fclose(read_file);
    return ss ;
}
