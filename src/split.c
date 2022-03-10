#include <string.h>
#include <math.h>
#include <stdlib.h>
#include <stdio.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <limits.h>

char **
split (char * path, int n) {
    
    struct stat st;
    stat(path, &st);
    int size = (int) ceil((double)st.st_size / n) ;

    FILE * read_file = fopen(path, "r");

    char * dir_path = (char *) malloc (sizeof(char) * PATH_MAX);
    char * extension ;

    extension = strrchr(path, '.');
    size_t fileNameLengthWithoutExtension = strlen(path) - strlen(extension);
    strncat(dir_path, path, fileNameLengthWithoutExtension);

    char ** ss ;
    ss = (char ** ) malloc (sizeof(char *) * n);
    // char ss[n][PATH_MAX];
    for (int i = 0 ; i < n ; i ++ ) {

        ss[i] = (char * ) malloc (sizeof(char) * PATH_MAX);
        sprintf(ss[i], "%s%d%s", dir_path, i, extension);
        
        mode_t mode = S_IRWXU | S_IRGRP | S_IXGRP | S_IROTH | S_IXOTH ;
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

    free(dir_path);
    fclose(read_file);
    return ss ;
}