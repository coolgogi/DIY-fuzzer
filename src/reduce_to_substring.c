#include "../include/runner.h"
#include "../include/ddmin.h"
#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <string.h>

char * 
reduce_to_substring (char * executeFile_path, char * input_file_path, char ** substrings, int n) {
    
    for (int i = 0 ; i < n ; i ++ ) {
        
        EXITCODE rt = runner(executeFile_path, substrings[i], "output/output.txt");
        if(rt.valid == INVALID) {
            for (int j = i + 1; j < n ; j ++) {
                remove(substrings[j]);
            }
            return substrings[i];
        }
        remove(substrings[i]);
    }
    return input_file_path;
}