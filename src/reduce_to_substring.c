#include "../include/runner.h"
#include "../include/ddmin.h"
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <string.h>
#include <sys/stat.h>
#include <limits.h>

char * 
reduce_to_substring (char * file_path, char * s, int n) {

    char ** ss = split(s, n);
    for (int i = 0 ; i < n ; i ++ ) {
        
        EXITCODE rt = runner(file_path, ss[i], "./output/output.txt");
        if(rt.valid == INVALID) {
            return ss[i];
        }
    }
    return s;
}