#include "../include/runner.h"
#include "../include/ddmin.h"
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <string.h>
#include <sys/stat.h>
#include <limits.h>

char * 
reduce_to_complement(char * file_path, char * s, int n) {

    char ** ss = split(s, n);
    char ** sub_complement = (char **) malloc (sizeof(char *) * n);

    char * extension = strrchr(s, '.');
    char * fileName_path = (char *) malloc (sizeof(char) * PATH_MAX);
    size_t fileNameLengthWithoutExtension = strlen(s) - strlen(extension);
    strncat(fileName_path, s, fileNameLengthWithoutExtension);

    for (int i = 0 ; i < n ; i ++) {
        sub_complement[i] = (char *) malloc (sizeof(char) * PATH_MAX);
        sprintf(sub_complement[i], "%s-%d%s", fileName_path, i, extension);

        mode_t mode = S_IRWXU | S_IRGRP | S_IXGRP | S_IROTH | S_IXOTH ;
        creat(sub_complement[i], mode);

        FILE * write_file = fopen(sub_complement[i], "wa");

        for(int j = 0 ; j < n ; j ++) {
            if (i == j) {
                continue;
            }

            unsigned char buf;
            FILE * read_file = fopen(ss[j], "r");
            while (fread(&buf, 1, 1, read_file) == 1) {
                fwrite(&buf, 1, 1, write_file);
            }
            fclose(read_file);
        }
        fclose(write_file);

        EXITCODE rt = runner(file_path, sub_complement[i], "./output/output.txt");
        if(rt.valid == INVALID) {
            return sub_complement[i];
        }
    }
    return s;
}