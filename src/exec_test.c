#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "../include/runner.h"

int
main (int argc, char * argv[]) {

    EXITCODE rt ;
    rt = runner("../test/input/dir1/.DS_Store", ".", "../test/output/answer.txt");
    rt = runner("../test/input/dir1/dir2", "", "../test/output/answer.txt");
    rt = runner("../test/input/dir1/dir2/hello4.c", ".", "../test/output/answer.txt");
    rt = runner("../test/input/dir1/dir2/.DS_Store", ".", "../test/output/answer.txt");
    rt = runner("../test/input/dir1/dir2/hello5", ".", "../test/output/answer.txt");
    rt = runner("../test/input/dir1/dir2/hello3.c", ".", "../test/output/answer.txt");
    rt = runner("../test/input/dir1/dir2/hello4", ".", "../test/output/answer.txt");
    rt = runner("../test/input/dir1/dir2/hello3", ".", "../test/output/answer.txt");
    rt = runner("../test/input/dir1/dir2/dir4", ".", "../test/output/answer.txt");
    rt = runner("../test/input/dir1/dir2/dir4/hello7.c", ".", "../test/output/answer.txt");
    rt = runner("../test/input/dir1/dir2/dir4/hello6.c", ".", "../test/output/answer.txt");
    rt = runner("../test/input/dir1/dir2/dir4/hello6", ".", "../test/output/answer.txt");
    rt = runner("../test/input/dir1/dir2/dir4/hello7", ".", "../test/output/answer.txt");
    rt = runner("../test/input/dir1/dir2/hello5.c", ".", "../test/output/answer.txt");
    rt = runner("../test/input/dir1/hello2", ".", "../test/output/answer.txt");
    rt = runner("../test/input/dir1/dir3", ".", "../test/output/answer.txt");
    rt = runner("../test/input/dir1/dir3/hello9.c", ".", "../test/output/answer.txt");
    rt = runner("../test/input/dir1/dir3/hello8.c", ".", "../test/output/answer.txt");
    rt = runner("../test/input/dir1/dir3/hello8", ".", "../test/output/answer.txt");
    rt = runner("../test/input/dir1/dir3/hello9", ".", "../test/output/answer.txt");
    rt = runner("../test/input/dir1/hello2.c", ".", "../test/output/answer.txt");
    rt = runner("../test/input/dir1/hello1.c", ".", "../test/output/answer.txt");
    rt = runner("../test/input/dir1/hello1", ".", "../test/output/answer.txt");
    return 0;

}