#include "../include/runner.h"
#include "../include/ddmin.h"
#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <string.h>

char * 
reduce_to_substring (char * executeFile_path, char * s, int n) {
    
    char ** ss = split(s, n);
    
    for (int i = 0 ; i < n ; i ++ ) {
        
        EXITCODE rt = runner(executeFile_path, ss[i], "output/output.txt");
        if(rt.valid == INVALID) {
            for (int j = i + 1 ; j < n ; j ++) {
                remove(ss[j]);
            }
            return ss[i];
           }
        remove(ss[i]);
    }
    free(ss);
    return s;
}